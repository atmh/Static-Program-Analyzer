#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "catch.hpp"
#include "qps/evaluator/such_that_clause_evaluator/ModifiesClauseEvaluator.h"
#include "qps/query/clauses/Argument.h"
#include "qps/query/declaration/Declaration.h"
#include "qps/table/NormalizedDataStorage.h"
#include "stubs/pkb/PKBStorageReadAPI.h"

TEST_CASE("Modifies clause evaluator - stmt synonym & wildcard") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual std::unordered_set<std::string>
    getModifiesStatementFirstArgRelationships(const int& argOne) override {
      return {"v1"};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureFirstArgRelationships(
        const std::string& argOne) override {
      return {"v2"};
    }
    virtual std::unordered_set<int> getModifiesStatementSecondArgRelationships(
        const std::string& argTwo) override {
      return {3, 4};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureSecondArgRelationships(
        const std::string& argTwo) override {
      return {"proc"};
    }

    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }

    std::unordered_set<int> assigns{3};
  };

  SECTION("Test 1") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::Argument wildcard;
    QPS::ModifiesClauseEvaluator evaluator(a, wildcard);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
    REQUIRE(table.colSize() == 1);
  }
}

TEST_CASE("Modifies clause evaluator - stmt synonym & synonym") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual std::unordered_set<std::string>
    getModifiesStatementFirstArgRelationships(const int& argOne) override {
      return {"v1"};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureFirstArgRelationships(
        const std::string& argOne) override {
      return {"v2"};
    }
    virtual std::unordered_set<int> getModifiesStatementSecondArgRelationships(
        const std::string& argTwo) override {
      return {3};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureSecondArgRelationships(
        const std::string& argTwo) override {
      return {"proc"};
    }

    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }

    virtual const std::unordered_set<std::string>& getVariables()
        const noexcept override {
      return variables;
    }

    std::unordered_set<int> assigns{3};
    std::unordered_set<std::string> variables{"v1", "v2"};
  };

  SECTION("Test 1") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    std::shared_ptr<QPS::Declaration> v =
        std::make_shared<QPS::VariableDeclaration>("v");
    QPS::ModifiesClauseEvaluator evaluator(a, v);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
    REQUIRE(table.colSize() == 2);
  }
}

TEST_CASE("Modifies clause evaluator - stmt synonym & variable") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual std::unordered_set<std::string>
    getModifiesStatementFirstArgRelationships(const int& argOne) override {
      return {"v1"};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureFirstArgRelationships(
        const std::string& argOne) override {
      return {"v2"};
    }
    virtual std::unordered_set<int> getModifiesStatementSecondArgRelationships(
        const std::string& argTwo) override {
      return {3};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureSecondArgRelationships(
        const std::string& argTwo) override {
      return {"proc"};
    }

    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }

    virtual const std::unordered_set<std::string>& getVariables()
        const noexcept override {
      return variables;
    }

    std::unordered_set<int> assigns{3};
    std::unordered_set<std::string> variables{"v1", "v2"};
  };

  SECTION("Test 1") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::Argument var{std::string("v1")};
    QPS::ModifiesClauseEvaluator evaluator(a, var);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
    REQUIRE(table.colSize() == 1);
  }
}

TEST_CASE("Modifies clause evaluator - procedure synonym & wildcard") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual std::unordered_set<std::string>
    getModifiesStatementFirstArgRelationships(const int& argOne) override {
      return {"v1"};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureFirstArgRelationships(
        const std::string& argOne) override {
      return {"v2"};
    }
    virtual std::unordered_set<int> getModifiesStatementSecondArgRelationships(
        const std::string& argTwo) override {
      return {3};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureSecondArgRelationships(
        const std::string& argTwo) override {
      return {"proc"};
    }

    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }

    virtual const std::unordered_set<std::string>& getVariables()
        const noexcept override {
      return variables;
    }

    virtual const std::unordered_set<std::string>& getProcedures()
        const noexcept override {
      return procedures;
    }

    std::unordered_set<int> assigns{3};
    std::unordered_set<std::string> variables{"v1", "v2"};
    std::unordered_set<std::string> procedures{"proc"};
  };

  SECTION("Test 1") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::ProcedureDeclaration>("proc");
    QPS::Argument wildcard;
    QPS::ModifiesClauseEvaluator evaluator(a, wildcard);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
    REQUIRE(table.colSize() == 1);
  }
}

