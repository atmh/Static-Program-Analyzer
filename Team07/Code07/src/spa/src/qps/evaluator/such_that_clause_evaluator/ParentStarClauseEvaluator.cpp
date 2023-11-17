#include "ParentStarClauseEvaluator.h"

namespace QPS {

bool ParentStarClauseEvaluator::doHasRelationship(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb) {
  return pkb->hasParentStarRelationship();
}

bool ParentStarClauseEvaluator::getRelationshipExists(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache, const Argument& arg1,
    const Argument& arg2) {
  return pkb->getParentStarRelationshipExists(arg1, arg2);
}

std::unordered_set<int> ParentStarClauseEvaluator::doGetFirstArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  auto res =
      dataStorage->encodeInts(pkb->getParentStarFirstArgRelationships(arg));
  return {res.begin(), res.end()};
}

std::unordered_set<int> ParentStarClauseEvaluator::doGetSecondArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  auto res =
      dataStorage->encodeInts(pkb->getParentStarSecondArgRelationships(arg));
  return {res.begin(), res.end()};
}

}  // namespace QPS
