#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "qps/query/Validateable.h"
#include "qps/query/clauses/Clause.h"
#include "qps/query/select/SelectClause.h"

namespace QPS {

class Query : public EvaluatorFactory, public Validateable {
 public:
  Query();
  explicit Query(SelectClause select_clause);

  Table evaluate(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache = nullptr);

  const SelectClause& getSelectClause() const noexcept;

  QueryResult select(
      const Table& table,
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage) const;

  const std::vector<std::shared_ptr<Clause>>& getClauses() const noexcept;

  bool isValid() const noexcept;

  void addClause(const std::shared_ptr<Clause>& clause);

  virtual bool validate() const override;

  virtual std::shared_ptr<Evaluator> createEvaluator() const override;

 private:
  SelectClause selectClause;
  std::vector<std::shared_ptr<Clause>> clauses;
  bool valid;
};

}  // namespace QPS
