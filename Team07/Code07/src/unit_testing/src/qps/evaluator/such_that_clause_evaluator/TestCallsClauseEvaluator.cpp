#include <memory>
#include <string>
#include <unordered_set>

#include "catch.hpp"
#include "qps/evaluator/such_that_clause_evaluator/CallsClauseEvaluator.h"
#include "qps/query/declaration/ProcedureDeclaration.h"
#include "qps/table/NormalizedDataStorage.h"
#include "stubs/pkb/PKBStorageReadAPI.h"

/*
 * Light testing, most such that clause testing already completed in
 * follows relationship
 */

struct CallsEvaluatorPKBStub : public PKB::PKBStorageReadStub {
  virtual const std::unordered_set<std::string>& getProcedures()
      const noexcept override {
    return procedures;
  };

  virtual bool hasCallsRelationship() { return true; }

  virtual bool getCallsRelationshipExists(const std::string& argOne,
                                          const std::string& argTwo) {
    return argOne == "a" && argTwo == "b";
  }

  virtual std::unordered_set<std::string> getCallsFirstArgRelationships(
      const std::string& argOne) {
    if (argOne == "a")
      return {"b"};
    return {};
  }

  virtual std::unordered_set<std::string> getCallsSecondArgRelationships(
      const std::string& argTwo) {
    if (argTwo == "b")
      return {"a"};
    return {};
  }

  std::unordered_set<std::string> procedures{"a", "b"};
};

TEST_CASE("Calls Evaluator value value") {
  QPS::Argument arg1{"a"};
  QPS::Argument arg2{"b"};
  QPS::CallsClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<CallsEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.trueTable());
}

TEST_CASE("Calls Evaluator value synonym") {
  QPS::Argument arg1{"a"};
  QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>("p")};
  QPS::CallsClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<CallsEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 1);
}

TEST_CASE("Calls Evaluator value wildcard") {
  QPS::Argument arg1{"a"};
  QPS::Argument arg2;
  QPS::CallsClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<CallsEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.trueTable());
}

TEST_CASE("Calls Evaluator synonym value") {
  QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>("p")};
  QPS::Argument arg2{"b"};
  QPS::CallsClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<CallsEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 1);
}

TEST_CASE("Calls Evaluator synonym synonym") {
  QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>("p1")};
  QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>("p2")};
  QPS::CallsClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<CallsEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 1);
}

TEST_CASE("Calls Evaluator synonym wildcard") {
  QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>("p")};
  QPS::Argument arg2;
  QPS::CallsClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<CallsEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 1);
}

TEST_CASE("Calls Evaluator wildcard value") {
  QPS::Argument arg1;
  QPS::Argument arg2{"b"};
  QPS::CallsClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<CallsEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.trueTable());
}

TEST_CASE("Calls Evaluator wildcard synonym") {
  QPS::Argument arg1;
  QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>("p")};
  QPS::CallsClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<CallsEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 1);
}

TEST_CASE("Calls Evaluator wildcard wildcard") {
  QPS::Argument arg1;
  QPS::Argument arg2;
  QPS::CallsClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<CallsEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.trueTable());
}
