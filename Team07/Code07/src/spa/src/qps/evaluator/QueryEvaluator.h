#pragma once

#include <memory>
#include <vector>

#include "qps/evaluator/Evaluator.h"
#include "qps/query/clauses/Clause.h"
#include "qps/query/select/SelectClause.h"

namespace QPS {

class QueryEvaluator : public Evaluator {
 public:
  QueryEvaluator(const SelectClause& selectClause,
                 const std::vector<std::shared_ptr<Clause>>& clauses);

  virtual Table evaluate(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache) override;

  virtual ~QueryEvaluator() = default;

 private:
  SelectClause selectClause;
  std::vector<std::shared_ptr<Clause>> clauses;
};

}  // namespace QPS
