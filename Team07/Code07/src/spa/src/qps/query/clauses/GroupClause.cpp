#include "GroupClause.h"
#include "qps/evaluator/decorator_evaluator/GroupEvaluator.h"

#include <unordered_set>

namespace QPS {

GroupClause::GroupClause(const SelectClause& selectClause,
                         const std::vector<std::shared_ptr<Clause>>& clauses)
    : selectClause(selectClause), clauses(clauses) {}

std::shared_ptr<Evaluator> GroupClause::createEvaluator() const {
  return std::make_shared<GroupEvaluator>(selectClause, clauses);
}

bool GroupClause::validate() const {
  for (const auto& clause : clauses) {
    if (!clause->validate())
      return false;
  }
  return true;
}

std::vector<std::shared_ptr<Declaration>> GroupClause::synonyms() const {
  std::unordered_set<std::shared_ptr<Declaration>> synonymsSet;
  std::vector<std::shared_ptr<Declaration>> res;

  for (const auto& clause : clauses) {
    const auto clauseSynonyms = clause->synonyms();
    for (const auto& s : clauseSynonyms) {
      if (synonymsSet.find(s) != synonymsSet.end())
        continue;
      synonymsSet.insert(s);
      res.push_back(s);
    }
  }

  return res;
}

// somewhat inaccurate, but hard to tell whether if we should add or multiply the cost
size_t GroupClause::doEstimatedCost(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  size_t cost = 0;
  for (auto& clause : clauses)
    cost += clause->estimatedCost(pkb, dataStorage, evaluatorCache);
  return cost;
}

}  // namespace QPS
