#include "sp/extractor_adapter/adapters/FollowsAdapter.h"

namespace SP {
FollowsAdapter::FollowsAdapter(
    const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
    : ExtractorAdapter(pkb) {}

void FollowsAdapter::adapt(
    std::unordered_map<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>>
        followsRelationships) {
  for (auto it = followsRelationships.begin(); it != followsRelationships.end();
       ++it) {
    auto nodePtr1 = it->first;
    auto nodePtr2 = it->second;
    if (nodePtr1 && nodePtr2) {
      pkb->addFollowsRelationship(nodePtr1->stmtNo, nodePtr2->stmtNo);
    }
  }
}
}  // namespace SP
