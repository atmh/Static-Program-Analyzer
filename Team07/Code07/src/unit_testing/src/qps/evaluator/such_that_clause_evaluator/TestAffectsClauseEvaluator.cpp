#include <memory>
#include <unordered_set>

#include "catch.hpp"
#include "qps/evaluator/such_that_clause_evaluator/AffectsClauseEvaluator.h"
#include "qps/query/declaration/StatementDeclaration.h"
#include "qps/table/NormalizedDataStorage.h"
#include "stubs/pkb/PKBStorageReadAPI.h"

/*
 * Light testing, most such that clause testing already completed in
 * follows relationship
 */

// follows this cfg here
// https://nus-cs3203.github.io/course-website/contents/advanced-spa-requirements/cfg.html

struct AffectsEvaluatorPKBStub : public PKB::PKBStorageReadStub {
  virtual const std::unordered_set<int>& getAssigns() const noexcept override {
    return assigns;
  };

  virtual const std::unordered_set<int>& getReads() const noexcept override {
    return reads;
  };

  virtual const std::unordered_set<int>& getCalls() const noexcept override {
    return calls;
  };

  virtual const std::unordered_set<int>& getStmts() const noexcept override {
    return stmts;
  };

  virtual bool getModifiesStatementRelationshipExists(
      const int& argOne, const std::string& argTwo) override {
    const auto pt = modifiedMap.find(argOne);
    if (pt == modifiedMap.end())
      return false;
    return pt->second.find(argTwo) != pt->second.end();
  }

  virtual bool getUsesStatementRelationshipExists(
      int argOne, const std::string& argTwo) override {
    const auto pt = usesMap.find(argOne);
    if (pt == usesMap.end())
      return false;
    return pt->second.find(argTwo) != pt->second.end();
  }

  virtual std::unordered_set<std::string>
  getModifiesStatementFirstArgRelationships(const int& argOne) override {
    const auto pt = modifiedMap.find(argOne);
    if (pt == modifiedMap.end())
      return {};
    return pt->second;
  }

  virtual std::unordered_set<std::string> getUsesStatementFirstArgRelationships(
      int argOne) override {
    const auto pt = usesMap.find(argOne);
    if (pt == usesMap.end())
      return {};
    return pt->second;
  }

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

  std::unordered_set<int> assigns{1, 2, 4, 6, 8, 9, 10, 11, 12};
  std::unordered_set<int> reads{};
  std::unordered_set<int> calls = {5};
  std::unordered_set<int> stmts{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

  std::unordered_map<int, std::unordered_set<std::string>> modifiedMap = {
      {1, {"x"}},
      {2, {"i"}},
      {
          3,
          {"i", "v", "x", "z"},
      },
      {4, {"x"}},
      {5, {"v", "z"}},
      {6, {"i"}},
      {7, {"x", "z"}},
      {8, {"x"}},
      {9, {"z"}},
      {10, {"z"}},
      {11, {"y"}},
      {12, {"x"}}};

  std::unordered_map<int, std::unordered_set<std::string>> usesMap = {
      {3, {"i", "v", "x", "y", "z"}},
      {4, {"x", "y"}},
      {5, {"v", "z"}},
      {6, {"i"}},
      {7, {"x"}},
      {8, {"x"}},
      {10, {"i", "x", "z"}},
      {11, {"z"}},
      {12, {"x", "y", "z"}}};
};

TEST_CASE("Affects Evaluator value value") {
  SECTION("1 - 4") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{4};
    QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<AffectsEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }

  SECTION("1 - 10") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{10};
    QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<AffectsEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }

  SECTION("6 - 6") {
    QPS::Argument arg1{6};
    QPS::Argument arg2{6};
    QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<AffectsEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }

  SECTION("4 - 10") {
    QPS::Argument arg1{4};
    QPS::Argument arg2{10};
    QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<AffectsEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }

  SECTION("6 - 2") {
    QPS::Argument arg1{6};
    QPS::Argument arg2{2};
    QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<AffectsEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(table.empty());
    REQUIRE(!table.trueTable());
  }

  SECTION("9 - 11") {
    QPS::Argument arg1{9};
    QPS::Argument arg2{11};
    QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<AffectsEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(table.empty());
    REQUIRE(!table.trueTable());
  }
}

TEST_CASE("Affects Evaluator value synonym") {
  SECTION("Affects(1, s)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>("s")};
    QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<AffectsEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.size() == 4);
  }

  SECTION("Affects(4, s)") {
    QPS::Argument arg1{4};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>("s")};
    QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<AffectsEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.size() == 4);
  }

  SECTION("Affects(6, s)") {
    QPS::Argument arg1{6};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>("s")};
    QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<AffectsEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.size() == 2);
  }

  SECTION("Affects(9, s)") {
    QPS::Argument arg1{9};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>("s")};
    QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<AffectsEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
  }

  SECTION("Affects(3, s)") {
    QPS::Argument arg1{3};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>("s")};
    QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<AffectsEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(table.empty());
    REQUIRE(!table.trueTable());
  }
}

TEST_CASE("Affects Evaluator value wildcard") {
  SECTION("Affects(1, _)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2;
    QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<AffectsEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }

  SECTION("Affects(12, _)") {
    QPS::Argument arg1{12};
    QPS::Argument arg2;
    QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<AffectsEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(table.empty());
    REQUIRE(!table.trueTable());
  }
}

TEST_CASE("Affects Evaluator synonym value") {
  SECTION("Affects(s, 6)") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>("s")};
    QPS::Argument arg2{6};
    QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<AffectsEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.size() == 2);
  }

  SECTION("Affects(s, 10)") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>("s")};
    QPS::Argument arg2{10};
    QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<AffectsEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.size() == 6);
  }
}

TEST_CASE("Affects synonym synonym") {
  QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>("s1")};
  QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>("s2")};
  QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<AffectsEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 18);
}

TEST_CASE("Affects synonym wildcard") {
  QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>("s")};
  QPS::Argument arg2;
  QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<AffectsEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 8);
}

TEST_CASE("Affects Evaluator wildcard value") {
  SECTION("Affects(_, 1)") {
    QPS::Argument arg1;
    QPS::Argument arg2{1};
    QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<AffectsEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(table.empty());
    REQUIRE(!table.trueTable());
  }

  SECTION("Affects(_, 10)") {
    QPS::Argument arg1;
    QPS::Argument arg2{10};
    QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<AffectsEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }

  SECTION("Affects(_, 12)") {
    QPS::Argument arg1;
    QPS::Argument arg2{12};
    QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<AffectsEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }
}

TEST_CASE("Affects Evaluator wildcard synonym") {
  QPS::Argument arg1;
  QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>("s")};
  QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<AffectsEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 6);
}

TEST_CASE("Affects Evaluator wildcard wildcard") {
  QPS::Argument arg1;
  QPS::Argument arg2;
  QPS::AffectsClauseEvaluator evaluator{arg1, arg2};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<AffectsEvaluatorPKBStub>()};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.trueTable());
}