TEST_CASE("Modifies clause evaluator - procedure synonym & synonym") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual std::unordered_set<std::string>
    getModifiesStatementFirstArgRelationships(const int& argOne) override {
      return {"v1"};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureFirstArgRelationships(
        const std::string& argOne) override {
      return {"v2"};
    }
    virtual std::unordered_set<int> getModifiesStatementSecondArgRelationships(
        const std::string& argTwo) override {
      return {3};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureSecondArgRelationships(
        const std::string& argTwo) override {
      return {"proc"};
    }

    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }

    virtual const std::unordered_set<std::string>& getVariables()
        const noexcept override {
      return variables;
    }

    virtual const std::unordered_set<std::string>& getProcedures()
        const noexcept override {
      return procedures;
    }

    std::unordered_set<int> assigns{3};
    std::unordered_set<std::string> variables{"v1", "v2"};
    std::unordered_set<std::string> procedures{"proc"};
  };

  SECTION("Test 1") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::ProcedureDeclaration>("proc");
    std::shared_ptr<QPS::Declaration> v =
        std::make_shared<QPS::VariableDeclaration>("v");
    QPS::ModifiesClauseEvaluator evaluator(a, v);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
    REQUIRE(table.colSize() == 2);
  }
}

TEST_CASE("Modifies clause evaluator - procedure synonym & variable") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual std::unordered_set<std::string>
    getModifiesStatementFirstArgRelationships(const int& argOne) override {
      return {"v1"};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureFirstArgRelationships(
        const std::string& argOne) override {
      return {"v2"};
    }
    virtual std::unordered_set<int> getModifiesStatementSecondArgRelationships(
        const std::string& argTwo) override {
      return {3};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureSecondArgRelationships(
        const std::string& argTwo) override {
      return {"proc"};
    }

    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }

    virtual const std::unordered_set<std::string>& getVariables()
        const noexcept override {
      return variables;
    }

    virtual const std::unordered_set<std::string>& getProcedures()
        const noexcept override {
      return procedures;
    }

    std::unordered_set<int> assigns{3};
    std::unordered_set<std::string> variables{"v1", "v2"};
    std::unordered_set<std::string> procedures{"proc"};
  };

  SECTION("Test 1") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::ProcedureDeclaration>("proc");
    QPS::Argument v = std::string("v");
    QPS::ModifiesClauseEvaluator evaluator(a, v);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
    REQUIRE(table.colSize() == 1);
  }
}

TEST_CASE("Modifies clause evaluator - stmt value & wildcard") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual std::unordered_set<std::string>
    getModifiesStatementFirstArgRelationships(const int& argOne) override {
      return {"v1"};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureFirstArgRelationships(
        const std::string& argOne) override {
      return {"v2"};
    }
    virtual std::unordered_set<int> getModifiesStatementSecondArgRelationships(
        const std::string& argTwo) override {
      return {3};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureSecondArgRelationships(
        const std::string& argTwo) override {
      return {"proc"};
    }

    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }

    virtual const std::unordered_set<std::string>& getVariables()
        const noexcept override {
      return variables;
    }

    virtual const std::unordered_set<std::string>& getProcedures()
        const noexcept override {
      return procedures;
    }

    std::unordered_set<int> assigns{3};
    std::unordered_set<std::string> variables{"v1", "v2"};
    std::unordered_set<std::string> procedures{"proc"};
  };

  SECTION("Test 1") {
    QPS::Argument wildcard;
    QPS::ModifiesClauseEvaluator evaluator(1, wildcard);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }
}

TEST_CASE("Modifies clause evaluator - stmt value & synonym") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual std::unordered_set<std::string>
    getModifiesStatementFirstArgRelationships(const int& argOne) override {
      return {"v1"};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureFirstArgRelationships(
        const std::string& argOne) override {
      return {"v2"};
    }
    virtual std::unordered_set<int> getModifiesStatementSecondArgRelationships(
        const std::string& argTwo) override {
      return {3};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureSecondArgRelationships(
        const std::string& argTwo) override {
      return {"proc"};
    }

    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }

    virtual const std::unordered_set<std::string>& getVariables()
        const noexcept override {
      return variables;
    }

    virtual const std::unordered_set<std::string>& getProcedures()
        const noexcept override {
      return procedures;
    }

    std::unordered_set<int> assigns{3};
    std::unordered_set<std::string> variables{"v1", "v2"};
    std::unordered_set<std::string> procedures{"proc"};
  };

  SECTION("Test 1") {
    std::shared_ptr<QPS::Declaration> v =
        std::make_shared<QPS::VariableDeclaration>("v");
    QPS::ModifiesClauseEvaluator evaluator(1, v);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
    REQUIRE(table.colSize() == 1);
  }
}

