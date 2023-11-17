#pragma once

#include <unordered_set>

#include "qps/evaluator/such_that_clause_evaluator/SuchThatClauseEvaluator.h"
#include "qps/query/clauses/Argument.h"

namespace QPS {

class AffectsClauseEvaluator : public SuchThatClauseEvaluator {
 public:
  using SuchThatClauseEvaluator::SuchThatClauseEvaluator;

  virtual ~AffectsClauseEvaluator() = default;

 private:
  virtual bool doHasRelationship(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb) override;

  virtual bool getRelationshipExists(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache,
      const Argument& arg1, const Argument& arg2) override;

  virtual std::unordered_set<int> doGetFirstArgRelationships(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const Argument& arg) override;

  virtual std::unordered_set<int> doGetSecondArgRelationships(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const Argument& arg) override;

  std::unordered_set<int> getAffects(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb, int u,
      bool isFirstArg);
};

}  // namespace QPS
