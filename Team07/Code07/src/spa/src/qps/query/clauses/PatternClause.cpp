#include "PatternClause.h"

#include <memory>

#include "qps/evaluator/pattern_evaluator/IfPatternClauseEvaluator.h"
#include "qps/evaluator/pattern_evaluator/WhilePatternClauseEvaluator.h"
#include "qps/query/declaration/VariableDeclaration.h"

namespace QPS {

namespace {

template <typename PatternType>
struct EvaluatorGetter;

template <>
struct EvaluatorGetter<Assign> {
  using EvaluatorType = AssignPatternClauseEvaluator;
};

template <>
struct EvaluatorGetter<If> {
  using EvaluatorType = IfPatternClauseEvaluator;
};

template <>
struct EvaluatorGetter<While> {
  using EvaluatorType = WhilePatternClauseEvaluator;
};

template <typename Relationship>
using get_evaluator = typename EvaluatorGetter<Relationship>::EvaluatorType;

}  // namespace

template <typename PatternType>
std::shared_ptr<Evaluator> PatternClause<PatternType>::createEvaluator() const {
  return std::make_shared<get_evaluator<PatternType>>(declaration, arg1);
}

template <>
std::shared_ptr<Evaluator> PatternClause<Assign>::createEvaluator() const {
  return std::make_shared<get_evaluator<Assign>>(declaration, arg1,
                                                 *optionalArg2);
}

template <typename PatternType>
std::vector<std::shared_ptr<Declaration>> PatternClause<PatternType>::synonyms()
    const {
  assert(declaration && "Declaration of pattern clause must not be null!");
  std::vector<std::shared_ptr<Declaration>> res{declaration};
  if (arg1.getArgumentType() == Argument::ArgumentType::SYNONYM)
    res.push_back(arg1);
  if (optionalArg2 &&
      optionalArg2->getArgumentType() == Argument::ArgumentType::SYNONYM)
    res.push_back(*optionalArg2);
  return res;
}

template class PatternClause<If>;

template <>
const std::type_index PatternClause<If>::allowedDeclarationType{
    typeid(IfDeclaration)};

template class PatternClause<While>;

template <>
const std::type_index PatternClause<While>::allowedDeclarationType{
    typeid(WhileDeclaration)};

template class PatternClause<Assign>;

template <>
const std::type_index PatternClause<Assign>::allowedDeclarationType{
    typeid(AssignDeclaration)};

template <typename PatternType>
bool PatternClause<PatternType>::validateArg1() const {
  return validateEntRef(arg1) &&
         (arg1.getArgumentType() != Argument::ArgumentType::SYNONYM ||
          std::shared_ptr<Declaration>(arg1) != nullptr &&
              typeid(*std::shared_ptr<Declaration>(arg1)) ==
                  typeid(VariableDeclaration));
}

template <>
bool PatternClause<Assign>::validateArg2() const {
  return optionalArg2 && validateExpr(*optionalArg2);
  ;
}

template <typename PatternType>
bool PatternClause<PatternType>::validateArg2() const {
  return !optionalArg2;
}

template <typename PatternType>
bool PatternClause<PatternType>::validate() const {
  return declaration != nullptr &&
         std::type_index(typeid(*declaration)) == allowedDeclarationType &&
         validateArg1() && validateArg2();
}

}  // namespace QPS
