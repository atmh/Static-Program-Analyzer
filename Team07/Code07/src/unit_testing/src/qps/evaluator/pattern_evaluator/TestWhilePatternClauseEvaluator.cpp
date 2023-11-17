#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "catch.hpp"
#include "qps/evaluator/pattern_evaluator/WhilePatternClauseEvaluator.h"
#include "qps/query/clauses/Argument.h"
#include "qps/query/declaration/Declaration.h"
#include "qps/query/declaration/VariableDeclaration.h"
#include "qps/query/declaration/WhileDeclaration.h"
#include "qps/table/NormalizedDataStorage.h"
#include "stubs/pkb/PKBStorageReadAPI.h"

namespace {

struct WhilePatternTestStub : public PKB::PKBStorageReadStub {
  virtual const std::unordered_map<std::string, std::unordered_set<int>>&
  getWhilePatterns() const noexcept override {
    return whilePatterns;
  }

  virtual const std::unordered_set<int>& getWhileFirstArgPatterns(
      const std::string& lhsArg) const noexcept override {
    return whilePatterns.find(lhsArg) == whilePatterns.end()
               ? emptySet
               : whilePatterns.find(lhsArg)->second;
  }

  std::unordered_map<std::string, std::unordered_set<int>> whilePatterns{
      {"v", {1, 2}},
      {"v2", {1, 3, 4}}};
  std::unordered_set<int> emptySet;
};

}  // namespace

TEST_CASE("While Pattern Evaluator - Synonym") {
  std::shared_ptr<QPS::Declaration> decl =
      std::make_shared<QPS::WhileDeclaration>("while");
  std::shared_ptr<QPS::Declaration> synonym =
      std::make_shared<QPS::VariableDeclaration>("var");

  QPS::WhilePatternClauseEvaluator evaluator(decl, synonym);
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<WhilePatternTestStub>()};

  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 5);
}

TEST_CASE("While Pattern Evaluator - Value") {
  SECTION("v") {
    std::shared_ptr<QPS::Declaration> decl =
        std::make_shared<QPS::WhileDeclaration>("while");
    QPS::Argument value{"v"};

    QPS::WhilePatternClauseEvaluator evaluator(decl, value);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<WhilePatternTestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.size() == 2);
  }

  SECTION("v2") {
    std::shared_ptr<QPS::Declaration> decl =
        std::make_shared<QPS::WhileDeclaration>("while");
    QPS::Argument value{"v2"};

    QPS::WhilePatternClauseEvaluator evaluator(decl, value);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<WhilePatternTestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.size() == 3);
  }

  SECTION("v3") {
    std::shared_ptr<QPS::Declaration> decl =
        std::make_shared<QPS::WhileDeclaration>("while");
    QPS::Argument value{"v3"};

    QPS::WhilePatternClauseEvaluator evaluator(decl, value);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<WhilePatternTestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(table.empty());
  }
}

TEST_CASE("While Pattern Evaluator - Wildcard") {
  std::shared_ptr<QPS::Declaration> decl =
      std::make_shared<QPS::WhileDeclaration>("while");
  QPS::Argument wildcard;

  QPS::WhilePatternClauseEvaluator evaluator(decl, wildcard);
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<WhilePatternTestStub>()};

  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
      std::make_shared<QPS::NormalizedDataStorage>()};

  QPS::Table table = evaluator.evaluate(pkb, dataStorage);

  REQUIRE(!table.empty());
  REQUIRE(table.size() == 4);  // it is not the case that every while uses a
                               // variable in the conditional
}
