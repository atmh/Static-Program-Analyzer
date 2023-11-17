#pragma once

#include <cassert>

#include "pkb/PKBStorageReadInterface.h"
#include "qps/evaluator/Evaluator.h"
#include "qps/query/clauses/Argument.h"
#include "qps/query/declaration/visitor/DeclarationSelector.h"
#include "qps/table/Table.h"

namespace QPS {
/**
 * Template method pattern class.
 *
 * This is a framework to evaluate SuchThatClauseEvaluator.
 * To specify the behavior of the evaluator, override the private virtual
 * functions.
 *
 * To enable the class to work with strings and ints, all manipulation is done
 * on the encoded ints. This is a key invariant and any methods invoked within
 * this class that returns results from pkb must return results in the form of
 * encoded results.
 */
class SuchThatClauseEvaluator : public Evaluator {
 public:
  SuchThatClauseEvaluator(const Argument& arg1, const Argument& arg2);

  // template method pattern, override private virtual functions
  virtual Table evaluate(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache = nullptr);

  virtual ~SuchThatClauseEvaluator() = 0;

  using EvalFuncType = Table (SuchThatClauseEvaluator::*)(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache);

 private:
  EvalFuncType getEvalFunc(const Argument& arg1, const Argument& arg2);
  EvalFuncType getSynonymEvalFunc(const Argument& arg2);
  EvalFuncType getValueEvalFunc(const Argument& arg2);
  EvalFuncType getWildcardEvalFunc(const Argument& arg2);

  virtual Table evaluateSynonymSynonym(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache);

  virtual Table evaluateSynonymValue(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache);

  virtual Table evaluateSynonymWildcard(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache);

  virtual Table evaluateValueSynonym(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache);

  virtual Table evaluateValueValue(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache);

  virtual Table evaluateValueWildcard(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache);

  virtual Table evaluateWildcardSynonym(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache);

  virtual Table evaluateWildcardValue(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache);

  virtual Table evaluateWildcardWildcard(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache);

  virtual bool doHasRelationship(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb) = 0;
  virtual bool getRelationshipExists(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache,
      const Argument& arg1, const Argument& arg2) = 0;
  virtual std::unordered_set<int> doGetFirstArgRelationships(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const Argument& arg) = 0;
  virtual std::unordered_set<int> doGetSecondArgRelationships(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const Argument& arg) = 0;

 protected:
  // wraps over the virtual form and caches the results
  bool hasRelationship(const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
                       const std::shared_ptr<EvaluatorCache>& evaluatorCache);
  const std::unordered_set<int>& getFirstArgRelationships(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache,
      const Argument& arg);
  const std::unordered_set<int>& getSecondArgRelationships(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache,
      const Argument& arg);

 protected:
  Argument arg1;
  Argument arg2;
  EvalFuncType evalFunc;
};

}  // namespace QPS
