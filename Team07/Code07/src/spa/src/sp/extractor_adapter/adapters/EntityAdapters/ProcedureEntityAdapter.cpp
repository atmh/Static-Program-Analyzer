#include "sp/extractor_adapter/adapters/EntityAdapters/ProcedureEntityAdapter.h"

namespace SP {
ProcedureEntityAdapter::ProcedureEntityAdapter(
    const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
    : ExtractorAdapter(pkb) {}

void ProcedureEntityAdapter::adapt(
    std::vector<std::shared_ptr<ProcedureNode>> procedures) {
  for (const auto& procedure : procedures) {
    pkb->addProcedureEntity(procedure->name);
  }
}
}  // namespace SP
