#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "catch.hpp"
#include "qps/evaluator/with_evaluator/WithClauseEvaluator.h"
#include "qps/query/clauses/Argument.h"
#include "qps/query/clauses/WithClause.h"
#include "qps/query/declaration/CallDeclaration.h"
#include "qps/query/declaration/Declaration.h"
#include "qps/query/declaration/PrintDeclaration.h"
#include "qps/table/NormalizedDataStorage.h"
#include "stubs/pkb/PKBStorageReadAPI.h"

namespace {

struct WithClausePKBStub : PKB::PKBStorageReadStub {
  virtual const std::unordered_set<int>& getCalls() const noexcept override {
    return calls;
  }

  virtual const std::unordered_set<int>& getPrints() const noexcept override {
    return prints;
  }

  const std::string getCallProcName(int stmtNo) const noexcept override {
    if (stmtNo == 1)
      return "x";
    return std::to_string(stmtNo);
  }

  const std::string getPrintVarName(int stmtNo) const noexcept override {
    if (stmtNo == 3 || stmtNo == 6)
      return "x";
    return std::to_string(stmtNo);
  }

  std::unordered_set<int> calls{1, 2, 5};
  std::unordered_set<int> prints{3, 4, 5, 6};
};

}  // namespace

TEST_CASE("With Clause - value value") {
  SECTION("int - true") {
    QPS::Argument arg1 = 1;
    QPS::Argument arg2 = 1;
    QPS::WithClause withClause{arg1, arg2};
    auto evaluator = withClause.createEvaluator();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<WithClausePKBStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator->evaluate(pkb, dataStorage);
    REQUIRE(table.trueTable());
  }

  SECTION("int - false") {
    QPS::Argument arg1 = 1;
    QPS::Argument arg2 = 2;
    QPS::WithClause withClause{arg1, arg2};
    auto evaluator = withClause.createEvaluator();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<WithClausePKBStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator->evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }

  SECTION("string - true") {
    QPS::Argument arg1 = std::string("1");
    QPS::Argument arg2 = std::string("1");
    QPS::WithClause withClause{arg1, arg2};
    auto evaluator = withClause.createEvaluator();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<WithClausePKBStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator->evaluate(pkb, dataStorage);
    REQUIRE(table.trueTable());
  }

  SECTION("string - false") {
    QPS::Argument arg1 = std::string("1");
    QPS::Argument arg2 = std::string("2");
    QPS::WithClause withClause{arg1, arg2};
    auto evaluator = withClause.createEvaluator();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<WithClausePKBStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator->evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }
}

TEST_CASE("With Clause - value synonym") {
  SECTION("int - call") {
    std::shared_ptr<QPS::Declaration> decl =
        std::make_shared<QPS::CallDeclaration>("a");
    QPS::Argument arg1 = 2;
    QPS::Argument arg2 = decl;
    QPS::WithClause withClause{arg1, arg2};
    auto evaluator = withClause.createEvaluator();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<WithClausePKBStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator->evaluate(pkb, dataStorage);

    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {2};
    REQUIRE(table == QPS::Table{m});
  }

  SECTION("int - print") {
    std::shared_ptr<QPS::Declaration> decl =
        std::make_shared<QPS::PrintDeclaration>("a");
    QPS::Argument arg1 = 2;
    QPS::Argument arg2 = decl;
    QPS::WithClause withClause{arg1, arg2};
    auto evaluator = withClause.createEvaluator();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<WithClausePKBStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator->evaluate(pkb, dataStorage);

    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {};
    REQUIRE(table == QPS::Table{m});
    REQUIRE(table.empty());
  }

  SECTION("string - call") {
    std::shared_ptr<QPS::Declaration> decl =
        std::make_shared<QPS::CallDeclaration>("a",
                                               QPS::Declaration::Type::NAME);
    QPS::Argument arg1 = std::string("x");
    QPS::Argument arg2 = decl;
    QPS::WithClause withClause{arg1, arg2};
    auto evaluator = withClause.createEvaluator();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<WithClausePKBStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator->evaluate(pkb, dataStorage);

    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {1};
    REQUIRE(table == QPS::Table{m});
  }

  SECTION("string - print") {
    std::shared_ptr<QPS::Declaration> decl =
        std::make_shared<QPS::PrintDeclaration>("a",
                                                QPS::Declaration::Type::NAME);
    QPS::Argument arg1 = std::string("x");
    QPS::Argument arg2 = decl;
    QPS::WithClause withClause{arg1, arg2};
    auto evaluator = withClause.createEvaluator();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<WithClausePKBStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator->evaluate(pkb, dataStorage);

    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {3, 6};
    REQUIRE(table == QPS::Table{m});
  }
}

