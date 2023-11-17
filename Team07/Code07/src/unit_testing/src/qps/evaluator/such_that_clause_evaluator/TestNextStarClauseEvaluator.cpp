#include <memory>
#include <unordered_set>

#include "catch.hpp"
#include "qps/evaluator/such_that_clause_evaluator/NextStarClauseEvaluator.h"
#include "qps/query/declaration/StatementDeclaration.h"
#include "qps/table/NormalizedDataStorage.h"
#include "stubs/pkb/PKBStorageReadAPI.h"

/*
 * Light testing, most such that clause testing already completed in
 * follows relationship
 */

// follows this cfg here
// https://nus-cs3203.github.io/course-website/contents/advanced-spa-requirements/cfg.html

struct NextStarEvaluatorPKBStub : public PKB::PKBStorageReadStub {
  virtual const std::unordered_set<int>& getStmts() const noexcept override {
    return stmts;
  };

  virtual bool hasNextRelationship() override { return true; }

  std::unordered_set<int> getNextFirstArgRelationships(int argOne) override {
    switch (argOne) {
      case 1:
        return {2};
      case 2:
        return {3};
      case 3:
        return {4, 7};
      case 4:
        return {5};
      case 5:
        return {6};
      case 6:
        return {3};
      case 7:
        return {8, 9};
      case 8:
        return {10};
      case 9:
        return {10};
      case 10:
        return {11};
      case 11:
        return {12};
      case 12:
        return {};
      default:
        return {};
    }
  }

  std::unordered_set<int> getNextSecondArgRelationships(int argTwo) override {
    switch (argTwo) {
      case 1:
        return {};
      case 2:
        return {1};
      case 3:
        return {2, 6};
      case 4:
        return {3};
      case 5:
        return {4};
      case 6:
        return {5};
      case 7:
        return {3};
      case 8:
        return {7};
      case 9:
        return {7};
      case 10:
        return {8, 9};
      case 11:
        return {10};
      case 12:
        return {11};
      default:
        return {};
    }
  }

  std::unordered_set<int> stmts{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
};

TEST_CASE("Next Star Evaluator value value") {
  SECTION("1 - 2") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{2};
    QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NextStarEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }

  SECTION("1 - 3") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{3};
    QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NextStarEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }

  SECTION("3 - 3") {
    QPS::Argument arg1{3};
    QPS::Argument arg2{3};
    QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NextStarEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }

  SECTION("4 - 3") {
    QPS::Argument arg1{4};
    QPS::Argument arg2{3};
    QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NextStarEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }

  SECTION("4 - 7") {
    QPS::Argument arg1{4};
    QPS::Argument arg2{7};
    QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NextStarEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }

  SECTION("7 - 4") {
    QPS::Argument arg1{7};
    QPS::Argument arg2{4};
    QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NextStarEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(table.empty());
    REQUIRE(!table.trueTable());
  }
}

TEST_CASE("Next Star Evaluator value synonym") {
  SECTION("Next*(1, s)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>("s")};
    QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NextStarEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.size() == 11);
  }

  SECTION("Next*(2, s)") {
    QPS::Argument arg1{2};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>("s")};
    QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NextStarEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.size() == 10);
  }

  SECTION("Next*(3, s)") {
    QPS::Argument arg1{3};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>("s")};
    QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NextStarEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.size() == 10);
  }

  SECTION("Next*(4, s)") {
    QPS::Argument arg1{4};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>("s")};
    QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NextStarEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.size() == 10);
  }

  SECTION("Next*(7, s)") {
    QPS::Argument arg1{7};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>("s")};
    QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NextStarEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.size() == 5);
  }
}

TEST_CASE("Next Star Evaluator value wildcard") {
  SECTION("Next*(1, _)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2;
    QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NextStarEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }

  SECTION("Next*(12, _)") {
    QPS::Argument arg1{12};
    QPS::Argument arg2;
    QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NextStarEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(table.empty());
    REQUIRE(!table.trueTable());
  }
}

TEST_CASE("Next Star Evaluator synonym value") {
  SECTION("Next*(s, 2)") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>("s")};
    QPS::Argument arg2{2};
    QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NextStarEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
  }

  SECTION("Next*(s, 10)") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>("s")};
    QPS::Argument arg2{10};
    QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NextStarEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.size() == 9);
  }
}

TEST_CASE("Next Star Evaluator synonym synonym") {
  QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>("s1")};
  QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>("s2")};
  QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<NextStarEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 75);
}

TEST_CASE("Next Star Evaluator synonym wildcard") {
  QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>("s")};
  QPS::Argument arg2;
  QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<NextStarEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 11);
}

TEST_CASE("Next Star Evaluator wildcard value") {
  SECTION("Next*(_, 1)") {
    QPS::Argument arg1;
    QPS::Argument arg2{1};
    QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NextStarEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(table.empty());
    REQUIRE(!table.trueTable());
  }

  SECTION("Next*(_, 2)") {
    QPS::Argument arg1;
    QPS::Argument arg2{2};
    QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NextStarEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }

  SECTION("Next*(_, 12)") {
    QPS::Argument arg1;
    QPS::Argument arg2{12};
    QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NextStarEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }
}

TEST_CASE("Next Star Evaluator wildcard synonym") {
  QPS::Argument arg1;
  QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>("s")};
  QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<NextStarEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 11);
}

TEST_CASE("Next Star Evaluator wildcard wildcard") {
  QPS::Argument arg1;
  QPS::Argument arg2;
  QPS::NextStarClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<NextStarEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.trueTable());
}
