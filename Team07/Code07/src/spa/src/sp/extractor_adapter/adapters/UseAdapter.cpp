#include "sp/extractor_adapter/adapters/UseAdapter.h"

namespace SP {
UseAdapter::UseAdapter(
    const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
    : ExtractorAdapter(pkb) {}

void UseAdapter::adapt(
    std::unordered_map<std::shared_ptr<StmtNode>,
                       std::unordered_set<std::string>>
        usesS,
    std::unordered_map<std::string, std::unordered_set<std::string>> usesP) {
  for (const auto& [procedure, v] : usesP) {
    for (const auto& var : v) {
      pkb->addUsesProcedureRelationship(procedure, var);
    }
  }

  for (const auto& [stmt, v] : usesS) {
    for (const auto& var : v) {
      pkb->addUsesStatementRelationship(stmt->stmtNo, var);
    }
  }
}
}  // namespace SP
