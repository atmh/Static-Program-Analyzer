#include "ParentClauseEvaluator.h"

namespace QPS {

bool ParentClauseEvaluator::doHasRelationship(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb) {
  return pkb->hasParentRelationship();
}

bool ParentClauseEvaluator::getRelationshipExists(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache, const Argument& arg1,
    const Argument& arg2) {
  return pkb->getParentRelationshipExists(arg1, arg2);
}

std::unordered_set<int> ParentClauseEvaluator::doGetFirstArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  auto res = dataStorage->encodeInts(pkb->getParentFirstArgRelationships(arg));
  return {res.begin(), res.end()};
}

std::unordered_set<int> ParentClauseEvaluator::doGetSecondArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  auto res = dataStorage->encodeInts(pkb->getParentSecondArgRelationships(arg));
  return {res.begin(), res.end()};
}

}  // namespace QPS
