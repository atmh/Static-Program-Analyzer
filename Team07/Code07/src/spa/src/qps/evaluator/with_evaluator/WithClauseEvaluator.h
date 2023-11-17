#pragma once

#include "pkb/PKBStorageReadInterface.h"
#include "qps/evaluator/Evaluator.h"
#include "qps/query/clauses/Argument.h"
#include "qps/table/Table.h"

namespace QPS {

class WithClauseEvaluator : public Evaluator {
 public:
  WithClauseEvaluator(const Argument& arg1, const Argument& arg2);

  // nvi, impl method is called eval
  virtual Table evaluate(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache);

  virtual ~WithClauseEvaluator() = default;

  using EvalFuncType = Table (WithClauseEvaluator::*)(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage);

 private:
  EvalFuncType getEvalFunc(const Argument& arg1, const Argument& arg2);
  EvalFuncType getSynonymEvalFunc(const Argument& arg2);
  EvalFuncType getValueEvalFunc(const Argument& arg2);

  Table evalValueValue(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage);
  Table evalValueSynonym(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage);
  Table evalSynonymValue(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage);
  Table evalSynonymSynonym(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage);

 private:
  Argument arg1;
  Argument arg2;
  EvalFuncType evalFunc;
};

}  // namespace QPS
