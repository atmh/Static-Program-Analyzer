#pragma once

#include "qps/evaluator/pattern_evaluator/PatternClauseEvaluator.h"
#include "qps/query/clauses/Argument.h"

namespace QPS {

class AssignPatternClauseEvaluator : public PatternClauseEvaluator {
 public:
  AssignPatternClauseEvaluator(const std::shared_ptr<Declaration>& declaration,
                               const Argument& arg1, const Argument& arg2);

 protected:
  /**
   * Customized logic as 2nd argument may not be wildcard
   */
  virtual Table evaluateWildcard(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage) override;

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

 protected:
  Argument arg2;
};

}  // namespace QPS