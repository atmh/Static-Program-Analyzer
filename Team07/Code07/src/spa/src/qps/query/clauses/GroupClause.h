#pragma once

#include <memory>
#include <vector>

#include "qps/query/clauses/Clause.h"
#include "qps/query/select/SelectClause.h"

namespace QPS {

/**
 * The purpose of this is to enable higher level of abstraction on the optimizer end.
 * It logically groups the clauses and abstracts out the grouping logic from the evaluator side.
 * The optimizer will do the grouping by taking in a vector of clauses and returning a vector of group clauses.
 * Since group clauses are clauses, it is transparent to the evaluator. This is a decorator class.
 */
class GroupClause : public Clause {
 public:
  GroupClause(const SelectClause& selectClause,
              const std::vector<std::shared_ptr<Clause>>& clauses);

  virtual std::shared_ptr<Evaluator> createEvaluator() const override;

  virtual bool validate() const override;

  virtual std::vector<std::shared_ptr<Declaration>> synonyms() const override;

  virtual size_t doEstimatedCost(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache) override;

  virtual ~GroupClause() = default;

 private:
  SelectClause selectClause;
  std::vector<std::shared_ptr<Clause>> clauses;
};

}  // namespace QPS