TEST_CASE("With Clause - synonym value") {
  SECTION("int - call") {
    std::shared_ptr<QPS::Declaration> decl =
        std::make_shared<QPS::CallDeclaration>("a");
    QPS::Argument arg1 = decl;
    QPS::Argument arg2 = 2;
    QPS::WithClause withClause{arg1, arg2};
    auto evaluator = withClause.createEvaluator();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<WithClausePKBStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator->evaluate(pkb, dataStorage);

    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {2};
    REQUIRE(table == QPS::Table{m});
  }

  SECTION("int - print") {
    std::shared_ptr<QPS::Declaration> decl =
        std::make_shared<QPS::PrintDeclaration>("a");
    QPS::Argument arg1 = decl;
    QPS::Argument arg2 = 2;
    QPS::WithClause withClause{arg1, arg2};
    auto evaluator = withClause.createEvaluator();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<WithClausePKBStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator->evaluate(pkb, dataStorage);

    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {};
    REQUIRE(table == QPS::Table{m});
    REQUIRE(table.empty());
  }

  SECTION("string - call") {
    std::shared_ptr<QPS::Declaration> decl =
        std::make_shared<QPS::CallDeclaration>("a",
                                               QPS::Declaration::Type::NAME);
    QPS::Argument arg1 = decl;
    QPS::Argument arg2 = std::string("x");
    QPS::WithClause withClause{arg1, arg2};
    auto evaluator = withClause.createEvaluator();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<WithClausePKBStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator->evaluate(pkb, dataStorage);

    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {1};
    REQUIRE(table == QPS::Table{m});
  }

  SECTION("string - print") {
    std::shared_ptr<QPS::Declaration> decl =
        std::make_shared<QPS::PrintDeclaration>("a",
                                                QPS::Declaration::Type::NAME);
    QPS::Argument arg1 = decl;
    QPS::Argument arg2 = std::string("x");
    QPS::WithClause withClause{arg1, arg2};
    auto evaluator = withClause.createEvaluator();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<WithClausePKBStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator->evaluate(pkb, dataStorage);

    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {3, 6};
    REQUIRE(table == QPS::Table{m});
  }
}

TEST_CASE("With Clause - synonym synonym") {
  SECTION("int") {
    std::shared_ptr<QPS::Declaration> decl1 =
        std::make_shared<QPS::CallDeclaration>("a",
                                               QPS::Declaration::Type::INTEGER);
    std::shared_ptr<QPS::Declaration> decl2 =
        std::make_shared<QPS::PrintDeclaration>(
            "b", QPS::Declaration::Type::INTEGER);
    QPS::WithClause withClause{decl1, decl2};
    auto evaluator = withClause.createEvaluator();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<WithClausePKBStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator->evaluate(pkb, dataStorage);

    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {5};
    m["b"] = {5};
    REQUIRE(table == QPS::Table{m});
  }

  SECTION("string") {
    std::shared_ptr<QPS::Declaration> decl1 =
        std::make_shared<QPS::CallDeclaration>("a",
                                               QPS::Declaration::Type::NAME);
    std::shared_ptr<QPS::Declaration> decl2 =
        std::make_shared<QPS::PrintDeclaration>("b",
                                                QPS::Declaration::Type::NAME);
    QPS::WithClause withClause{decl1, decl2};
    auto evaluator = withClause.createEvaluator();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<WithClausePKBStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator->evaluate(pkb, dataStorage);

    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {1, 1, 5};
    m["b"] = {3, 6, 5};
    REQUIRE(table == QPS::Table{m});
  }
}
