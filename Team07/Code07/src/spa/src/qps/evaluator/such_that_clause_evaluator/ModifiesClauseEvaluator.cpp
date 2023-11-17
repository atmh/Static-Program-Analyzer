#include "ModifiesClauseEvaluator.h"

namespace QPS {

namespace {

enum class ModifiesClauseArgumentType {
  STATEMENT,
  PROCEDURE,
};

ModifiesClauseArgumentType getModifiesClauseArgumentType(const Argument& arg) {
  switch (arg.getArgumentType()) {
    case Argument::ArgumentType::INTEGER:
      return ModifiesClauseArgumentType::STATEMENT;
    case Argument::ArgumentType::STRING:
      return ModifiesClauseArgumentType::PROCEDURE;
    case Argument::ArgumentType::SYNONYM: {
      // we could use a visitor here but seems quite redundant to me
      if (std::dynamic_pointer_cast<ProcedureDeclaration>(
              std::shared_ptr<Declaration>(arg)))
        return ModifiesClauseArgumentType::PROCEDURE;
      else
        return ModifiesClauseArgumentType::STATEMENT;
    }
    default:
      assert(false);
      return ModifiesClauseArgumentType::STATEMENT;
  }
}

}  // namespace

bool ModifiesClauseEvaluator::doHasRelationship(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb) {
  assert(false && "Modifies clause does not require hasRelationship API");
  switch (getModifiesClauseArgumentType(arg1)) {
    case ModifiesClauseArgumentType::STATEMENT: {
      return pkb->hasModifiesStatementRelationship();
    }
    case ModifiesClauseArgumentType::PROCEDURE: {
      return pkb->hasModifiesProcedureRelationship();
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
bool ModifiesClauseEvaluator::getRelationshipExists(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache, const Argument& arg1,
    const Argument& arg2) {
  switch (getModifiesClauseArgumentType(arg1)) {
    case ModifiesClauseArgumentType::STATEMENT: {
      return pkb->getModifiesStatementRelationshipExists(arg1, arg2);
    }
    case ModifiesClauseArgumentType::PROCEDURE: {
      return pkb->getModifiesProcedureRelationshipExists(arg1, arg2);
    }
    default:
      assert(false);
      return false;
  }
}

std::unordered_set<int> ModifiesClauseEvaluator::doGetFirstArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  switch (getModifiesClauseArgumentType(arg)) {
    case ModifiesClauseArgumentType::STATEMENT: {
      return dataStorage->encodeStrings(
          pkb->getModifiesStatementFirstArgRelationships(arg));
    }
    case ModifiesClauseArgumentType::PROCEDURE: {
      return dataStorage->encodeStrings(
          pkb->getModifiesProcedureFirstArgRelationships(arg));
    }
    default:
      assert(false);
      return {};
  }
}

std::unordered_set<int> ModifiesClauseEvaluator::doGetSecondArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  switch (getModifiesClauseArgumentType(arg1)) {
    case ModifiesClauseArgumentType::STATEMENT: {
      return dataStorage->encodeInts(
          pkb->getModifiesStatementSecondArgRelationships(arg));
    }
    case ModifiesClauseArgumentType::PROCEDURE: {
      return dataStorage->encodeStrings(
          pkb->getModifiesProcedureSecondArgRelationships(arg));
    }
    default:
      assert(false);
      return {};
  }
}

}  // namespace QPS
