#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "catch.hpp"
#include "qps/evaluator/such_that_clause_evaluator/ParentClauseEvaluator.h"
#include "qps/query/clauses/Argument.h"
#include "qps/query/declaration/Declaration.h"
#include "qps/table/NormalizedDataStorage.h"
#include "stubs/pkb/PKBStorageReadAPI.h"

TEST_CASE("ParentClauseEvaluator - Test value value") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual bool getParentRelationshipExists(int a, int b) override {
      return a == 1 && (b == 2 || b == 3);
    }
  };

  SECTION("Correct relationship - 1") {
    QPS::ParentClauseEvaluator evaluator(1, 2);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }

  SECTION("Correct relationship - 2") {
    QPS::ParentClauseEvaluator evaluator(1, 3);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }

  SECTION("Wrong relationship 1") {
    QPS::ParentClauseEvaluator evaluator(1, 4);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
    REQUIRE(!table.trueTable());
  }
}

TEST_CASE("ParentClauseEvaluator - Test first arg") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }
    virtual std::unordered_set<int> getParentFirstArgRelationships(
        int argOne) override {
      switch (argOne) {
        case 1:
          return {2, 3};
        case 2:
          return {};
        case 3:
          return {};
        case 4:
          return {};
        case 5:
          return {};
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
    QPS::ParentClauseEvaluator evaluator(1, a);
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
    QPS::ParentClauseEvaluator evaluator(2, a);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }
}

TEST_CASE("ParentClauseEvaluator - Test second arg") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }
    virtual std::unordered_set<int> getParentSecondArgRelationships(
        int argTwo) override {
      switch (argTwo) {
        case 1:
          return {};
        case 2:
          return {1};
        case 3:
          return {1};
        case 4:
          return {};
        case 5:
          return {};
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
    QPS::ParentClauseEvaluator evaluator(a, 1);
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
    QPS::ParentClauseEvaluator evaluator(a, 2);
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
    QPS::ParentClauseEvaluator evaluator(a, 3);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
  }
}

TEST_CASE("ParentClauseEvaluator - Test wildcard wildcard") {
  SECTION("No parent") {
    struct TestStub : public PKB::PKBStorageReadStub {
      virtual bool hasParentRelationship() override { return false; }
    };
    QPS::Argument wildcard1;
    QPS::Argument wildcard2;
    QPS::ParentClauseEvaluator evaluator(wildcard1, wildcard2);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }

  SECTION("Has parent") {
    struct TestStub : public PKB::PKBStorageReadStub {
      virtual bool hasParentRelationship() override { return true; }
    };
    QPS::Argument wildcard1;
    QPS::Argument wildcard2;
    QPS::ParentClauseEvaluator evaluator(wildcard1, wildcard2);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }
}
