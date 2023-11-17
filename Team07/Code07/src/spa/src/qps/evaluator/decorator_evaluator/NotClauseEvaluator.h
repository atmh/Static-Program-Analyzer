#pragma once

#include <memory>
#include <string>
#include <vector>

#include "qps/evaluator/Evaluator.h"
#include "qps/query/clauses/Clause.h"
#include "qps/query/declaration/Declaration.h"

namespace QPS {

class NotClauseEvaluator : public Evaluator {
 public:
  NotClauseEvaluator(const std::shared_ptr<Clause>& clause,
                     const std::vector<std::shared_ptr<Declaration>>& synonyms);

  virtual Table evaluate(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache = nullptr) override;

  virtual ~NotClauseEvaluator() = default;

 private:
  std::shared_ptr<Clause> clause;
  std::vector<std::shared_ptr<Declaration>> synonyms;
};

}  // namespace QPS
