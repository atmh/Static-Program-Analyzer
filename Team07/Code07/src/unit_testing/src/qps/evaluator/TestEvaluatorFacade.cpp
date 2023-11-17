#include <algorithm>
#include <list>
#include <memory>
#include <string>
#include <unordered_set>

#include "catch.hpp"
#include "qps/evaluator/EvaluatorFacade.h"
#include "qps/query/Query.h"
#include "qps/query/declaration/AssignDeclaration.h"
#include "qps/query/declaration/CallDeclaration.h"
#include "qps/query/declaration/ConstantDeclaration.h"
#include "qps/query/declaration/IfDeclaration.h"
#include "qps/query/declaration/PrintDeclaration.h"
#include "qps/query/declaration/ProcedureDeclaration.h"
#include "qps/query/declaration/ReadDeclaration.h"
#include "qps/query/declaration/StatementDeclaration.h"
#include "qps/query/declaration/VariableDeclaration.h"
#include "qps/query/declaration/WhileDeclaration.h"
#include "qps/query/select/SelectClause.h"
#include "stubs/pkb/PKBStorageReadAPI.h"

namespace {

template <typename DeclarationType, typename StmtLstType,
          typename MemFuncPtrType, typename FunctorType>
void testIntDeclarations(const StmtLstType& stmt_lst,
                         MemFuncPtrType mem_fun_ptr, FunctorType functor) {
  QPS::EvaluatorFacade evaluator;
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb =
      std::make_shared<PKB::PKBStorageReadStub>();
  (static_cast<PKB::PKBStorageReadStub*>(pkb.get())->*mem_fun_ptr)(stmt_lst);

  std::unique_ptr<QPS::Declaration> declaration =
      std::make_unique<DeclarationType>("s");
  QPS::SelectClause sc({std::move(declaration)});
  QPS::Query query{std::move(sc)};

  std::list<std::string> res = evaluator.evaluate(pkb, query);

  std::vector<std::string> stmt_lst_str;
  std::transform(stmt_lst.begin(), stmt_lst.end(),
                 std::back_inserter(stmt_lst_str), functor);
  REQUIRE(res.size() == stmt_lst.size());
  REQUIRE(std::unordered_set<std::string>{res.begin(), res.end()} ==
          std::unordered_set<std::string>{stmt_lst_str.begin(),
                                          stmt_lst_str.end()});
}

}  // namespace

TEST_CASE("assign a; select a - 1") {
  std::vector<int> stmtLst{3, 1, 4, 5, 2};
  auto functor = [](auto x) {
    return std::to_string(x);
  };
  testIntDeclarations<QPS::AssignDeclaration>(
      stmtLst, &PKB::PKBStorageReadStub::withAssigns, functor);
}

TEST_CASE("call c; select c - 1") {
  std::vector<int> stmtLst{3, 1, 4, 5, 2};
  auto functor = [](auto x) {
    return std::to_string(x);
  };
  testIntDeclarations<QPS::CallDeclaration>(
      stmtLst, &PKB::PKBStorageReadStub::withCalls, functor);
}

TEST_CASE("constant c; select c - 1") {
  std::vector<std::string> stmtLst{"3", "1", "4", "5", "2"};
  auto functor = [](auto x) {
    return x;
  };
  testIntDeclarations<QPS::ConstantDeclaration>(
      stmtLst, &PKB::PKBStorageReadStub::withConstants, functor);
}

TEST_CASE("if i; select i - 1") {
  std::vector<int> stmtLst{3, 1, 4, 5, 2};
  auto functor = [](auto x) {
    return std::to_string(x);
  };
  testIntDeclarations<QPS::IfDeclaration>(
      stmtLst, &PKB::PKBStorageReadStub::withIfs, functor);
}

TEST_CASE("print p; select p - 1") {
  std::vector<int> stmtLst{3, 1, 4, 5, 2};
  auto functor = [](auto x) {
    return std::to_string(x);
  };
  testIntDeclarations<QPS::PrintDeclaration>(
      stmtLst, &PKB::PKBStorageReadStub::withPrints, functor);
}

TEST_CASE("procedure p; select p - 1") {
  std::vector<std::string> stmtLst{"I", "am", "a", "cute", "kitty", "MEOWWWW"};
  auto functor = [](auto x) {
    return x;
  };
  testIntDeclarations<QPS::ProcedureDeclaration>(
      stmtLst, &PKB::PKBStorageReadStub::withProcedures, functor);
}

TEST_CASE("read r; select r - 1") {
  std::vector<int> stmtLst{3, 1, 4, 5, 2};
  auto functor = [](auto x) {
    return std::to_string(x);
  };
  testIntDeclarations<QPS::ReadDeclaration>(
      stmtLst, &PKB::PKBStorageReadStub::withReads, functor);
}

TEST_CASE("stmt s; select s - 1") {
  std::vector<int> stmtLst{3, 1, 4, 5, 2};
  auto functor = [](auto x) {
    return std::to_string(x);
  };
  testIntDeclarations<QPS::StatementDeclaration>(
      stmtLst, &PKB::PKBStorageReadStub::withStmts, functor);
}

TEST_CASE("variable v; select v - 1") {
  QPS::EvaluatorFacade evaluator;
  std::vector<std::string> var_lst{"MyVar"};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb =
      std::make_shared<PKB::PKBStorageReadStub>();
  static_cast<PKB::PKBStorageReadStub*>(pkb.get())->withVariables(var_lst);

  std::unique_ptr<QPS::Declaration> declaration =
      std::make_unique<QPS::VariableDeclaration>("v");
  QPS::SelectClause sc({std::move(declaration)});
  QPS::Query query{std::move(sc)};

  std::list<std::string> res = evaluator.evaluate(pkb, query);

  REQUIRE(res.size() == 1);
  REQUIRE(res.front() == var_lst.front());
}

TEST_CASE("variable v; select v - 2") {
  QPS::EvaluatorFacade evaluator;
  std::vector<std::string> var_lst{"MyVar1", "MyVar2", "MyVar3"};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb =
      std::make_shared<PKB::PKBStorageReadStub>();
  static_cast<PKB::PKBStorageReadStub*>(pkb.get())->withVariables(var_lst);

  std::unique_ptr<QPS::Declaration> declaration =
      std::make_unique<QPS::VariableDeclaration>("v");
  QPS::SelectClause sc({std::move(declaration)});
  QPS::Query query{std::move(sc)};

  std::list<std::string> res = evaluator.evaluate(pkb, query);

  REQUIRE(res.size() == var_lst.size());
  REQUIRE(std::unordered_set<std::string>{res.begin(), res.end()} ==
          std::unordered_set<std::string>{var_lst.begin(), var_lst.end()});
}

TEST_CASE("while w; select w - 1") {
  std::vector<int> stmtLst{3, 1, 4, 5, 2};
  auto functor = [](auto x) {
    return std::to_string(x);
  };
  testIntDeclarations<QPS::WhileDeclaration>(
      stmtLst, &PKB::PKBStorageReadStub::withWhiles, functor);
}

TEST_CASE("boolean select") {
  QPS::SelectClause sc;
  QPS::Query query{sc};
  QPS::EvaluatorFacade evaluatorFacade;
  std::shared_ptr<PKB::PKBStorageReadStub> pkb =
      std::make_shared<PKB::PKBStorageReadStub>();
  REQUIRE(std::list<std::string>(evaluatorFacade.evaluate(pkb, query)) ==
          std::list<std::string>{"TRUE"});
}