TEST_CASE("Modifies clause evaluator - stmt value & variable") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual std::unordered_set<std::string>
    getModifiesStatementFirstArgRelationships(const int& argOne) override {
      return {"v1"};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureFirstArgRelationships(
        const std::string& argOne) override {
      return {"v2"};
    }
    virtual std::unordered_set<int> getModifiesStatementSecondArgRelationships(
        const std::string& argTwo) override {
      return {3};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureSecondArgRelationships(
        const std::string& argTwo) override {
      return {"proc"};
    }

    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }

    virtual const std::unordered_set<std::string>& getVariables()
        const noexcept override {
      return variables;
    }

    virtual const std::unordered_set<std::string>& getProcedures()
        const noexcept override {
      return procedures;
    }

    std::unordered_set<int> assigns{3};
    std::unordered_set<std::string> variables{"v1", "v2"};
    std::unordered_set<std::string> procedures{"proc"};
  };

  SECTION("Test 1") {
    QPS::Argument v = std::string("v");
    QPS::ModifiesClauseEvaluator evaluator(1, v);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }
}

TEST_CASE("Modifies clause evaluator - procedure value & wildcard") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual std::unordered_set<std::string>
    getModifiesStatementFirstArgRelationships(const int& argOne) override {
      return {"v1"};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureFirstArgRelationships(
        const std::string& argOne) override {
      return {"v2"};
    }
    virtual std::unordered_set<int> getModifiesStatementSecondArgRelationships(
        const std::string& argTwo) override {
      return {3};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureSecondArgRelationships(
        const std::string& argTwo) override {
      return {"proc"};
    }

    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }

    virtual const std::unordered_set<std::string>& getVariables()
        const noexcept override {
      return variables;
    }

    virtual const std::unordered_set<std::string>& getProcedures()
        const noexcept override {
      return procedures;
    }

    std::unordered_set<int> assigns{3};
    std::unordered_set<std::string> variables{"v1", "v2"};
    std::unordered_set<std::string> procedures{"proc"};
  };

  SECTION("Test 1") {
    QPS::Argument wildcard;
    QPS::Argument val = std::string("v");
    QPS::ModifiesClauseEvaluator evaluator(val, wildcard);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }
}

TEST_CASE("Modifies clause evaluator - procedure value & synonym") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual std::unordered_set<std::string>
    getModifiesStatementFirstArgRelationships(const int& argOne) override {
      return {"v1"};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureFirstArgRelationships(
        const std::string& argOne) override {
      return {"v2"};
    }
    virtual std::unordered_set<int> getModifiesStatementSecondArgRelationships(
        const std::string& argTwo) override {
      return {3};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureSecondArgRelationships(
        const std::string& argTwo) override {
      return {"proc"};
    }

    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }

    virtual const std::unordered_set<std::string>& getVariables()
        const noexcept override {
      return variables;
    }

    virtual const std::unordered_set<std::string>& getProcedures()
        const noexcept override {
      return procedures;
    }

    std::unordered_set<int> assigns{3};
    std::unordered_set<std::string> variables{"v1", "v2"};
    std::unordered_set<std::string> procedures{"proc"};
  };

  SECTION("Test 1") {
    QPS::Argument val = std::string("v");
    std::shared_ptr<QPS::Declaration> var =
        std::make_shared<QPS::VariableDeclaration>("v");
    QPS::ModifiesClauseEvaluator evaluator(val, var);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
  }
}

TEST_CASE("Modifies clause evaluator - procedure value & variable") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual std::unordered_set<std::string>
    getModifiesStatementFirstArgRelationships(const int& argOne) override {
      return {"v1"};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureFirstArgRelationships(
        const std::string& argOne) override {
      return {"v2"};
    }
    virtual std::unordered_set<int> getModifiesStatementSecondArgRelationships(
        const std::string& argTwo) override {
      return {3};
    }
    virtual std::unordered_set<std::string>
    getModifiesProcedureSecondArgRelationships(
        const std::string& argTwo) override {
      return {"proc"};
    }

    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }

    virtual const std::unordered_set<std::string>& getVariables()
        const noexcept override {
      return variables;
    }

    virtual const std::unordered_set<std::string>& getProcedures()
        const noexcept override {
      return procedures;
    }

    std::unordered_set<int> assigns{3};
    std::unordered_set<std::string> variables{"v1", "v2"};
    std::unordered_set<std::string> procedures{"proc"};
  };

  SECTION("Test 1") {
    QPS::Argument procVal = std::string("proc");
    QPS::Argument val = std::string("v");
    QPS::ModifiesClauseEvaluator evaluator(procVal, val);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }
}
