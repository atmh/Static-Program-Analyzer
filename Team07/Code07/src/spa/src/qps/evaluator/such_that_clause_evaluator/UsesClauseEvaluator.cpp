#include "UsesClauseEvaluator.h"

namespace QPS {

namespace {

enum class UsesClauseArgumentType {
  STATEMENT,
  PROCEDURE,
};

UsesClauseArgumentType getUsesClauseArgumentType(const Argument& arg) {
  switch (arg.getArgumentType()) {
    case Argument::ArgumentType::INTEGER:
      return UsesClauseArgumentType::STATEMENT;
    case Argument::ArgumentType::STRING:
      return UsesClauseArgumentType::PROCEDURE;
    case Argument::ArgumentType::SYNONYM: {
      // we could use a visitor here but seems quite redundant to me
      if (std::dynamic_pointer_cast<ProcedureDeclaration>(
              std::shared_ptr<Declaration>(arg)))
        return UsesClauseArgumentType::PROCEDURE;
      else
        return UsesClauseArgumentType::STATEMENT;
    }
    default:
      assert(false);
      return UsesClauseArgumentType::STATEMENT;
  }
}

}  // namespace

bool UsesClauseEvaluator::doHasRelationship(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb) {
  assert(false && "Uses clause does not require hasRelationship API");
  switch (getUsesClauseArgumentType(arg1)) {
    case UsesClauseArgumentType::STATEMENT: {
      return pkb->hasUsesStatementRelationship();
    }
    case UsesClauseArgumentType::PROCEDURE: {
      return pkb->hasUsesProcedureRelationship();
    }
    default:
      assert(false);
      return false;
  }
}

/**
 * Can't use a strategy of sorts because pkb method params
 * are different. Similar for the other methods.
 */
bool UsesClauseEvaluator::getRelationshipExists(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache, const Argument& arg1,
    const Argument& arg2) {
  switch (getUsesClauseArgumentType(arg1)) {
    case UsesClauseArgumentType::STATEMENT: {
      return pkb->getUsesStatementRelationshipExists(arg1, arg2);
    }
    case UsesClauseArgumentType::PROCEDURE: {
      return pkb->getUsesProcedureRelationshipExists(arg1, arg2);
    }
    default:
      assert(false);
      return false;
  }
}

std::unordered_set<int> UsesClauseEvaluator::doGetFirstArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  switch (getUsesClauseArgumentType(arg)) {
    case UsesClauseArgumentType::STATEMENT: {
      return dataStorage->encodeStrings(
          pkb->getUsesStatementFirstArgRelationships(arg));
    }
    case UsesClauseArgumentType::PROCEDURE: {
      return dataStorage->encodeStrings(
          pkb->getUsesProcedureFirstArgRelationships(arg));
    }
    default:
      assert(false);
      return {};
  }
}

std::unordered_set<int> UsesClauseEvaluator::doGetSecondArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  switch (getUsesClauseArgumentType(arg1)) {
    case UsesClauseArgumentType::STATEMENT: {
      return dataStorage->encodeInts(
          pkb->getUsesStatementSecondArgRelationships(arg));
    }
    case UsesClauseArgumentType::PROCEDURE: {
      return dataStorage->encodeStrings(
          pkb->getUsesProcedureSecondArgRelationships(arg));
    }
    default:
      assert(false);
      return {};
  }
}

}  // namespace QPS
