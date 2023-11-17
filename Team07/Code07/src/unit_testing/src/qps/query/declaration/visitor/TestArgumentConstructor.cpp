#include <memory>

#include "catch.hpp"
#include "qps/query/clauses/Argument.h"
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
#include "qps/query/declaration/visitor/ArgumentConstructor.h"
#include "qps/table/NormalizedDataStorage.h"
#include "stubs/pkb/PKBStorageReadAPI.h"

TEST_CASE("Argument constructor") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }

    virtual const std::unordered_set<int>& getCalls() const noexcept {
      return calls;
    }

    virtual const std::unordered_set<std::string>& getConstants()
        const noexcept {
      return constants;
    }

    virtual const std::unordered_set<int>& getIfs() const noexcept {
      return ifs;
    };

    virtual const std::unordered_set<int>& getPrints() const noexcept {
      return prints;
    }

    virtual const std::unordered_set<std::string>& getProcedures()
        const noexcept {
      return procedures;
    }

    virtual const std::unordered_set<int>& getReads() const noexcept {
      return reads;
    }

    virtual const std::unordered_set<int>& getStmts() const noexcept {
      return stmts;
    }

    virtual const std::unordered_set<std::string>& getVariables()
        const noexcept {
      return variables;
    }

    virtual const std::unordered_set<int>& getWhiles() const noexcept {
      return whiles;
    }

    std::unordered_set<int> assigns{1};
    std::unordered_set<int> calls{2};
    std::unordered_set<std::string> constants{"3"};
    std::unordered_set<int> ifs{4};
    std::unordered_set<int> prints{5};
    std::unordered_set<std::string> procedures{"6"};
    std::unordered_set<int> reads{7};
    std::unordered_set<int> stmts{1, 2, 4, 5, 7, 9};
    std::unordered_set<std::string> variables{"8"};
    std::unordered_set<int> whiles{9};
  };

  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage =
      std::make_shared<QPS::NormalizedDataStorage>();
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb =
      std::make_shared<TestStub>();

  SECTION("Assign") {
    int assignId = dataStorage->encodeInt(*pkb->getAssigns().begin());
    QPS::ArgumentConstructor constructor{assignId, dataStorage};
    QPS::AssignDeclaration decl{"a"};
    decl.accept(constructor);
    REQUIRE(QPS::Argument{constructor} == QPS::Argument(1));
  }

  SECTION("Calls") {
    int callId = dataStorage->encodeInt(*pkb->getCalls().begin());
    QPS::ArgumentConstructor constructor{callId, dataStorage};
    QPS::CallDeclaration decl{"a"};
    decl.accept(constructor);
    REQUIRE(QPS::Argument{constructor} == QPS::Argument(2));
  }

  SECTION("Constant") {
    int constantId = dataStorage->encodeString(*pkb->getConstants().begin());
    QPS::ArgumentConstructor constructor{constantId, dataStorage};
    QPS::ConstantDeclaration decl{"a"};
    decl.accept(constructor);
    REQUIRE(QPS::Argument{constructor} == QPS::Argument("3"));
  }

  SECTION("If") {
    int ifId = dataStorage->encodeInt(*pkb->getIfs().begin());
    QPS::ArgumentConstructor constructor{ifId, dataStorage};
    QPS::IfDeclaration decl{"a"};
    decl.accept(constructor);
    REQUIRE(QPS::Argument{constructor} == QPS::Argument(4));
  }

  SECTION("Print") {
    int printId = dataStorage->encodeInt(*pkb->getPrints().begin());
    QPS::ArgumentConstructor constructor{printId, dataStorage};
    QPS::PrintDeclaration decl{"a"};
    decl.accept(constructor);
    REQUIRE(QPS::Argument{constructor} == QPS::Argument(5));
  }

  SECTION("Procedure") {
    int procedureId = dataStorage->encodeString(*pkb->getProcedures().begin());
    QPS::ArgumentConstructor constructor{procedureId, dataStorage};
    QPS::ProcedureDeclaration decl{"a"};
    decl.accept(constructor);
    REQUIRE(QPS::Argument{constructor} == QPS::Argument("6"));
  }

  SECTION("Read") {
    int readId = dataStorage->encodeInt(*pkb->getReads().begin());
    QPS::ArgumentConstructor constructor{readId, dataStorage};
    QPS::ReadDeclaration decl{"a"};
    decl.accept(constructor);
    REQUIRE(QPS::Argument{constructor} == QPS::Argument(7));
  }

  SECTION("Stmt") {
    int stmtId = dataStorage->encodeInt(*pkb->getStmts().begin());
    QPS::ArgumentConstructor constructor{stmtId, dataStorage};
    QPS::StatementDeclaration decl{"a"};
    decl.accept(constructor);
    REQUIRE(QPS::Argument{constructor} ==
            QPS::Argument(*pkb->getStmts().begin()));
  }

  SECTION("Variable") {
    int variableId = dataStorage->encodeString(*pkb->getVariables().begin());
    QPS::ArgumentConstructor constructor{variableId, dataStorage};
    QPS::VariableDeclaration decl{"a"};
    decl.accept(constructor);
    REQUIRE(QPS::Argument{constructor} == QPS::Argument("8"));
  }

  SECTION("While") {
    int whileId = dataStorage->encodeInt(*pkb->getWhiles().begin());
    QPS::ArgumentConstructor constructor{whileId, dataStorage};
    QPS::WhileDeclaration decl{"a"};
    decl.accept(constructor);
    REQUIRE(QPS::Argument{constructor} == QPS::Argument(9));
  }
}
