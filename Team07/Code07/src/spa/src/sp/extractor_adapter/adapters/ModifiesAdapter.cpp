#include "sp/extractor_adapter/adapters/ModifiesAdapter.h"

namespace SP {
ModifiesAdapter::ModifiesAdapter(
    const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
    : ExtractorAdapter(pkb) {}

// every statement will be under a procedure. so we can just iterate through
// the procedures and add the modifies relationship
void ModifiesAdapter::adapt(
    std::unordered_map<std::shared_ptr<StmtNode>,
                       std::unordered_set<std::string>>
        modifiesS,
    std::unordered_map<std::string, std::unordered_set<std::string>>
        modifiesP) {
  for (const auto& [procedure, v] : modifiesP) {
    for (const auto& var : v) {
      pkb->addModifiesProcedureRelationship(procedure, var);
    }
  }

  for (const auto& [stmt, v] : modifiesS) {
    for (const auto& var : v) {
      pkb->addModifiesStatementRelationship(stmt->stmtNo, var);
    }
  }
}
}  // namespace SP
