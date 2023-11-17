#include "QueryOptimizer.h"

#include <algorithm>
#include <cassert>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "qps/algorithm/UFDS.h"
#include "qps/query/clauses/GroupClause.h"

namespace QPS {

namespace {

std::unordered_set<std::string> toStringSet(
    const std::vector<std::shared_ptr<Declaration>>& synonyms) {
  std::unordered_set<std::string> res;
  for (const auto& s : synonyms)
    res.insert(s->name());
  return res;
}

int countCommon(const std::shared_ptr<Clause>& clause,
                const std::unordered_set<std::string>& synonymsSet) {
  int commonCnt = 0;
  for (const auto& s : toStringSet(clause->synonyms())) {
    if (synonymsSet.find(s) != synonymsSet.end())
      ++commonCnt;
  }
  return commonCnt;
}

int countCheapSynonyms(const std::shared_ptr<Clause>& clause,
                       std::unordered_map<std::string, int>& synonymCounts,
                       const std::unordered_set<std::string>& projectedSet) {
  int cheapCnt = 0;
  for (const auto& s : toStringSet(clause->synonyms())) {
    assert(synonymCounts[s] != 0 &&
           "Should not be zero until we remove clause from consideration");
    if (synonymCounts[s] == 1 &&
        projectedSet.find(s) ==
            projectedSet.end())  // can drop synonym if we take it now
      cheapCnt++;
  }
  return cheapCnt;
}

bool comparator(const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
                const std::shared_ptr<NormalizedDataStorage>& dataStorage,
                const std::shared_ptr<EvaluatorCache>& evaluatorCache,
                const std::shared_ptr<Clause>& clauseA,
                const std::shared_ptr<Clause>& clauseB,
                const std::unordered_set<std::string>& projectedSet,
                const std::unordered_set<std::string>& synonymsSet,
                std::unordered_map<std::string, int>& synonymFreq) {
  int costA = static_cast<int>(
      clauseA->estimatedCost(pkb, dataStorage, evaluatorCache));
  int costB = static_cast<int>(
      clauseB->estimatedCost(pkb, dataStorage, evaluatorCache));

  // prioritize clauses with no constraints or those that make it immediately false
  if (costA != costB && (costA == 0 || costB == 0))
    return costA < costB;
  int aCommonCnt = countCommon(clauseA, synonymsSet);
  int bCommonCnt = countCommon(clauseB, synonymsSet);
  auto aStringSet = toStringSet(clauseA->synonyms());
  auto bStringSet = toStringSet(clauseB->synonyms());
  bool aIsFilter = aCommonCnt == aStringSet.size();
  bool bIsFilter = bCommonCnt == bStringSet.size();
  if (aIsFilter != bIsFilter)  // prefer clauses that do a filter
    return bIsFilter < aIsFilter;
  int aProjectedCnt = countCommon(clauseA, projectedSet);
  int bProjectedCnt = countCommon(clauseB, projectedSet);
  int aCheapCnt = countCheapSynonyms(clauseA, synonymFreq, projectedSet);
  int bCheapCnt = countCheapSynonyms(clauseB, synonymFreq, projectedSet);
  if (aCommonCnt != bCommonCnt)  // prefer those with more overlaps
    return bCommonCnt < aCommonCnt;
  if (aCheapCnt !=
      bCheapCnt)  // cheap counts are synonyms that can be dropped next
    return bCheapCnt < aCheapCnt;
  if (aProjectedCnt != bProjectedCnt)  // prefer those with lesser in projection
    return aProjectedCnt < bProjectedCnt;
  std::vector<std::string> aSynonyms{aStringSet.begin(), aStringSet.end()};
  std::vector<std::string> bSynonyms{bStringSet.begin(), bStringSet.end()};
  if (aSynonyms.size() !=
      bSynonyms.size())  // prefer clauses with lesser synonyms
    return aSynonyms.size() < bSynonyms.size();
  return costA < costB;
}

std::vector<std::shared_ptr<Clause>> sortingOptimization(
    const std::vector<std::shared_ptr<Clause>>& clauses,
    const SelectClause& selectClause,
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {

  if (clauses.empty())
    return {};

  auto sortedClauses = clauses;
  std::vector<std::shared_ptr<Clause>> res;
  std::unordered_set<std::shared_ptr<Clause>> visited;
  std::unordered_set<std::shared_ptr<Clause>> remainingClauses{clauses.begin(),
                                                               clauses.end()};
  std::unordered_set<std::string> synonymsSet;
  std::unordered_set<std::string> projectedSet;
  std::unordered_map<std::string, int> synonymFreq;
  for (auto& clause : clauses)
    for (auto& synonym : toStringSet(clause->synonyms()))
      synonymFreq[synonym]++;

  for (const auto& s : toStringSet(selectClause.getDeclarations()))
    projectedSet.insert(s);

  auto cmp = [&](auto& clauseA, auto& clauseB) {
    return comparator(pkb, dataStorage, evaluatorCache, clauseA, clauseB,
                      projectedSet, synonymsSet, synonymFreq);
  };

  std::sort(sortedClauses.begin(), sortedClauses.end(), cmp);
  // perform traversal in order of cost
  for (const auto& start : sortedClauses) {
    if (visited.find(start) != visited.end())
      continue;

    std::queue<std::shared_ptr<Clause>> q;
    q.push(start);
    visited.insert(start);
    remainingClauses.erase(start);
    for (const auto& synonym : toStringSet(start->synonyms()))
      synonymFreq[synonym]--;

    while (!q.empty()) {
      auto curr = q.front();
      q.pop();
      res.push_back(curr);
      for (const auto& s : toStringSet(curr->synonyms()))
        synonymsSet.insert(s);

      std::vector<std::shared_ptr<Clause>> clausesInConsideration{
          remainingClauses.begin(), remainingClauses.end()};

      auto it = std::min_element(clausesInConsideration.begin(),
                                 clausesInConsideration.end(), cmp);
      if (it == clausesInConsideration.end())
        continue;

      auto next = *it;

      visited.insert(next);
      remainingClauses.erase(next);
      q.push(next);
      for (const auto& synonym : toStringSet(next->synonyms()))
        synonymFreq[synonym]--;
    }
  }

  assert(std::unordered_set<std::shared_ptr<Clause>>(clauses.begin(),
                                                     clauses.end()) ==
         std::unordered_set<std::shared_ptr<Clause>>(res.begin(), res.end()));
  return res;
}

std::unordered_map<std::string, int> serializeDeclarations(
    const std::vector<std::shared_ptr<Clause>>& clauses) {
  std::unordered_map<std::string, int> declarationMap;
  for (const auto& clause : clauses) {
    for (const auto& synonym : toStringSet(clause->synonyms())) {
      if (declarationMap.find(synonym) != declarationMap.end())
        continue;
      declarationMap[synonym] = static_cast<int>(declarationMap.size());
    }
  }
  return declarationMap;
}

std::vector<std::vector<std::shared_ptr<Clause>>> groupingOptimization(
    const Query& query) {
  auto selectClause = query.getSelectClause();
  auto clauses = query.getClauses();

  // serialize declaredNames
  std::unordered_map<std::string, int> declarationMap =
      serializeDeclarations(clauses);

  UFDS uf(static_cast<int>(declarationMap.size()));

  // perform union find
  for (const auto& clause : clauses) {
    const auto stringSet = toStringSet(clause->synonyms());
    std::vector<std::string> clauseSynonyms = {stringSet.begin(),
                                               stringSet.end()};
    for (int i = 1; i < clauseSynonyms.size(); i++) {
      int currId = declarationMap[clauseSynonyms[i]];
      int prevId = declarationMap[clauseSynonyms[i - 1]];

      uf.merge(currId, prevId);
    }
  }

  std::unordered_map<int, std::vector<std::shared_ptr<Clause>>> groups;
  // append clauses with synonyms
  for (const auto& clause : clauses) {
    const auto clauseSynonyms = toStringSet(clause->synonyms());
    if (clauseSynonyms.empty())
      continue;
    int synonymId = declarationMap[*clauseSynonyms.begin()];
    int groupId = uf.getPar(synonymId);
    groups[groupId].push_back(clause);
  }

  // append clauses without synonyms...
  for (const auto& clause : clauses) {
    if (clause->synonyms().empty()) {
      groups[static_cast<int>(groups.size())].push_back(clause);
    }
  }

  std::vector<std::vector<std::shared_ptr<Clause>>> res;

  for (auto& [_, groupClauseVec] : groups)
    res.push_back(groupClauseVec);

  return res;
}

}  // namespace

QueryOptimizer::QueryOptimizer(const QPS::Query& query) : query(query) {}

Query QueryOptimizer::optimize(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  auto selectClause = query.getSelectClause();
  auto groups = groupingOptimization(query);
  std::vector<std::shared_ptr<Clause>> newClauses;

  for (auto& group : groups) {
    group = sortingOptimization(group, selectClause, pkb, dataStorage,
                                evaluatorCache);
    newClauses.push_back(std::make_shared<GroupClause>(selectClause, group));
  }

  newClauses = sortingOptimization(newClauses, selectClause, pkb, dataStorage,
                                   evaluatorCache);

  Query res{selectClause};
  for (auto& clause : newClauses)
    res.addClause(clause);

  return res;
}

}  // namespace QPS
