#pragma once

#include "qps/evaluator/pattern_evaluator/PatternClauseEvaluator.h"
#include "qps/query/clauses/Argument.h"
#include "qps/query/declaration/Declaration.h"

namespace QPS {

class IfPatternClauseEvaluator : public PatternClauseEvaluator {
 public:
  using PatternClauseEvaluator::PatternClauseEvaluator;

 private:
  virtual bool hasPattern(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb) override;

  virtual std::vector<std::vector<int>> getPatterns(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage) override;

  virtual std::vector<int> getPatternStatementByValue(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const Argument& arg) override;
};

}  // namespace QPS
