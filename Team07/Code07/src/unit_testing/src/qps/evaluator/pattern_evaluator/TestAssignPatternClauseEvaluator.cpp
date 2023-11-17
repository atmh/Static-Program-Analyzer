#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "catch.hpp"
#include "qps/evaluator/pattern_evaluator/AssignPatternClauseEvaluator.h"
#include "qps/query/clauses/Argument.h"
#include "qps/query/declaration/AssignDeclaration.h"
#include "qps/query/declaration/Declaration.h"
#include "qps/query/declaration/VariableDeclaration.h"
#include "qps/table/NormalizedDataStorage.h"
#include "stubs/pkb/PKBStorageReadAPI.h"

TEST_CASE("Pattern clause evaluator - synonym wildcard") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual const std::unordered_map<
        std::string, std::vector<std::pair<std::vector<std::string>, int>>>&
    getAssignPatterns() const noexcept override {
      return assignPatterns;
    }

    virtual const std::vector<std::pair<std::vector<std::string>, int>>&
    getAssignFirstArgPatterns(
        const std::string& lhsArg) const noexcept override {
      return assignPatterns.find(lhsArg) == assignPatterns.end()
                 ? emptyRes
                 : assignPatterns.find(lhsArg)->second;
    }

    std::vector<std::pair<std::vector<std::string>, int>> emptyRes;
    std::unordered_map<std::string,
                       std::vector<std::pair<std::vector<std::string>, int>>>
        assignPatterns{{"v", {{{"1", "2", "+", "3", "+"}, 1}}},
                       {"v2", {{{"1", "2", "+"}, 2}}}};
  };

  SECTION("Test 1") {
    std::shared_ptr<QPS::Declaration> assign =
        std::make_shared<QPS::AssignDeclaration>("a");
    std::shared_ptr<QPS::Declaration> variable =
        std::make_shared<QPS::VariableDeclaration>("v");
    QPS::Argument wildcard;

    QPS::AssignPatternClauseEvaluator evaluator(assign, variable, wildcard);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 2);
  }
}

TEST_CASE("Pattern clause evaluator - synonym tree") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual const std::unordered_map<
        std::string, std::vector<std::pair<std::vector<std::string>, int>>>&
    getAssignPatterns() const noexcept override {
      return assignPatterns;
    }

    virtual const std::vector<std::pair<std::vector<std::string>, int>>&
    getAssignFirstArgPatterns(
        const std::string& lhsArg) const noexcept override {
      return assignPatterns.find(lhsArg) == assignPatterns.end()
                 ? emptyRes
                 : assignPatterns.find(lhsArg)->second;
    }

    std::vector<std::pair<std::vector<std::string>, int>> emptyRes;
    std::unordered_map<std::string,
                       std::vector<std::pair<std::vector<std::string>, int>>>
        assignPatterns{{"v", {{{"1", "2", "+", "3", "+"}, 1}}},
                       {"v2", {{{"1", "2", "+"}, 2}}}};
  };

  SECTION("Exact match") {
    std::shared_ptr<QPS::Declaration> assign =
        std::make_shared<QPS::AssignDeclaration>("a");
    std::shared_ptr<QPS::Declaration> variable =
        std::make_shared<QPS::VariableDeclaration>("v");
    QPS::Argument tree({"1", "2", "+"}, true);

    QPS::AssignPatternClauseEvaluator evaluator(assign, variable, tree);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
  }

  SECTION("Partial match") {
    std::shared_ptr<QPS::Declaration> assign =
        std::make_shared<QPS::AssignDeclaration>("a");
    std::shared_ptr<QPS::Declaration> variable =
        std::make_shared<QPS::VariableDeclaration>("v");
    QPS::Argument tree({"1", "2", "+"}, false);

    QPS::AssignPatternClauseEvaluator evaluator(assign, variable, tree);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 2);
  }

  SECTION("Partial match fail") {
    std::shared_ptr<QPS::Declaration> assign =
        std::make_shared<QPS::AssignDeclaration>("a");
    std::shared_ptr<QPS::Declaration> variable =
        std::make_shared<QPS::VariableDeclaration>("v");
    QPS::Argument tree({"2", "3", "+"}, false);

    QPS::AssignPatternClauseEvaluator evaluator(assign, variable, tree);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }
}

