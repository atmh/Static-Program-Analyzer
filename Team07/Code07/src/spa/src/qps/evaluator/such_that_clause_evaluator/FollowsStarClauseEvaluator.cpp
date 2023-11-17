#include "FollowsStarClauseEvaluator.h"

namespace QPS {

bool FollowsStarClauseEvaluator::doHasRelationship(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb) {
  return pkb->hasFollowsStarRelationship();
}

bool FollowsStarClauseEvaluator::getRelationshipExists(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache, const Argument& arg1,
    const Argument& arg2) {
  return pkb->getFollowsStarRelationshipExists(arg1, arg2);
}

std::unordered_set<int> FollowsStarClauseEvaluator::doGetFirstArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  auto res =
      dataStorage->encodeInts(pkb->getFollowsStarFirstArgRelationships(arg));
  return {res.begin(), res.end()};
}

std::unordered_set<int> FollowsStarClauseEvaluator::doGetSecondArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  auto res =
      dataStorage->encodeInts(pkb->getFollowsStarSecondArgRelationships(arg));
  return {res.begin(), res.end()};
}

}  // namespace QPS
