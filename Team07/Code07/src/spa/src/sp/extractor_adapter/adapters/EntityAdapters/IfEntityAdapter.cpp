#include "sp/extractor_adapter/adapters/EntityAdapters/IfEntityAdapter.h"

namespace SP {
IfEntityAdapter::IfEntityAdapter(
    const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
    : ExtractorAdapter(pkb) {}

void IfEntityAdapter::adapt(std::vector<std::shared_ptr<IfNode>> ifs) {
  for (const auto& ifNode : ifs) {
    pkb->addIfEntity(ifNode->stmtNo);
    for (const auto& constant : ifNode->exprCon) {
      pkb->addConstantEntity(constant);
    }

    for (const auto& variable : ifNode->exprVar) {
      pkb->addVariableEntity(variable);
      pkb->addIfPattern(ifNode->stmtNo, variable);
    }
  }
}
}  // namespace SP
