#include "sp/design_extractor/extractors/FollowsExtractor.h"

#include "sp/node/StmtLstNode.h"
#include "sp/node/StmtNode.h"

namespace SP {
FollowsExtractor::FollowsExtractor(const FollowsAdapter& adapter)
    : adapter{adapter} {}

std::unordered_map<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>>
FollowsExtractor::getStorage() {
  return storage;
}

void FollowsExtractor::sendDataToAdapter() {
  adapter.adapt(getStorage());
}

void FollowsExtractor::visitStmtList(const std::shared_ptr<StmtLstNode>& node) {
  if (isSubtreeComputed(node))
    return;

  std::vector<std::shared_ptr<Node>> children = node->getChildren();
  if (children.empty()) {
    return;
  }

  for (int i = 1; i < children.size(); i++) {
    std::shared_ptr<StmtNode> stmtNode1 =
        std::dynamic_pointer_cast<StmtNode>(children[i - 1]);
    std::shared_ptr<StmtNode> stmtNode2 =
        std::dynamic_pointer_cast<StmtNode>(children[i]);

    if (stmtNode1 == nullptr || stmtNode2 == nullptr) {
      continue;
    }
    storage.insert(std::make_pair(stmtNode1, stmtNode2));
  }

  visitedStack.push(node);
}
}  // namespace SP
