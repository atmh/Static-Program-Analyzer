#pragma once

#include <cassert>

#include "qps/evaluator/Evaluator.h"
#include "qps/query/clauses/Argument.h"
#include "qps/table/Table.h"

namespace QPS {

class PatternClauseEvaluator : public Evaluator {
 public:
  PatternClauseEvaluator(const std::shared_ptr<Declaration>& declaration,
                         const Argument& arg1);

  virtual Table evaluate(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache = nullptr) override;

  virtual ~PatternClauseEvaluator() = 0;

  using EvalFuncType = Table (PatternClauseEvaluator::*)(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage);

 protected:
  virtual Table evaluateSynonym(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage);

  virtual Table evaluateValue(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage);

  virtual Table evaluateWildcard(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage);

 private:
  virtual bool hasPattern(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb) = 0;

  virtual std::vector<std::vector<int>> getPatterns(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage) = 0;

  virtual std::vector<int> getPatternStatementByValue(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const Argument& arg) = 0;

  EvalFuncType getEvalFunc(const Argument& arg1);

 protected:
  std::shared_ptr<Declaration> declaration;
  Argument arg1;
  EvalFuncType evalFunc;
};

}  // namespace QPS
