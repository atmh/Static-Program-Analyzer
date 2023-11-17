#include <memory>
#include <unordered_set>

#include "catch.hpp"
#include "qps/evaluator/such_that_clause_evaluator/NextClauseEvaluator.h"
#include "qps/query/declaration/StatementDeclaration.h"
#include "qps/table/NormalizedDataStorage.h"
#include "stubs/pkb/PKBStorageReadAPI.h"

/*
 * Light testing, most such that clause testing already completed in
 * follows relationship
 */

struct NextEvaluatorPKBStub : public PKB::PKBStorageReadStub {
  virtual const std::unordered_set<int>& getStmts() const noexcept override {
    return stmts;
  };

  virtual bool hasNextRelationship() override { return true; }

  virtual bool getNextRelationshipExists(int argOne, int argTwo) override {
    return argOne == 1 && argTwo == 2;
  }

  std::unordered_set<int> getNextFirstArgRelationships(int argOne) override {
    if (argOne == 1)
      return {2};
    return {};
  }

  std::unordered_set<int> getNextSecondArgRelationships(int argTwo) override {
    if (argTwo == 2)
      return {1};
    return {};
  }

  std::unordered_set<int> stmts{1, 2};
};

TEST_CASE("Next Evaluator value value") {
  QPS::Argument arg1{1};
  QPS::Argument arg2{2};
  QPS::NextClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<NextEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.trueTable());
}

TEST_CASE("Next Evaluator value synonym") {
  QPS::Argument arg1{1};
  QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>("s")};
  QPS::NextClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<NextEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 1);
}

TEST_CASE("Next Evaluator value wildcard") {
  QPS::Argument arg1{1};
  QPS::Argument arg2;
  QPS::NextClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<NextEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.trueTable());
}

TEST_CASE("Next Evaluator synonym value") {
  QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>("s")};
  QPS::Argument arg2{2};
  QPS::NextClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<NextEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 1);
}

TEST_CASE("Next Evaluator synonym synonym") {
  QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>("s1")};
  QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>("s2")};
  QPS::NextClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<NextEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 1);
}

TEST_CASE("Next Evaluator synonym wildcard") {
  QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>("s")};
  QPS::Argument arg2;
  QPS::NextClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<NextEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 1);
}

TEST_CASE("Next Evaluator wildcard value") {
  QPS::Argument arg1;
  QPS::Argument arg2{2};
  QPS::NextClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<NextEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.trueTable());
}

TEST_CASE("Next Evaluator wildcard synonym") {
  QPS::Argument arg1;
  QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>("s")};
  QPS::NextClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<NextEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 1);
}

TEST_CASE("Next Evaluator wildcard wildcard") {
  QPS::Argument arg1;
  QPS::Argument arg2;
  QPS::NextClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<NextEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.trueTable());
}
