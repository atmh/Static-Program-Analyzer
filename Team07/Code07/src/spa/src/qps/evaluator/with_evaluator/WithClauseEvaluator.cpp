#include "WithClauseEvaluator.h"

#include "qps/query/declaration/visitor/DeclarationSelector.h"
#include "qps/query/declaration/visitor/DeclarationStringSerializer.h"

#include <cassert>
#include <string>
#include <vector>

namespace QPS {

namespace {

// assumes that validator already made sure we won't compare int with string,
// so we can convert int into string version and just compare strings with strings
Table evalSingleSynonym(
    const std::shared_ptr<Declaration>& synonym, const Argument& val,
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage) {
  auto declSelector = DeclarationSelector{pkb, dataStorage};
  synonym->accept(declSelector);
  auto res = declSelector.getResult();

  std::vector<int> col;

  for (auto a : res) {
    DeclarationStringSerializer serializer{pkb, dataStorage, a};
    synonym->accept(serializer);
    auto valStr = val.getArgumentType() == Argument::ArgumentType::STRING
                      ? std::string(val)
                      : std::to_string(int(val));
    if (serializer.getResult() != valStr)
      continue;
    col.push_back(a);
  }

  return Table{{{synonym->name(), col}}};
}

}  // namespace

WithClauseEvaluator::WithClauseEvaluator(const Argument& arg1,
                                         const Argument& arg2)
    : arg1(arg1), arg2(arg2), evalFunc(getEvalFunc(arg1, arg2)) {}

Table WithClauseEvaluator::evaluate(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  return (this->*evalFunc)(pkb, dataStorage);
}

/**
 * These switch statements are used in the constructor! Not violating G7.
 */
WithClauseEvaluator::EvalFuncType WithClauseEvaluator::getEvalFunc(
    const QPS::Argument& arg1, const QPS::Argument& arg2) {
  assert(arg1.getArgumentType() != Argument::ArgumentType::WILDCARD &&
         arg2.getArgumentType() != Argument::ArgumentType::WILDCARD &&
         "Wild card not allowed in with clause");

  switch (arg1.getArgumentType()) {
    case Argument::ArgumentType::SYNONYM:
      return getSynonymEvalFunc(arg2);
    case Argument::ArgumentType::INTEGER:
    case Argument::ArgumentType::STRING:
      return getValueEvalFunc(arg2);
    default:
      assert(false && "Illegal with clause arg1 type, validator bug");
      return {};
  }
}

/**
 * These switch statements are used in the constructor! Not violating G7.
 */
WithClauseEvaluator::EvalFuncType WithClauseEvaluator::getSynonymEvalFunc(
    const QPS::Argument& arg2) {
  switch (arg2.getArgumentType()) {
    case Argument::ArgumentType::SYNONYM:
      return &WithClauseEvaluator::evalSynonymSynonym;
    case Argument::ArgumentType::INTEGER:
    case Argument::ArgumentType::STRING:
      return &WithClauseEvaluator::evalSynonymValue;
    default:
      assert(false && "Illegal with clause arg2 type, validator bug");
      return {};
  }
}

/**
 * These switch statements are used in the constructor! Not violating G7.
 */
WithClauseEvaluator::EvalFuncType WithClauseEvaluator::getValueEvalFunc(
    const QPS::Argument& arg2) {
  switch (arg2.getArgumentType()) {
    case Argument::ArgumentType::SYNONYM:
      return &WithClauseEvaluator::evalValueSynonym;
    case Argument::ArgumentType::INTEGER:
    case Argument::ArgumentType::STRING:
      return &WithClauseEvaluator::evalValueValue;
    default:
      assert(false && "Illegal with clause arg2 type, validator bug");
      return {};
  }
}

Table WithClauseEvaluator::evalValueValue(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage) {
  assert(arg1.getArgumentType() == arg2.getArgumentType() &&
         "arg1 and arg2 has to be of same type");
  if (arg1 == arg2) {
    return {};
  } else {
    return EMPTY_TABLE;
  }
}

Table WithClauseEvaluator::evalValueSynonym(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage) {
  return evalSingleSynonym(arg2, arg1, pkb, dataStorage);
}

Table WithClauseEvaluator::evalSynonymValue(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage) {
  return evalSingleSynonym(arg1, arg2, pkb, dataStorage);
}

Table WithClauseEvaluator::evalSynonymSynonym(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage) {
  std::shared_ptr<Declaration> decl1 = arg1;
  std::shared_ptr<Declaration> decl2 = arg2;

  if (*decl1 == *decl2) {
    auto declSelector = DeclarationSelector{pkb, dataStorage};
    decl1->accept(declSelector);
    auto res = declSelector.getResult();
    return Table{{{decl1->name(), {res.begin(), res.end()}}}};
  }

  auto declSelector = DeclarationSelector{pkb, dataStorage};
  decl1->accept(declSelector);
  auto res1 = declSelector.getResult();
  decl2->accept(declSelector);
  auto res2 = declSelector.getResult();

  std::vector<std::string> cols{decl1->name(), decl2->name()};
  std::vector<std::vector<int>> rows;

  for (auto a : res1) {
    for (auto b : res2) {
      DeclarationStringSerializer serializer1{pkb, dataStorage, a};
      DeclarationStringSerializer serializer2{pkb, dataStorage, b};
      decl1->accept(serializer1);
      decl2->accept(serializer2);
      if (serializer1.getResult() != serializer2.getResult())
        continue;
      rows.push_back({a, b});
    }
  }

  return Table{cols, rows};
}

}  // namespace QPS
