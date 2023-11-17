#include "sp/extractor_adapter/adapters/EntityAdapters/WhileEntityAdapter.h"

namespace SP {
WhileEntityAdapter::WhileEntityAdapter(
    const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
    : ExtractorAdapter(pkb) {}

void WhileEntityAdapter::adapt(std::vector<std::shared_ptr<WhileNode>> whiles) {
  for (const auto& whileNode : whiles) {
    pkb->addWhileEntity(whileNode->stmtNo);
    for (const auto& constant : whileNode->exprCon) {
      pkb->addConstantEntity(constant);
    }

    for (const auto& variable : whileNode->exprVar) {
      pkb->addVariableEntity(variable);
      pkb->addWhilePattern(whileNode->stmtNo, variable);
    }
  }
}
}  // namespace SP
