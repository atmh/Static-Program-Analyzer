#include "QueryEvaluator.h"

namespace QPS {

QueryEvaluator::QueryEvaluator(
    const QPS::SelectClause& selectClause,
    const std::vector<std::shared_ptr<Clause>>& clauses)
    : selectClause(selectClause), clauses(clauses) {}

Table QueryEvaluator::evaluate(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  // evaluate clauses
  Table table;
  for (const auto& clause : clauses) {
    table = table * clause->evaluate(pkb, dataStorage, evaluatorCache);
    if (table.empty())
      break;
  }

  // evaluate select
  table = selectClause.project(pkb, table, dataStorage);

  return table;
}

}  // namespace QPS