TEST_CASE("Pattern clause evaluator - value wildcard") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual const std::unordered_map<
        std::string, std::vector<std::pair<std::vector<std::string>, int>>>&
    getAssignPatterns() const noexcept override {
      return assignPatterns;
    }

    virtual const std::vector<std::pair<std::vector<std::string>, int>>&
    getAssignFirstArgPatterns(
        const std::string& lhsArg) const noexcept override {
      return assignPatterns.find(lhsArg) == assignPatterns.end()
                 ? emptyRes
                 : assignPatterns.find(lhsArg)->second;
    }

    std::vector<std::pair<std::vector<std::string>, int>> emptyRes;
    std::unordered_map<std::string,
                       std::vector<std::pair<std::vector<std::string>, int>>>
        assignPatterns{{"v", {{{"1", "2", "+", "3", "+"}, 1}}},
                       {"v2", {{{"1", "2", "+"}, 2}}}};
  };

  SECTION("v") {
    std::shared_ptr<QPS::Declaration> assign =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::Argument val = std::string("v");
    QPS::Argument wildcard;

    QPS::AssignPatternClauseEvaluator evaluator(assign, val, wildcard);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.size() == 1);
  }

  SECTION("v2") {
    std::shared_ptr<QPS::Declaration> assign =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::Argument val = std::string("v2");
    QPS::Argument wildcard;

    QPS::AssignPatternClauseEvaluator evaluator(assign, val, wildcard);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.size() == 1);
  }

  SECTION("random") {
    std::shared_ptr<QPS::Declaration> assign =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::Argument val = std::string("random");
    QPS::Argument wildcard;

    QPS::AssignPatternClauseEvaluator evaluator(assign, val, wildcard);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }
}

TEST_CASE("Pattern clause evaluator - value tree") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual const std::unordered_map<
        std::string, std::vector<std::pair<std::vector<std::string>, int>>>&
    getAssignPatterns() const noexcept override {
      return assignPatterns;
    }

    virtual const std::vector<std::pair<std::vector<std::string>, int>>&
    getAssignFirstArgPatterns(
        const std::string& lhsArg) const noexcept override {
      return assignPatterns.find(lhsArg) == assignPatterns.end()
                 ? emptyRes
                 : assignPatterns.find(lhsArg)->second;
    }

    std::vector<std::pair<std::vector<std::string>, int>> emptyRes;
    std::unordered_map<std::string,
                       std::vector<std::pair<std::vector<std::string>, int>>>
        assignPatterns{{"v", {{{"1", "2", "+", "3", "+"}, 1}}},
                       {"v2", {{{"1", "2", "+"}, 2}}}};
  };

  SECTION("Exact match - success") {
    std::shared_ptr<QPS::Declaration> assign =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::Argument val = std::string("v2");
    QPS::Argument tree({"1", "2", "+"}, true);

    QPS::AssignPatternClauseEvaluator evaluator(assign, val, tree);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
  }

  SECTION("Exact match - fail") {
    std::shared_ptr<QPS::Declaration> assign =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::Argument val = std::string("v");
    QPS::Argument tree({"1", "2", "+"}, true);

    QPS::AssignPatternClauseEvaluator evaluator(assign, val, tree);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }

  SECTION("Partial match") {
    std::shared_ptr<QPS::Declaration> assign =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::Argument val = std::string("v");
    QPS::Argument tree({"1", "2", "+"}, false);

    QPS::AssignPatternClauseEvaluator evaluator(assign, val, tree);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
  }

  SECTION("Partial match fail") {
    std::shared_ptr<QPS::Declaration> assign =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::Argument val = std::string("v");
    QPS::Argument tree({"2", "3", "+"}, false);

    QPS::AssignPatternClauseEvaluator evaluator(assign, val, tree);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }
}

