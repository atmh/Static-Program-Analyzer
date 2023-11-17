#include "NextStarClauseEvaluator.h"

#include <queue>
#include <unordered_set>

#include "pkb/PKBStorageReadInterface.h"

namespace QPS {

namespace {

template <typename AdjacencyList>
std::unordered_set<int> getNext(AdjacencyList al, int u) {
  std::unordered_set<int> result;
  std::queue<int> q;
  q.push(u);
  // intentionally not pushing u into result...

  while (!q.empty()) {
    auto curr = q.front();
    q.pop();
    for (auto v : al(curr)) {
      // if it so happens to go back to u, the if cond will fail so we manage to
      // insert u into result, All of u's neighbors will be in the result at
      // that point and visiting u's neighbor will always continue
      if (result.find(v) != result.end())
        continue;
      result.insert(v);
      q.push(v);
    }
  }

  return result;
}

}  // namespace

bool NextStarClauseEvaluator::doHasRelationship(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb) {
  return pkb->hasNextRelationship();
}

bool NextStarClauseEvaluator::getRelationshipExists(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache, const Argument& arg1,
    const Argument& arg2) {
  auto al = [&pkb](int u) {
    return pkb->getNextFirstArgRelationships(u);
  };
  auto res = getNext(al, arg1);
  return res.find(arg2) != res.end();
}

std::unordered_set<int> NextStarClauseEvaluator::doGetFirstArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  auto al = [&pkb](int u) {
    return pkb->getNextFirstArgRelationships(u);
  };
  return dataStorage->encodeInts(getNext(al, arg));
}

std::unordered_set<int> NextStarClauseEvaluator::doGetSecondArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  auto al = [&pkb](int u) {
    return pkb->getNextSecondArgRelationships(u);
  };
  return dataStorage->encodeInts(getNext(al, arg));
}

}  // namespace QPS
