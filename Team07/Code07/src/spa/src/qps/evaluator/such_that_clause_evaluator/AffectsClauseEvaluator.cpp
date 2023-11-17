#include "AffectsClauseEvaluator.h"

#include "pkb/PKBStorageReadInterface.h"

#include <functional>
#include <unordered_set>

namespace QPS {

namespace {

template <typename AdjacencyList>
std::unordered_set<int> getAffectsHelper(
    const AdjacencyList& al, int u,
    const std::function<bool(int)>& checkTerminate,
    const std::function<bool(int)>& checkAddResult) {
  std::unordered_set<int> result, vis;

  std::function<void(int cur)> dfs = [&](int cur) {
    vis.insert(cur);
    if (checkAddResult(cur))
      result.insert(cur);
    if (checkTerminate(cur))
      return;

    for (int child : al(cur)) {
      if (vis.find(child) != vis.end())
        continue;
      dfs(child);
    }
  };

  for (int child : al(u))
    if (vis.find(child) == vis.end())
      dfs(child);
  return result;
}

}  // namespace

bool AffectsClauseEvaluator::doHasRelationship(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb) {
  const std::unordered_set<int>& assignmentStmts = pkb->getAssigns();
  for (const int assignmentStmt : assignmentStmts) {
    if (!getAffects(pkb, assignmentStmt, true).empty())
      return true;
  }
  return false;
}

bool AffectsClauseEvaluator::getRelationshipExists(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache, const Argument& arg1,
    const Argument& arg2) {
  // call polymorphic version in hopes of getting cached
  const std::unordered_set<int>& res =
      getFirstArgRelationships(pkb, dataStorage, evaluatorCache, arg1);
  return res.find(dataStorage->encodeInt(arg2)) != res.end();
}

std::unordered_set<int> AffectsClauseEvaluator::doGetFirstArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  const std::unordered_set<int>& res = getAffects(pkb, arg, true);
  return dataStorage->encodeInts(res);
}

std::unordered_set<int> AffectsClauseEvaluator::doGetSecondArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  const std::unordered_set<int>& res = getAffects(pkb, arg, false);
  return dataStorage->encodeInts(res);
}

std::unordered_set<int> AffectsClauseEvaluator::getAffects(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb, int u,
    bool isFirstArg) {
  const std::unordered_set<int>& assignmentStmts = pkb->getAssigns();
  if (assignmentStmts.find(u) == assignmentStmts.end())
    return {};
  const std::unordered_set<int>& readStmts = pkb->getReads();
  const std::unordered_set<int>& callStmts = pkb->getCalls();

  std::unordered_set<int> terminalStmts;
  for (const auto& stmts : {assignmentStmts, readStmts, callStmts})
    terminalStmts.insert(stmts.begin(), stmts.end());

  const auto& variables =
      isFirstArg ? pkb->getModifiesStatementFirstArgRelationships(u)
                 : pkb->getUsesStatementFirstArgRelationships(u);
  std::unordered_set<int> res;

  for (const auto& v : variables) {
    std::function<std::unordered_set<int>(int)> al;
    std::function<bool(int)> checkAddResult;
    std::function<bool(int)> checkTerminate = [&pkb, &v,
                                               &terminalStmts](int u) {
      return terminalStmts.find(u) != terminalStmts.end() &&
             pkb->getModifiesStatementRelationshipExists(u, v);
    };

    if (isFirstArg) {
      al = [&pkb](int u) {
        return pkb->getNextFirstArgRelationships(u);
      };
      checkAddResult = [&pkb, &v, &assignmentStmts](int u) {
        return assignmentStmts.find(u) != assignmentStmts.end() &&
               pkb->getUsesStatementRelationshipExists(u, v);
      };
    } else {
      al = [&pkb](int u) {
        return pkb->getNextSecondArgRelationships(u);
      };
      checkAddResult = [&pkb, &v, &assignmentStmts](int u) {
        return assignmentStmts.find(u) != assignmentStmts.end() &&
               pkb->getModifiesStatementRelationshipExists(u, v);
      };
    }

    const auto additionalStmts =
        getAffectsHelper(al, u, checkTerminate, checkAddResult);
    res.insert(additionalStmts.begin(), additionalStmts.end());
  }

  return res;
}

}  // namespace QPS
