#include "sp/extractor_adapter/adapters/ParentAdapter.h"

namespace SP {
ParentAdapter::ParentAdapter(
    const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
    : ExtractorAdapter(pkb) {}

void ParentAdapter::adapt(
    std::vector<std::pair<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>>>
        parentRelationships) {
  for (const auto& pair : parentRelationships) {
    pkb->addParentRelationship(pair.first->stmtNo, pair.second->stmtNo);
  }
}
}  // namespace SP
