#include "PatternClauseEvaluator.h"

namespace QPS {

PatternClauseEvaluator::PatternClauseEvaluator(
    const std::shared_ptr<Declaration>& declaration, const Argument& arg1)
    : declaration(declaration), arg1(arg1), evalFunc(getEvalFunc(arg1)) {}

Table PatternClauseEvaluator::evaluate(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  return (this->*evalFunc)(pkb, dataStorage);
}

/**
 * These switch statements are used in the constructor! Not violating G7.
 */
PatternClauseEvaluator::EvalFuncType PatternClauseEvaluator::getEvalFunc(
    const QPS::Argument& arg1) {
  switch (arg1.getArgumentType()) {
    case Argument::ArgumentType::SYNONYM:
      return &PatternClauseEvaluator::evaluateSynonym;
    case Argument::ArgumentType::STRING:
      return &PatternClauseEvaluator::evaluateValue;
    case Argument::ArgumentType::WILDCARD:
      return &PatternClauseEvaluator::evaluateWildcard;
    default:
      assert(false);
      return {};
  }
}

Table PatternClauseEvaluator::evaluateSynonym(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage) {
  std::shared_ptr<Declaration> decl = declaration;
  std::shared_ptr<Declaration> synonym = arg1;

  std::vector<std::string> columns{decl->name(), synonym->name()};

  return Table{columns, getPatterns(pkb, dataStorage)};
}

Table PatternClauseEvaluator::evaluateValue(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage) {
  return Table{{{declaration->name(),
                 getPatternStatementByValue(pkb, dataStorage, arg1)}}};
}

Table PatternClauseEvaluator::evaluateWildcard(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage) {
  auto res = getPatterns(pkb, dataStorage);
  std::unordered_set<int> s;
  for (auto& v : res) {
    assert(v.size() == 2 &&
           "Column len should be 2 for result returned by getPatterns");
    s.insert(v[0]);
  }
  return Table{{{declaration->name(), {s.begin(), s.end()}}}};
}

PatternClauseEvaluator::~PatternClauseEvaluator() = default;

}  // namespace QPS