#include "sp/extractor_adapter/adapters/EntityAdapters/CallEntityAdapter.h"

namespace SP {
CallEntityAdapter::CallEntityAdapter(
    const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
    : ExtractorAdapter(pkb) {}

void CallEntityAdapter::adapt(std::vector<std::shared_ptr<CallNode>> calls) {
  for (const auto& call : calls) {
    pkb->addCallEntity(call->stmtNo, call->name);
  }
}
}  // namespace SP
