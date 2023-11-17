#include "sp/extractor_adapter/adapters/CallAdapter.h"

namespace SP {
CallAdapter::CallAdapter(
    const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
    : ExtractorAdapter{pkb} {}

void CallAdapter::adapt(
    const std::vector<
        std::pair<std::shared_ptr<ProcedureNode>, std::shared_ptr<CallNode>>>&
        callRelationships) {
  for (const auto& [key, val] : callRelationships) {
    pkb->addCallsRelationship(key->name, val->name);
  }
}
}  // namespace SP
