#include "Clause.h"

namespace QPS {

/**
 * Delegates work to evaluator, clause is not an evaluator so it
 * does not make semantic sense to implement the Evaluator interface.
 * The actual evaluation logic is inside ClauseEvaluator.
 * This is to resolve previous code review comments given
 * about potential LoDs.
 */
Table Clause::evaluate(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  auto evaluator = createEvaluator();
  return evaluator->evaluate(pkb, dataStorage, evaluatorCache);
}

bool Clause::validateStmtRef(const Argument& arg) const {
  return arg.getArgumentType() != Argument::ArgumentType::EXPR &&
         arg.getArgumentType() != Argument::ArgumentType::STRING;
}

bool Clause::validateEntRef(const Argument& arg) const {
  return arg.getArgumentType() != Argument::ArgumentType::EXPR &&
         arg.getArgumentType() != Argument::ArgumentType::INTEGER;
}

bool Clause::validateExpr(const Argument& arg) const {
  return arg.getArgumentType() == Argument::ArgumentType::EXPR ||
         arg.getArgumentType() == Argument::ArgumentType::WILDCARD;
}

size_t Clause::doEstimatedCost(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  auto evaluator = createEvaluator();
  size_t sz = evaluator->evaluate(pkb, dataStorage, evaluatorCache).size();
  if (sz == std::numeric_limits<int>::max())
    return 0;  // true clause, cheap
  return sz;
}

size_t Clause::estimatedCost(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  if (cost != std::numeric_limits<size_t>::max())
    return cost;
  return cost = doEstimatedCost(pkb, dataStorage, evaluatorCache);
}
}  // namespace QPS
