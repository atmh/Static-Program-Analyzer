#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "catch.hpp"
#include "qps/evaluator/pattern_evaluator/IfPatternClauseEvaluator.h"
#include "qps/query/clauses/Argument.h"
#include "qps/query/declaration/Declaration.h"
#include "qps/query/declaration/IfDeclaration.h"
#include "qps/query/declaration/VariableDeclaration.h"
#include "qps/table/NormalizedDataStorage.h"
#include "stubs/pkb/PKBStorageReadAPI.h"

namespace {

struct IfPatternTestStub : public PKB::PKBStorageReadStub {
  virtual const std::unordered_map<std::string, std::unordered_set<int>>&
  getIfPatterns() const noexcept override {
    return ifPatterns;
  }

  virtual const std::unordered_set<int>& getIfFirstArgPatterns(
      const std::string& lhsArg) const noexcept override {
    return ifPatterns.find(lhsArg) == ifPatterns.end()
               ? emptySet
               : ifPatterns.find(lhsArg)->second;
  }

  std::unordered_map<std::string, std::unordered_set<int>> ifPatterns{
      {"v", {1, 2}},
      {"v2", {1, 3, 4}}};
  std::unordered_set<int> emptySet;
};

}  // namespace

TEST_CASE("If Pattern Evaluator - Synonym") {
  std::shared_ptr<QPS::Declaration> decl =
      std::make_shared<QPS::IfDeclaration>("if");
  std::shared_ptr<QPS::Declaration> synonym =
      std::make_shared<QPS::VariableDeclaration>("var");

  QPS::IfPatternClauseEvaluator evaluator(decl, synonym);
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<IfPatternTestStub>()};

  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 5);
}

TEST_CASE("If Pattern Evaluator - Value") {
  SECTION("v") {
    std::shared_ptr<QPS::Declaration> decl =
        std::make_shared<QPS::IfDeclaration>("if");
    QPS::Argument value{"v"};

    QPS::IfPatternClauseEvaluator evaluator(decl, value);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<IfPatternTestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.size() == 2);
  }

  SECTION("v2") {
    std::shared_ptr<QPS::Declaration> decl =
        std::make_shared<QPS::IfDeclaration>("if");
    QPS::Argument value{"v2"};

    QPS::IfPatternClauseEvaluator evaluator(decl, value);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<IfPatternTestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.size() == 3);
  }

  SECTION("v3") {
    std::shared_ptr<QPS::Declaration> decl =
        std::make_shared<QPS::IfDeclaration>("if");
    QPS::Argument value{"v3"};

    QPS::IfPatternClauseEvaluator evaluator(decl, value);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<IfPatternTestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(table.empty());
  }
}

TEST_CASE("If Pattern Evaluator - Wildcard") {
  std::shared_ptr<QPS::Declaration> decl =
      std::make_shared<QPS::IfDeclaration>("if");
  QPS::Argument wildcard;

  QPS::IfPatternClauseEvaluator evaluator(decl, wildcard);
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<IfPatternTestStub>()};

  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 4);  // it is not the case that every if loop uses a
                               // variable in the conditional
}
