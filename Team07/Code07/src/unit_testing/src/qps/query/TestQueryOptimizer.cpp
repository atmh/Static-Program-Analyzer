#include "catch.hpp"
#include "qps/query/Query.h"
#include "qps/query/QueryOptimizer.h"
#include "qps/query/clauses/SuchThatClause.h"
#include "qps/query/select/SelectClause.h"
#include "stubs/pkb/PKBStorageReadAPI.h"

#include <memory>

namespace {
struct OptimizationPKBTestStub : public PKB::PKBStorageReadStub {
  const std::unordered_set<int>& getStmts() const noexcept override {
    return stmts;
  }

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

  virtual bool hasFollowsRelationship() override { return true; }

  std::unordered_set<int> stmts{1, 2};
};

}  // namespace

TEST_CASE("Group optimization") {

  SECTION("1 group from 1 clause") {
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage =
        std::make_shared<QPS::NormalizedDataStorage>();
    std::shared_ptr<PKB::PKBStorageReadStub> pkb =
        std::make_shared<OptimizationPKBTestStub>();
    std::shared_ptr<QPS::EvaluatorCache> evaluatorCache =
        std::make_shared<QPS::EvaluatorCache>();
    std::shared_ptr<QPS::Declaration> declaration =
        std::make_shared<QPS::StatementDeclaration>("s");
    QPS::Query query{QPS::SelectClause{{declaration}}};
    query.addClause(
        std::make_shared<QPS::SuchThatClause<QPS::FollowsRelationship>>(
            1, declaration));

    QPS::QueryOptimizer queryOptimizer{query};
    QPS::Query optimizedQuery =
        queryOptimizer.optimize(pkb, dataStorage, evaluatorCache);
    REQUIRE(optimizedQuery.getClauses().size() == 1);

    QPS::Table table =
        optimizedQuery.createEvaluator()->evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    std::unordered_map<std::string, std::vector<int>> m{{"s", {2}}};
    REQUIRE(table == QPS::Table{m});
  }

  SECTION("1 group from 2 clauses") {
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage =
        std::make_shared<QPS::NormalizedDataStorage>();
    std::shared_ptr<PKB::PKBStorageReadStub> pkb =
        std::make_shared<OptimizationPKBTestStub>();
    std::shared_ptr<QPS::EvaluatorCache> evaluatorCache =
        std::make_shared<QPS::EvaluatorCache>();
    std::shared_ptr<QPS::Declaration> declaration =
        std::make_shared<QPS::StatementDeclaration>("s");
    QPS::Query query{QPS::SelectClause{{declaration}}};
    query.addClause(
        std::make_shared<QPS::SuchThatClause<QPS::FollowsRelationship>>(
            1, declaration));
    query.addClause(
        std::make_shared<QPS::SuchThatClause<QPS::FollowsRelationship>>(
            2, declaration));

    QPS::QueryOptimizer queryOptimizer{query};
    QPS::Query optimizedQuery =
        queryOptimizer.optimize(pkb, dataStorage, evaluatorCache);
    REQUIRE(optimizedQuery.getClauses().size() == 1);

    QPS::Table table =
        optimizedQuery.createEvaluator()->evaluate(pkb, dataStorage);

    std::unordered_map<std::string, std::vector<int>> m{{"s", {}}};
    REQUIRE(table.empty());
    REQUIRE(table == QPS::Table{m});
  }

  SECTION("2 group, with bool true") {
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage =
        std::make_shared<QPS::NormalizedDataStorage>();
    std::shared_ptr<PKB::PKBStorageReadStub> pkb =
        std::make_shared<OptimizationPKBTestStub>();
    std::shared_ptr<QPS::EvaluatorCache> evaluatorCache =
        std::make_shared<QPS::EvaluatorCache>();
    std::shared_ptr<QPS::Declaration> declaration =
        std::make_shared<QPS::StatementDeclaration>("s");
    QPS::Query query{QPS::SelectClause{{declaration}}};
    query.addClause(
        std::make_shared<QPS::SuchThatClause<QPS::FollowsRelationship>>(
            1, declaration));
    query.addClause(
        std::make_shared<QPS::SuchThatClause<QPS::FollowsRelationship>>(1, 2));

    QPS::QueryOptimizer queryOptimizer{query};
    QPS::Query optimizedQuery =
        queryOptimizer.optimize(pkb, dataStorage, evaluatorCache);
    REQUIRE(optimizedQuery.getClauses().size() == 2);

    QPS::Table table =
        optimizedQuery.createEvaluator()->evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    std::unordered_map<std::string, std::vector<int>> m{{"s", {2}}};
    REQUIRE(table == QPS::Table{m});
  }

  SECTION("2 group, with bool false") {
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage =
        std::make_shared<QPS::NormalizedDataStorage>();
    std::shared_ptr<PKB::PKBStorageReadStub> pkb =
        std::make_shared<OptimizationPKBTestStub>();
    std::shared_ptr<QPS::EvaluatorCache> evaluatorCache =
        std::make_shared<QPS::EvaluatorCache>();
    std::shared_ptr<QPS::Declaration> declaration =
        std::make_shared<QPS::StatementDeclaration>("s");
    QPS::Query query{QPS::SelectClause{{declaration}}};
    query.addClause(
        std::make_shared<QPS::SuchThatClause<QPS::FollowsRelationship>>(
            1, declaration));
    query.addClause(
        std::make_shared<QPS::SuchThatClause<QPS::FollowsRelationship>>(2, 1));

    QPS::QueryOptimizer queryOptimizer{query};
    QPS::Query optimizedQuery =
        queryOptimizer.optimize(pkb, dataStorage, evaluatorCache);
    REQUIRE(optimizedQuery.getClauses().size() == 2);

    QPS::Table table =
        optimizedQuery.createEvaluator()->evaluate(pkb, dataStorage);

    REQUIRE(table.empty());
  }

  SECTION("Test drop irrelevant synonyms") {
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage =
        std::make_shared<QPS::NormalizedDataStorage>();
    std::shared_ptr<PKB::PKBStorageReadStub> pkb =
        std::make_shared<OptimizationPKBTestStub>();
    std::shared_ptr<QPS::EvaluatorCache> evaluatorCache =
        std::make_shared<QPS::EvaluatorCache>();
    std::shared_ptr<QPS::Declaration> declaration1 =
        std::make_shared<QPS::StatementDeclaration>("s1");
    std::shared_ptr<QPS::Declaration> declaration2 =
        std::make_shared<QPS::StatementDeclaration>("s2");
    QPS::Query query{QPS::SelectClause{{declaration1}}};
    query.addClause(
        std::make_shared<QPS::SuchThatClause<QPS::FollowsRelationship>>(
            declaration1, declaration2));
    query.addClause(
        std::make_shared<QPS::SuchThatClause<QPS::FollowsRelationship>>(1, 2));

    QPS::QueryOptimizer queryOptimizer{query};
    QPS::Query optimizedQuery =
        queryOptimizer.optimize(pkb, dataStorage, evaluatorCache);
    REQUIRE(optimizedQuery.getClauses().size() == 2);

    QPS::Table table =
        optimizedQuery.createEvaluator()->evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(
        table[declaration2]
            .empty());  // if table is not empty and col is empty it means col does not exist in table
    std::unordered_map<std::string, std::vector<int>> m{{"s1", {1}}};
    REQUIRE(table == QPS::Table{m});
  }
}
