#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "catch.hpp"
#include "qps/evaluator/such_that_clause_evaluator/ParentStarClauseEvaluator.h"
#include "qps/query/clauses/Argument.h"
#include "qps/query/declaration/Declaration.h"
#include "qps/table/NormalizedDataStorage.h"
#include "stubs/pkb/PKBStorageReadAPI.h"

TEST_CASE("ParentStarClauseEvaluator - Test value value") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual bool getParentStarRelationshipExists(int a, int b) override {
      return a < b && b < 4;
    }
  };

  SECTION("Correct relationship - 1") {
    QPS::ParentStarClauseEvaluator evaluator(1, 2);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }

  SECTION("Correct relationship - 2") {
    QPS::ParentStarClauseEvaluator evaluator(1, 3);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }

  SECTION("Wrong relationship 1") {
    QPS::ParentStarClauseEvaluator evaluator(1, 4);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
    REQUIRE(!table.trueTable());
  }
}

TEST_CASE("ParentStarClauseEvaluator - Test first arg") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }
    virtual std::unordered_set<int> getParentStarFirstArgRelationships(
        int argOne) override {
      switch (argOne) {
        case 1:
          return {2, 3};
        case 2:
          return {3};
        case 3:
          return {};
        case 4:
          return {5, 6};
        case 5:
          return {6};
        case 6:
          return {};
        default:
          return {};
      }
    }
    std::unordered_set<int> assigns{1, 2, 3, 4, 5};
  };

  SECTION("Test - 1") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::ParentStarClauseEvaluator evaluator(1, a);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 2);
  }

  SECTION("Test - 2") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::ParentStarClauseEvaluator evaluator(2, a);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
  }

  SECTION("Test - 3") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::ParentStarClauseEvaluator evaluator(3, a);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }

  SECTION("Test - 4") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::ParentStarClauseEvaluator evaluator(4, a);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.size() == 1);
  }

  SECTION("Test - 5") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::ParentStarClauseEvaluator evaluator(5, a);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }

  SECTION("Test - 6") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::ParentStarClauseEvaluator evaluator(6, a);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }
}

TEST_CASE("ParentStarClauseEvaluator - Test second arg") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }
    virtual std::unordered_set<int> getParentStarSecondArgRelationships(
        int argTwo) override {
      switch (argTwo) {
        case 1:
          return {};
        case 2:
          return {1};
        case 3:
          return {2, 1};
        case 4:
          return {};
        case 5:
          return {4};
        case 6:
          return {4, 5};
        default:
          return {};
      }
    }
    std::unordered_set<int> assigns{1, 2, 3, 4, 6};
  };

  SECTION("Test - 1") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::ParentStarClauseEvaluator evaluator(a, 1);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }

  SECTION("Test - 2") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::ParentStarClauseEvaluator evaluator(a, 2);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
  }

  SECTION("Test - 3") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::ParentStarClauseEvaluator evaluator(a, 3);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 2);
  }

  SECTION("Test - 4") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::ParentStarClauseEvaluator evaluator(a, 4);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }

  SECTION("Test - 5") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::ParentStarClauseEvaluator evaluator(a, 5);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.size() == 1);
  }

  SECTION("Test - 6") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::ParentStarClauseEvaluator evaluator(a, 6);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.size() == 1);
  }
}

TEST_CASE("ParentStarClauseEvaluator - Test wildcard wildcard") {
  SECTION("No ParentStar") {
    struct TestStub : public PKB::PKBStorageReadStub {
      virtual bool hasParentStarRelationship() override { return false; }
    };

    QPS::Argument wildcard1;
    QPS::Argument wildcard2;
    QPS::ParentStarClauseEvaluator evaluator(wildcard1, wildcard2);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }

  SECTION("Has ParentStar") {
    struct TestStub : public PKB::PKBStorageReadStub {
      virtual bool hasParentStarRelationship() override { return true; }
    };

    QPS::Argument wildcard1;
    QPS::Argument wildcard2;
    QPS::ParentStarClauseEvaluator evaluator(wildcard1, wildcard2);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }
}
