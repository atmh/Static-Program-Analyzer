#pragma once

#include <memory>

#include "qps/query/clauses/Clause.h"

namespace QPS {

class NotClause : public Clause {
 public:
  NotClause(const std::shared_ptr<Clause>& clause);

  virtual std::shared_ptr<Evaluator> createEvaluator() const override;

  virtual bool validate() const override;

  virtual std::vector<std::shared_ptr<Declaration>> synonyms() const override;

  virtual size_t doEstimatedCost(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache) override;

  virtual ~NotClause() = default;

 private:
  std::shared_ptr<Clause> clause;
};

}  // namespace QPS
