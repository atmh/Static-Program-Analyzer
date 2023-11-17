#include "NotClause.h"

#include <memory>

#include "qps/evaluator/decorator_evaluator/NotClauseEvaluator.h"
#include "qps/query/declaration/visitor/DeclarationSelector.h"

namespace QPS {

NotClause::NotClause(const std::shared_ptr<Clause>& clause) : clause(clause) {}

std::shared_ptr<Evaluator> NotClause::createEvaluator() const {
  return std::make_shared<NotClauseEvaluator>(clause, clause->synonyms());
}

bool NotClause::validate() const {
  return clause->validate();
}

std::vector<std::shared_ptr<Declaration>> NotClause::synonyms() const {
  return clause->synonyms();
}

size_t NotClause::doEstimatedCost(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  size_t underlying = clause->estimatedCost(pkb, dataStorage, evaluatorCache);
  size_t crossSize = 1;

  for (auto& declaration : clause->synonyms()) {
    DeclarationSelector declarationSelector{pkb, dataStorage};
    declaration->accept(declarationSelector);
    crossSize *= declarationSelector.getResult().size();
  }

  return crossSize - underlying;
}

}  // namespace QPS
