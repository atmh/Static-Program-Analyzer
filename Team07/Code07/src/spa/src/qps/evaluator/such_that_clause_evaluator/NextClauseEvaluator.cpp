#include "NextClauseEvaluator.h"

#include "pkb/PKBStorageReadInterface.h"

namespace QPS {

bool NextClauseEvaluator::doHasRelationship(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb) {
  return pkb->hasNextRelationship();
}

bool NextClauseEvaluator::getRelationshipExists(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache, const Argument& arg1,
    const Argument& arg2) {
  return pkb->getNextRelationshipExists(arg1, arg2);
}

std::unordered_set<int> NextClauseEvaluator::doGetFirstArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  return dataStorage->encodeInts(pkb->getNextFirstArgRelationships(arg));
}

std::unordered_set<int> NextClauseEvaluator::doGetSecondArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  return dataStorage->encodeInts(pkb->getNextSecondArgRelationships(arg));
}

}  // namespace QPS
