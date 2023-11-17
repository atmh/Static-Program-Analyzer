#include <memory>
#include <string>
#include <unordered_set>

#include "catch.hpp"
#include "qps/evaluator/such_that_clause_evaluator/CallsStarClauseEvaluator.h"
#include "qps/query/declaration/ProcedureDeclaration.h"
#include "qps/table/NormalizedDataStorage.h"
#include "stubs/pkb/PKBStorageReadAPI.h"

/*
 * Light testing, most such that clause testing already completed in
 * follows relationship
 */

struct CallsStarEvaluatorPKBStub : public PKB::PKBStorageReadStub {
  virtual const std::unordered_set<std::string>& getProcedures()
      const noexcept override {
    return procedures;
  };

  virtual bool hasCallsStarRelationship() override { return true; }

  virtual bool getCallsStarRelationshipExists(
      const std::string& argOne, const std::string& argTwo) override {
    return argOne == "a" && argTwo == "b";
  }

  virtual std::unordered_set<std::string> getCallsStarFirstArgRelationships(
      const std::string& argOne) override {
    if (argOne == "a")
      return {"b"};
    return {};
  }

  virtual std::unordered_set<std::string> getCallsStarSecondArgRelationships(
      const std::string& argTwo) override {
    if (argTwo == "b")
      return {"a"};
    return {};
  }

  std::unordered_set<std::string> procedures{"a", "b"};
};

TEST_CASE("Calls Star Evaluator value value") {
  QPS::Argument arg1{"a"};
  QPS::Argument arg2{"b"};
  QPS::CallsStarClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<CallsStarEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.trueTable());
}

TEST_CASE("Calls Star Evaluator value synonym") {
  QPS::Argument arg1{"a"};
  QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>("p")};
  QPS::CallsStarClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<CallsStarEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 1);
}

TEST_CASE("Calls Star Evaluator value wildcard") {
  QPS::Argument arg1{"a"};
  QPS::Argument arg2;
  QPS::CallsStarClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<CallsStarEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.trueTable());
}

TEST_CASE("Calls Star Evaluator synonym value") {
  QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>("p")};
  QPS::Argument arg2{"b"};
  QPS::CallsStarClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<CallsStarEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 1);
}

TEST_CASE("Calls Star Evaluator synonym synonym") {
  QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>("p1")};
  QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>("p2")};
  QPS::CallsStarClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<CallsStarEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 1);
}

TEST_CASE("Calls Star Evaluator synonym wildcard") {
  QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>("p")};
  QPS::Argument arg2;
  QPS::CallsStarClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<CallsStarEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 1);
}

TEST_CASE("Calls Star Evaluator wildcard value") {
  QPS::Argument arg1;
  QPS::Argument arg2{"b"};
  QPS::CallsStarClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<CallsStarEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.trueTable());
}

TEST_CASE("Calls Star Evaluator wildcard synonym") {
  QPS::Argument arg1;
  QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>("p")};
  QPS::CallsStarClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<CallsStarEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 1);
}

TEST_CASE("Calls Star Evaluator wildcard wildcard") {
  QPS::Argument arg1;
  QPS::Argument arg2;
  QPS::CallsStarClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<CallsStarEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.trueTable());
}
