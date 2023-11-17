#include "sp/extractor_adapter/adapters/EntityAdapters/AssignEntityAdapter.h"

namespace SP {
AssignEntityAdapter::AssignEntityAdapter(
    const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
    : ExtractorAdapter(pkb) {}

void AssignEntityAdapter::adapt(
    std::vector<std::shared_ptr<AssignNode>> assigns) {
  for (const auto& assign : assigns) {
    pkb->addAssignEntity(assign->stmtNo);
    pkb->addVariableEntity(assign->name);
    pkb->addAssignPattern(assign->stmtNo, assign->name, assign->postfix);

    for (const auto& var : assign->exprVar) {
      pkb->addVariableEntity(var);
    }

    for (const auto& constant : assign->exprCon) {
      pkb->addConstantEntity(constant);
    }
  }
}
}  // namespace SP
