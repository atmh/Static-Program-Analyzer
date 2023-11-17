#pragma once

#include <memory>
#include <optional>
#include <typeindex>

#include "qps/evaluator/pattern_evaluator/AssignPatternClauseEvaluator.h"
#include "qps/query/clauses/Argument.h"
#include "qps/query/clauses/Clause.h"
#include "qps/query/declaration/AssignDeclaration.h"
#include "qps/query/declaration/IfDeclaration.h"
#include "qps/query/declaration/WhileDeclaration.h"

namespace QPS {

class Assign;
class If;
class While;

template <typename PatternType>
class PatternClause : public Clause {
 public:
  PatternClause(const std::shared_ptr<Declaration>& declaration,
                const Argument& arg1)
      : declaration(declaration), arg1(arg1) {}

  PatternClause(const std::shared_ptr<Declaration>& declaration,
                const Argument& arg1, const Argument& arg2)
      : declaration(declaration), arg1(arg1), optionalArg2(arg2) {}

  virtual std::shared_ptr<Evaluator> createEvaluator() const override;

  virtual bool validate() const override;

  virtual ~PatternClause() = default;

  virtual std::vector<std::shared_ptr<Declaration>> synonyms() const override;

 private:
  const static std::type_index allowedDeclarationType;
  std::shared_ptr<Declaration> declaration;
  Argument arg1;
  std::optional<Argument> optionalArg2;

  bool validateArg1() const;
  bool validateArg2() const;
};

}  // namespace QPS