TEST_CASE("Pattern clause evaluator - wildcard wildcard") {
  SECTION("True") {
    struct TestStub : public PKB::PKBStorageReadStub {
      virtual const std::unordered_map<
          std::string, std::vector<std::pair<std::vector<std::string>, int>>>&
      getAssignPatterns() const noexcept override {
        return assignPatterns;
      }

      virtual const std::vector<std::pair<std::vector<std::string>, int>>&
      getAssignFirstArgPatterns(
          const std::string& lhsArg) const noexcept override {
        return assignPatterns.find(lhsArg) == assignPatterns.end()
                   ? emptyRes
                   : assignPatterns.find(lhsArg)->second;
      }

      std::vector<std::pair<std::vector<std::string>, int>> emptyRes;
      std::unordered_map<std::string,
                         std::vector<std::pair<std::vector<std::string>, int>>>
          assignPatterns{{"v", {{{"1", "2", "+", "3", "+"}, 1}}},
                         {"v2", {{{"1", "2", "+"}, 2}}}};
    };

    std::shared_ptr<QPS::Declaration> assign =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::Argument wildcard1;
    QPS::Argument wildcard2;

    QPS::AssignPatternClauseEvaluator evaluator(assign, wildcard1, wildcard2);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.trueTable());
  }

  SECTION("False") {
    struct TestStub : public PKB::PKBStorageReadStub {
      virtual const std::unordered_map<
          std::string, std::vector<std::pair<std::vector<std::string>, int>>>&
      getAssignPatterns() const noexcept override {
        return assignPatterns;
      }

      virtual const std::vector<std::pair<std::vector<std::string>, int>>&
      getAssignFirstArgPatterns(
          const std::string& lhsArg) const noexcept override {
        return assignPatterns.find(lhsArg) == assignPatterns.end()
                   ? emptyRes
                   : assignPatterns.find(lhsArg)->second;
      }

      std::vector<std::pair<std::vector<std::string>, int>> emptyRes;
      std::unordered_map<std::string,
                         std::vector<std::pair<std::vector<std::string>, int>>>
          assignPatterns{};
    };

    std::shared_ptr<QPS::Declaration> assign =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::Argument wildcard1;
    QPS::Argument wildcard2;

    QPS::AssignPatternClauseEvaluator evaluator(assign, wildcard1, wildcard2);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }
}

TEST_CASE("Pattern clause evaluator - wildcard tree") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual const std::unordered_map<
        std::string, std::vector<std::pair<std::vector<std::string>, int>>>&
    getAssignPatterns() const noexcept override {
      return assignPatterns;
    }

    virtual const std::vector<std::pair<std::vector<std::string>, int>>&
    getAssignFirstArgPatterns(
        const std::string& lhsArg) const noexcept override {
      return assignPatterns.find(lhsArg) == assignPatterns.end()
                 ? emptyRes
                 : assignPatterns.find(lhsArg)->second;
    }

    std::vector<std::pair<std::vector<std::string>, int>> emptyRes;
    std::unordered_map<std::string,
                       std::vector<std::pair<std::vector<std::string>, int>>>
        assignPatterns{{"v", {{{"1", "2", "+", "3", "+"}, 1}}},
                       {"v2", {{{"1", "2", "+"}, 2}}}};
  };

  SECTION("Exact match - success") {
    std::shared_ptr<QPS::Declaration> assign =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::Argument wildcard;
    QPS::Argument tree({"1", "2", "+"}, true);

    QPS::AssignPatternClauseEvaluator evaluator(assign, wildcard, tree);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
  }

  SECTION("Exact match - fail") {
    std::shared_ptr<QPS::Declaration> assign =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::Argument wildcard;
    QPS::Argument tree({"2", "3", "+"}, true);

    QPS::AssignPatternClauseEvaluator evaluator(assign, wildcard, tree);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }

  SECTION("Partial match") {
    std::shared_ptr<QPS::Declaration> assign =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::Argument wildcard;
    QPS::Argument tree({"1", "2", "+"}, false);

    QPS::AssignPatternClauseEvaluator evaluator(assign, wildcard, tree);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 2);
  }

  SECTION("Partial match fail") {
    std::shared_ptr<QPS::Declaration> assign =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::Argument wildcard;
    QPS::Argument tree({"2", "3", "+"}, false);

    QPS::AssignPatternClauseEvaluator evaluator(assign, wildcard, tree);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }
}
