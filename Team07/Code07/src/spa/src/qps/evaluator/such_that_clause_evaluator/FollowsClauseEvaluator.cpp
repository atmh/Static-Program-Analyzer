#include "FollowsClauseEvaluator.h"

namespace QPS {

bool FollowsClauseEvaluator::doHasRelationship(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb) {
  return pkb->hasFollowsRelationship();
}

bool FollowsClauseEvaluator::getRelationshipExists(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache, const Argument& arg1,
    const Argument& arg2) {
  return pkb->getFollowsRelationshipExists(arg1, arg2);
}

std::unordered_set<int> FollowsClauseEvaluator::doGetFirstArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  return dataStorage->encodeInts(pkb->getFollowsFirstArgRelationships(arg));
}

std::unordered_set<int> FollowsClauseEvaluator::doGetSecondArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  return dataStorage->encodeInts(pkb->getFollowsSecondArgRelationships(arg));
}

}  // namespace QPS
