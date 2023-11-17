#include "CallsClauseEvaluator.h"

#include "pkb/PKBStorageReadInterface.h"

namespace QPS {

bool CallsClauseEvaluator::doHasRelationship(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb) {
  return pkb->hasCallsRelationship();
}

bool CallsClauseEvaluator::getRelationshipExists(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache, const Argument& arg1,
    const Argument& arg2) {
  return pkb->getCallsRelationshipExists(arg1, arg2);
}

std::unordered_set<int> CallsClauseEvaluator::doGetFirstArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  return dataStorage->encodeStrings(pkb->getCallsFirstArgRelationships(arg));
}

std::unordered_set<int> CallsClauseEvaluator::doGetSecondArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  return dataStorage->encodeStrings(pkb->getCallsSecondArgRelationships(arg));
}

}  // namespace QPS
