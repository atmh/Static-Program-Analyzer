#include "sp/extractor_adapter/adapters/EntityAdapters/ReadEntityAdapter.h"

namespace SP {
ReadEntityAdapter::ReadEntityAdapter(
    const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
    : ExtractorAdapter(pkb) {}

void ReadEntityAdapter::adapt(std::vector<std::shared_ptr<ReadNode>> reads) {
  for (const auto& read : reads) {
    pkb->addReadEntity(read->stmtNo, read->name);
    pkb->addVariableEntity(read->name);
  }
}
}  // namespace SP
