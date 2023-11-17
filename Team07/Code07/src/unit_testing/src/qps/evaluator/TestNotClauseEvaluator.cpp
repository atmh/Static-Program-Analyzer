#include <iostream>
#include <memory>

#include "catch.hpp"
#include "qps/evaluator/decorator_evaluator/NotClauseEvaluator.h"
#include "qps/query/clauses/NotClause.h"
#include "qps/query/clauses/SuchThatClause.h"
#include "qps/query/declaration/StatementDeclaration.h"
#include "qps/table/NormalizedDataStorage.h"
#include "stubs/pkb/PKBStorageReadAPI.h"

struct NotEvaluatorPKBStub : public PKB::PKBStorageReadStub {
  virtual const std::unordered_set<int>& getStmts() const noexcept override {
    return statements;
  };

  virtual bool hasFollowsRelationship() { return true; }

  virtual bool getFollowsRelationshipExists(int argOne, int argTwo) override {
    return argOne == 1 && argTwo == 2;
  }

  virtual std::unordered_set<int> getFollowsFirstArgRelationships(
      int argOne) override {
    if (argOne == 1)
      return {2};
    return {};
  }

  virtual std::unordered_set<int> getFollowsSecondArgRelationships(
      int argTwo) override {
    if (argTwo == 2)
      return {1};
    return {};
  }

  std::unordered_set<int> statements{1, 2};
};

TEST_CASE("Not evaluation with Follows") {
  SECTION("Test 1") {
    std::shared_ptr<QPS::Declaration> decl1 =
        std::make_shared<QPS::StatementDeclaration>("s1");
    QPS::Argument arg1 = decl1;
    std::shared_ptr<QPS::Declaration> decl2 =
        std::make_shared<QPS::StatementDeclaration>("s2");
    QPS::Argument arg2 = decl2;
    std::shared_ptr<QPS::Clause> followsClause =
        std::make_shared<QPS::SuchThatClause<QPS::FollowsRelationship>>(arg1,
                                                                        arg2);
    QPS::NotClauseEvaluator notEvaluator(followsClause,
                                         followsClause->synonyms());
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NotEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = notEvaluator.evaluate(pkb, dataStorage);

    std::unordered_map<std::string, std::vector<int>> m;
    m["s1"] = {1, 2, 2};
    m["s2"] = {1, 1, 2};
    QPS::Table expectedTable(m);

    REQUIRE(table == expectedTable);
  }

  SECTION("Test 2") {
    QPS::Argument arg1 = 1;
    std::shared_ptr<QPS::Declaration> decl2 =
        std::make_shared<QPS::StatementDeclaration>("s2");
    QPS::Argument arg2 = decl2;
    std::shared_ptr<QPS::Clause> followsClause =
        std::make_shared<QPS::SuchThatClause<QPS::FollowsRelationship>>(arg1,
                                                                        arg2);
    QPS::NotClauseEvaluator notEvaluator(followsClause,
                                         followsClause->synonyms());
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NotEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = notEvaluator.evaluate(pkb, dataStorage);

    std::unordered_map<std::string, std::vector<int>> m;
    m["s2"] = {1};
    QPS::Table expectedTable(m);

    REQUIRE(table == expectedTable);
  }

  SECTION("Test 3") {
    std::shared_ptr<QPS::Declaration> decl1 =
        std::make_shared<QPS::StatementDeclaration>("s1");
    QPS::Argument arg1 = decl1;
    QPS::Argument arg2 = 2;
    std::shared_ptr<QPS::Clause> followsClause =
        std::make_shared<QPS::SuchThatClause<QPS::FollowsRelationship>>(arg1,
                                                                        arg2);
    QPS::NotClauseEvaluator notEvaluator(followsClause,
                                         followsClause->synonyms());
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NotEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = notEvaluator.evaluate(pkb, dataStorage);

    std::unordered_map<std::string, std::vector<int>> m;
    m["s1"] = {2};
    QPS::Table expectedTable(m);

    REQUIRE(table == expectedTable);
  }

  SECTION("Test 4") {
    std::shared_ptr<QPS::Declaration> decl1 =
        std::make_shared<QPS::StatementDeclaration>("s1");
    QPS::Argument arg1 = decl1;
    QPS::Argument arg2 = 1;
    std::shared_ptr<QPS::Clause> followsClause =
        std::make_shared<QPS::SuchThatClause<QPS::FollowsRelationship>>(arg1,
                                                                        arg2);
    QPS::NotClauseEvaluator notEvaluator(followsClause,
                                         followsClause->synonyms());
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NotEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table;
    notEvaluator.evaluate(pkb, dataStorage);
    QPS::Table expectedTable{};
    REQUIRE(table == expectedTable);
  }

  SECTION("Test 5") {
    QPS::Argument arg1 = 1;
    QPS::Argument arg2 = 2;
    std::shared_ptr<QPS::Clause> followsClause =
        std::make_shared<QPS::SuchThatClause<QPS::FollowsRelationship>>(arg1,
                                                                        arg2);
    QPS::NotClauseEvaluator notEvaluator(followsClause,
                                         followsClause->synonyms());
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NotEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = notEvaluator.evaluate(pkb, dataStorage);

    REQUIRE(table == QPS::EMPTY_TABLE);
  }

  SECTION("Test 6") {
    QPS::Argument arg1 = 1;
    QPS::Argument arg2 = 2;
    std::shared_ptr<QPS::Clause> followsClause =
        std::make_shared<QPS::SuchThatClause<QPS::FollowsRelationship>>(arg1,
                                                                        arg2);
    std::shared_ptr<QPS::Clause> notFollowsClause =
        std::make_shared<QPS::NotClause>(followsClause);
    QPS::NotClauseEvaluator notEvaluator(notFollowsClause,
                                         notFollowsClause->synonyms());
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<NotEvaluatorPKBStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = notEvaluator.evaluate(pkb, dataStorage);

    QPS::Table expectedTable{};
    REQUIRE(table == expectedTable);
  }
}
