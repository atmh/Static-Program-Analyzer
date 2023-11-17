#include "sp/extractor_adapter/adapters/NextAdapter.h"

namespace SP {
NextAdapter::NextAdapter(
    const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
    : ExtractorAdapter(pkb) {}

void NextAdapter::adapt(
    std::vector<std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>>>
        nextRelationships) {
  for (const auto& [s1, s2] : nextRelationships) {
    std::shared_ptr<StmtNode> stmt1 = std::dynamic_pointer_cast<StmtNode>(s1);
    std::shared_ptr<StmtNode> stmt2 = std::dynamic_pointer_cast<StmtNode>(s2);

    if (stmt1 != nullptr && stmt2 != nullptr) {
      pkb->addNextRelationship(stmt1->stmtNo, stmt2->stmtNo);
    }
  }
}
};  // namespace SP
