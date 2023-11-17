#include "WithClause.h"

#include "qps/evaluator/with_evaluator/WithClauseEvaluator.h"

#include <memory>
#include <vector>

namespace QPS {
namespace {

enum class AttrType { NAME, INTEGER, INVALID };

AttrType getArgumentAttrType(const QPS::Argument& arg) {
  const Argument::ArgumentType& argType = arg.getArgumentType();
  if (argType == Argument::ArgumentType::STRING)
    return AttrType::NAME;
  else if (argType == Argument::ArgumentType::INTEGER)
    return AttrType::INTEGER;
  else if (argType == Argument::ArgumentType::SYNONYM) {
    const auto declPtr = std::shared_ptr<Declaration>(arg);
    if (declPtr == nullptr)
      return AttrType::INVALID;

    if (declPtr->type() == Declaration::Type::NAME)
      return AttrType::NAME;
    else
      return AttrType::INTEGER;
  }
  return AttrType::INVALID;
}

}  // namespace

WithClause::WithClause(const QPS::Argument& arg1, const QPS::Argument& arg2)
    : arg1(arg1), arg2(arg2) {}

std::shared_ptr<Evaluator> WithClause::createEvaluator() const {
  return std::make_shared<WithClauseEvaluator>(arg1, arg2);
}

bool WithClause::validate() const {
  AttrType attr1 = getArgumentAttrType(arg1), attr2 = getArgumentAttrType(arg2);
  return attr1 != AttrType::INVALID && attr2 != AttrType::INVALID &&
         attr1 == attr2;
}

std::vector<std::shared_ptr<Declaration>> WithClause::synonyms() const {
  std::vector<std::shared_ptr<Declaration>> res;
  if (arg1.getArgumentType() == Argument::ArgumentType::SYNONYM)
    res.push_back(arg1);
  if (arg2.getArgumentType() == Argument::ArgumentType::SYNONYM)
    res.push_back(arg2);
  return res;
}

}  // namespace QPS
