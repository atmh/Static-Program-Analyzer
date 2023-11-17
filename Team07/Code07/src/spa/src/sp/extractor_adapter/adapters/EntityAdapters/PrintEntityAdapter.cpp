#include "sp/extractor_adapter/adapters/EntityAdapters/PrintEntityAdapter.h"

namespace SP {
PrintEntityAdapter::PrintEntityAdapter(
    const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
    : ExtractorAdapter(pkb) {}

void PrintEntityAdapter::adapt(std::vector<std::shared_ptr<PrintNode>> prints) {
  for (const auto& print : prints) {
    pkb->addPrintEntity(print->stmtNo, print->name);
    pkb->addVariableEntity(print->name);
  }
}
}  // namespace SP
