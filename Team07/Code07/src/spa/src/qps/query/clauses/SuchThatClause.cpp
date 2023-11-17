#include "SuchThatClause.h"

#include "qps/evaluator/such_that_clause_evaluator/AffectsClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/CallsClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/CallsStarClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/FollowsClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/FollowsStarClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/ModifiesClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/NextClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/NextStarClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/ParentClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/ParentStarClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/UsesClauseEvaluator.h"

namespace QPS {

namespace {

template <typename Relationship>
struct EvaluatorGetter;

template <>
struct EvaluatorGetter<FollowsRelationship> {
  using EvaluatorType = FollowsClauseEvaluator;
};

template <>
struct EvaluatorGetter<FollowsStarRelationship> {
  using EvaluatorType = FollowsStarClauseEvaluator;
};

template <>
struct EvaluatorGetter<ParentRelationship> {
  using EvaluatorType = ParentClauseEvaluator;
};

template <>
struct EvaluatorGetter<ParentStarRelationship> {
  using EvaluatorType = ParentStarClauseEvaluator;
};

template <>
struct EvaluatorGetter<UsesRelationship> {
  using EvaluatorType = UsesClauseEvaluator;
};

template <>
struct EvaluatorGetter<ModifiesRelationship> {
  using EvaluatorType = ModifiesClauseEvaluator;
};

template <>
struct EvaluatorGetter<CallsRelationship> {
  using EvaluatorType = CallsClauseEvaluator;
};

template <>
struct EvaluatorGetter<CallsStarRelationship> {
  using EvaluatorType = CallsStarClauseEvaluator;
};

template <>
struct EvaluatorGetter<NextRelationship> {
  using EvaluatorType = NextClauseEvaluator;
};

template <>
struct EvaluatorGetter<NextStarRelationship> {
  using EvaluatorType = NextStarClauseEvaluator;
};

template <>
struct EvaluatorGetter<AffectsRelationship> {
  using EvaluatorType = AffectsClauseEvaluator;
};

template <typename Relationship>
using get_evaluator = typename EvaluatorGetter<Relationship>::EvaluatorType;

}  // namespace

template <typename Relationship>
std::shared_ptr<Evaluator> SuchThatClause<Relationship>::createEvaluator()
    const {
  return std::make_shared<get_evaluator<Relationship>>(arg1, arg2);
}

template class SuchThatClause<FollowsRelationship>;
template <>
const std::set<std::type_index>
    SuchThatClause<FollowsRelationship>::allowedArg1Declarations{
        typeid(StatementDeclaration), typeid(ReadDeclaration),
        typeid(PrintDeclaration),     typeid(AssignDeclaration),
        typeid(WhileDeclaration),     typeid(IfDeclaration),
        typeid(CallDeclaration)};
template <>
const std::set<std::type_index>
    SuchThatClause<FollowsRelationship>::allowedArg2Declarations{
        typeid(StatementDeclaration), typeid(ReadDeclaration),
        typeid(PrintDeclaration),     typeid(AssignDeclaration),
        typeid(WhileDeclaration),     typeid(IfDeclaration),
        typeid(CallDeclaration)};
template <>
bool SuchThatClause<FollowsRelationship>::validate() const {
  return validateArgDeclarations() && validateStmtRef(arg1) &&
         validateStmtRef(arg2);
}

template class SuchThatClause<FollowsStarRelationship>;
template <>
const std::set<std::type_index>
    SuchThatClause<FollowsStarRelationship>::allowedArg1Declarations{
        typeid(StatementDeclaration), typeid(ReadDeclaration),
        typeid(PrintDeclaration),     typeid(AssignDeclaration),
        typeid(WhileDeclaration),     typeid(IfDeclaration),
        typeid(CallDeclaration)};
template <>
const std::set<std::type_index>
    SuchThatClause<FollowsStarRelationship>::allowedArg2Declarations{
        typeid(StatementDeclaration), typeid(ReadDeclaration),
        typeid(PrintDeclaration),     typeid(AssignDeclaration),
        typeid(WhileDeclaration),     typeid(IfDeclaration),
        typeid(CallDeclaration)};
template <>
bool SuchThatClause<FollowsStarRelationship>::validate() const {
  return validateArgDeclarations() && validateStmtRef(arg1) &&
         validateStmtRef(arg2);
}

template class SuchThatClause<ParentRelationship>;
template <>
const std::set<std::type_index>
    SuchThatClause<ParentRelationship>::allowedArg1Declarations{
        typeid(StatementDeclaration), typeid(ReadDeclaration),
        typeid(PrintDeclaration),     typeid(AssignDeclaration),
        typeid(WhileDeclaration),     typeid(IfDeclaration),
        typeid(CallDeclaration)};
template <>
const std::set<std::type_index>
    SuchThatClause<ParentRelationship>::allowedArg2Declarations{
        typeid(StatementDeclaration), typeid(ReadDeclaration),
        typeid(PrintDeclaration),     typeid(AssignDeclaration),
        typeid(WhileDeclaration),     typeid(IfDeclaration),
        typeid(CallDeclaration)};
template <>
bool SuchThatClause<ParentRelationship>::validate() const {
  return validateArgDeclarations() && validateStmtRef(arg1) &&
         validateStmtRef(arg2);
}

template class SuchThatClause<ParentStarRelationship>;
template <>
const std::set<std::type_index>
    SuchThatClause<ParentStarRelationship>::allowedArg1Declarations{
        typeid(StatementDeclaration), typeid(ReadDeclaration),
        typeid(PrintDeclaration),     typeid(AssignDeclaration),
        typeid(WhileDeclaration),     typeid(IfDeclaration),
        typeid(CallDeclaration)};
template <>
const std::set<std::type_index>
    SuchThatClause<ParentStarRelationship>::allowedArg2Declarations{
        typeid(StatementDeclaration), typeid(ReadDeclaration),
        typeid(PrintDeclaration),     typeid(AssignDeclaration),
        typeid(WhileDeclaration),     typeid(IfDeclaration),
        typeid(CallDeclaration)};
template <>
bool SuchThatClause<ParentStarRelationship>::validate() const {
  return validateArgDeclarations() && validateStmtRef(arg1) &&
         validateStmtRef(arg2);
}

template class SuchThatClause<UsesRelationship>;
template <>
const std::set<std::type_index>
    SuchThatClause<UsesRelationship>::allowedArg1Declarations{
        typeid(ReadDeclaration),      typeid(PrintDeclaration),
        typeid(AssignDeclaration),    typeid(WhileDeclaration),
        typeid(IfDeclaration),        typeid(CallDeclaration),
        typeid(ProcedureDeclaration), typeid(StatementDeclaration)};
template <>
const std::set<std::type_index>
    SuchThatClause<UsesRelationship>::allowedArg2Declarations{
        typeid(VariableDeclaration)};
template <>
bool SuchThatClause<UsesRelationship>::validate() const {
  return validateArgDeclarations() &&
         (validateStmtRef(arg1) || validateEntRef(arg1)) &&
         validateEntRef(arg2) &&
         arg1.getArgumentType() != Argument::ArgumentType::WILDCARD;
}

template class SuchThatClause<ModifiesRelationship>;
template <>
const std::set<std::type_index>
    SuchThatClause<ModifiesRelationship>::allowedArg1Declarations{
        typeid(ReadDeclaration),      typeid(PrintDeclaration),
        typeid(AssignDeclaration),    typeid(WhileDeclaration),
        typeid(IfDeclaration),        typeid(CallDeclaration),
        typeid(ProcedureDeclaration), typeid(StatementDeclaration)};
template <>
const std::set<std::type_index>
    SuchThatClause<ModifiesRelationship>::allowedArg2Declarations{
        typeid(VariableDeclaration)};
template <>
bool SuchThatClause<ModifiesRelationship>::validate() const {
  return validateArgDeclarations() &&
         (validateStmtRef(arg1) || validateEntRef(arg1)) &&
         validateEntRef(arg2) &&
         arg1.getArgumentType() != Argument::ArgumentType::WILDCARD;
}

template class SuchThatClause<CallsRelationship>;
template <>
const std::set<std::type_index>
    SuchThatClause<CallsRelationship>::allowedArg1Declarations{
        typeid(ProcedureDeclaration)};
template <>
const std::set<std::type_index>
    SuchThatClause<CallsRelationship>::allowedArg2Declarations{
        typeid(ProcedureDeclaration)};
template <>
bool SuchThatClause<CallsRelationship>::validate() const {
  return validateArgDeclarations() && validateEntRef(arg1) &&
         validateEntRef(arg2);
}

template class SuchThatClause<CallsStarRelationship>;
template <>
const std::set<std::type_index>
    SuchThatClause<CallsStarRelationship>::allowedArg1Declarations{
        typeid(ProcedureDeclaration)};
template <>
const std::set<std::type_index>
    SuchThatClause<CallsStarRelationship>::allowedArg2Declarations{
        typeid(ProcedureDeclaration)};
template <>
bool SuchThatClause<CallsStarRelationship>::validate() const {
  return validateArgDeclarations() && validateEntRef(arg1) &&
         validateEntRef(arg2);
}

template class SuchThatClause<NextRelationship>;
template <>
const std::set<std::type_index>
    SuchThatClause<NextRelationship>::allowedArg1Declarations{
        typeid(StatementDeclaration), typeid(ReadDeclaration),
        typeid(PrintDeclaration),     typeid(AssignDeclaration),
        typeid(WhileDeclaration),     typeid(IfDeclaration),
        typeid(CallDeclaration)};
template <>
const std::set<std::type_index>
    SuchThatClause<NextRelationship>::allowedArg2Declarations{
        typeid(StatementDeclaration), typeid(ReadDeclaration),
        typeid(PrintDeclaration),     typeid(AssignDeclaration),
        typeid(WhileDeclaration),     typeid(IfDeclaration),
        typeid(CallDeclaration)};
template <>
bool SuchThatClause<NextRelationship>::validate() const {
  return validateArgDeclarations() && validateStmtRef(arg1) &&
         validateStmtRef(arg2);
}

template class SuchThatClause<NextStarRelationship>;
template <>
const std::set<std::type_index>
    SuchThatClause<NextStarRelationship>::allowedArg1Declarations{
        typeid(StatementDeclaration), typeid(ReadDeclaration),
        typeid(PrintDeclaration),     typeid(AssignDeclaration),
        typeid(WhileDeclaration),     typeid(IfDeclaration),
        typeid(CallDeclaration)};
template <>
const std::set<std::type_index>
    SuchThatClause<NextStarRelationship>::allowedArg2Declarations{
        typeid(StatementDeclaration), typeid(ReadDeclaration),
        typeid(PrintDeclaration),     typeid(AssignDeclaration),
        typeid(WhileDeclaration),     typeid(IfDeclaration),
        typeid(CallDeclaration)};
template <>
bool SuchThatClause<NextStarRelationship>::validate() const {
  return validateArgDeclarations() && validateStmtRef(arg1) &&
         validateStmtRef(arg2);
}

template class SuchThatClause<AffectsRelationship>;
template <>
const std::set<std::type_index>
    SuchThatClause<AffectsRelationship>::allowedArg1Declarations{
        typeid(StatementDeclaration), typeid(ReadDeclaration),
        typeid(PrintDeclaration),     typeid(AssignDeclaration),
        typeid(WhileDeclaration),     typeid(IfDeclaration),
        typeid(CallDeclaration)};
template <>
const std::set<std::type_index>
    SuchThatClause<AffectsRelationship>::allowedArg2Declarations{
        typeid(StatementDeclaration), typeid(ReadDeclaration),
        typeid(PrintDeclaration),     typeid(AssignDeclaration),
        typeid(WhileDeclaration),     typeid(IfDeclaration),
        typeid(CallDeclaration)};
template <>
bool SuchThatClause<AffectsRelationship>::validate() const {
  return validateArgDeclarations() && validateStmtRef(arg1) &&
         validateStmtRef(arg2);
}

template <typename Relationship>
bool SuchThatClause<Relationship>::validateArgDeclarations() const {
  return (arg1.getArgumentType() != Argument::ArgumentType::SYNONYM ||
          std::shared_ptr<Declaration>(arg1) != nullptr &&
              allowedArg1Declarations.find(typeid(*std::shared_ptr<Declaration>(
                  arg1))) != allowedArg1Declarations.end()) &&
         (arg2.getArgumentType() != Argument::ArgumentType::SYNONYM ||
          std::shared_ptr<Declaration>(arg2) != nullptr &&
              allowedArg2Declarations.find(typeid(*std::shared_ptr<Declaration>(
                  arg2))) != allowedArg2Declarations.end());
}

template <typename Relationship>
std::vector<std::shared_ptr<Declaration>>
SuchThatClause<Relationship>::synonyms() const {
  std::vector<std::shared_ptr<Declaration>> res;
  if (arg1.getArgumentType() == Argument::ArgumentType::SYNONYM)
    res.push_back(arg1);
  if (arg2.getArgumentType() == Argument::ArgumentType::SYNONYM)
    res.push_back(arg2);
  return res;
}

}  // namespace QPS
