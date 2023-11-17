#include "Query.h"

#include "qps/evaluator/QueryEvaluator.h"

namespace QPS {

Query::Query() : selectClause(), valid(false) {}

Query::Query(QPS::SelectClause selectClause)
    : selectClause(std::move(selectClause)), valid(true) {}

void Query::addClause(const std::shared_ptr<Clause>& clause) {
  clauses.push_back(clause);
}

/**
 * Delegates work to evaluator, query is not an evaluator so it
 * does not make semantic sense to implement the Evaluator interface.
 * The actual evaluation logic is inside QueryEvaluator.
 * This is to resolve previous code review comments given
 * about potential LoDs.
 */
Table Query::evaluate(const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
                      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
                      const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  auto evaluator = createEvaluator();
  return evaluator->evaluate(pkb, dataStorage, evaluatorCache);
};

const SelectClause& Query::getSelectClause() const noexcept {
  return selectClause;
}

QueryResult Query::select(
    const Table& table,
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage) const {
  return selectClause.select(table, pkb, dataStorage);
}

const std::vector<std::shared_ptr<Clause>>& Query::getClauses() const noexcept {
  return clauses;
}

bool Query::isValid() const noexcept {
  return valid;
}

std::shared_ptr<Evaluator> Query::createEvaluator() const {
  return std::make_shared<QueryEvaluator>(selectClause, clauses);
}

bool Query::validate() const {
  bool ok = selectClause.validate();
  for (const auto& clause : clauses)
    ok = ok && clause != nullptr && clause->validate();
  return ok;
}

}  // namespace QPS
