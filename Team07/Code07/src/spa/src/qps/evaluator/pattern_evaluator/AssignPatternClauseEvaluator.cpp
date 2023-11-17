#include "AssignPatternClauseEvaluator.h"

#include "qps/algorithm/SubstringComputer.h"

namespace QPS {

namespace {

bool isSubstring(const std::vector<std::string>& smaller,
                 const std::vector<std::string>& larger) {
  SubstringComputer<std::vector<std::string>> substringComputer;
  return substringComputer.isSubstring(smaller, larger);
}

bool match(const Argument& arg, const std::vector<std::string>& expr) {
  switch (arg.getArgumentType()) {
    case Argument::ArgumentType::WILDCARD:
      return true;
    case Argument::ArgumentType::EXPR: {
      auto [argExpr, exactMatch] =
          std::pair<std::vector<std::string>, bool>(arg);
      if (exactMatch && argExpr != expr)
        return false;
      if (!exactMatch && !isSubstring(argExpr, expr))
        return false;
      return true;
    }
    default:
      return false;
  }
}

}  // namespace

AssignPatternClauseEvaluator::AssignPatternClauseEvaluator(
    const std::shared_ptr<Declaration>& declaration, const QPS::Argument& arg1,
    const QPS::Argument& arg2)
    : PatternClauseEvaluator(declaration, arg1), arg2(arg2) {}

Table AssignPatternClauseEvaluator::evaluateWildcard(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage) {
  if (arg2.getArgumentType() != Argument::ArgumentType::WILDCARD)
    return PatternClauseEvaluator::evaluateWildcard(pkb, dataStorage);

  // special wildcard logic because every form of assign must be var = expr, but
  // not the case for if and while
  if (hasPattern(pkb))
    return {};
  else
    return EMPTY_TABLE;
}

bool AssignPatternClauseEvaluator::hasPattern(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb) {
  return !pkb->getAssignPatterns().empty();
}

std::vector<std::vector<int>> AssignPatternClauseEvaluator::getPatterns(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage) {
  std::vector<std::vector<int>> rows;

  auto& patterns = pkb->getAssignPatterns();

  for (auto& [lhs, vec] : patterns) {
    int sId = dataStorage->encodeString(lhs);
    for (auto& [rhs, stmtNum] : vec) {
      if (!match(arg2, rhs))
        continue;
      rows.push_back({dataStorage->encodeInt(stmtNum), sId});
    }
  }

  return rows;
}

std::vector<int> AssignPatternClauseEvaluator::getPatternStatementByValue(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  std::vector<int> res;

  for (auto& [expr, stmtNum] : pkb->getAssignFirstArgPatterns(arg)) {
    if (!match(arg2, expr))
      continue;
    res.emplace_back(dataStorage->encodeInt(stmtNum));
  }

  return res;
}

}  // namespace QPS
