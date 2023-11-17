#include "CallsStarClauseEvaluator.h"

#include "pkb/PKBStorageReadInterface.h"

namespace QPS {

bool CallsStarClauseEvaluator::doHasRelationship(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb) {
  return pkb->hasCallsStarRelationship();
}

bool CallsStarClauseEvaluator::getRelationshipExists(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache, const Argument& arg1,
    const Argument& arg2) {
  return pkb->getCallsStarRelationshipExists(arg1, arg2);
}

std::unordered_set<int> CallsStarClauseEvaluator::doGetFirstArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  return dataStorage->encodeStrings(
      pkb->getCallsStarFirstArgRelationships(arg));
}

std::unordered_set<int> CallsStarClauseEvaluator::doGetSecondArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  return dataStorage->encodeStrings(
      pkb->getCallsStarSecondArgRelationships(arg));
}

}  // namespace QPS
