#pragma once

#include "qps/query/clauses/Argument.h"
#include "qps/query/clauses/Clause.h"

namespace QPS {

class WithClause : public Clause {
 public:
  WithClause(const Argument& arg1, const Argument& arg2);

  virtual std::shared_ptr<Evaluator> createEvaluator() const override;

  virtual bool validate() const override;

  virtual ~WithClause() = default;

  virtual std::vector<std::shared_ptr<Declaration>> synonyms() const override;

 private:
  Argument arg1;
  Argument arg2;
};

}  // namespace QPS
