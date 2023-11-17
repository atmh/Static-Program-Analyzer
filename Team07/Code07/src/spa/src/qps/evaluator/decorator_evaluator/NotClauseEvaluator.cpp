#include "NotClauseEvaluator.h"

#include "qps/query/select/SelectClause.h"

namespace QPS {

namespace {

std::vector<std::shared_ptr<Declaration>> getUniqueDeclarations(
    const std::vector<std::shared_ptr<Declaration>>& synonyms) {
  std::vector<std::shared_ptr<Declaration>> res;
  std::unordered_set<std::string> synonymNameSet;

  for (const auto& s : synonyms) {
    if (synonymNameSet.find(s->name()) != synonymNameSet.end())
      continue;
    synonymNameSet.insert(s->name());
    res.push_back(s);
  }

  return res;
}

}  // namespace

NotClauseEvaluator::NotClauseEvaluator(
    const std::shared_ptr<Clause>& clause,
    const std::vector<std::shared_ptr<Declaration>>& synonyms)
    : clause(clause), synonyms(synonyms) {}

Table NotClauseEvaluator::evaluate(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  Table underlyingResult = clause->evaluate(pkb, dataStorage, evaluatorCache);

  if (underlyingResult.trueTable())
    return EMPTY_TABLE;

  if (underlyingResult.empty())
    return {};

  SelectClause selectClause(getUniqueDeclarations(synonyms));
  Table crossProductTable = selectClause.project(pkb, {}, dataStorage);

  return crossProductTable - underlyingResult;
}

}  // namespace QPS
