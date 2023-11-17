#include "EvaluatorFacade.h"

#include <memory>

#include "qps/evaluator/EvaluatorCache.h"
#include "qps/query/QueryOptimizer.h"
#include "qps/table/NormalizedDataStorage.h"

namespace QPS {

QueryResult EvaluatorFacade::evaluate(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const Query& query) {
  std::shared_ptr<NormalizedDataStorage> dataStorage =
      std::make_shared<NormalizedDataStorage>();
  std::shared_ptr<EvaluatorCache> evaluatorCache =
      std::make_shared<EvaluatorCache>();

  QueryOptimizer queryOptimizer{query};
  Query optimizedQuery =
      queryOptimizer.optimize(pkb, dataStorage, evaluatorCache);

  auto table = optimizedQuery.evaluate(pkb, dataStorage, evaluatorCache);

  // deal with boolean select
  return optimizedQuery.select(table, pkb, dataStorage);
}

};  // namespace QPS
