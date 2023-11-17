#include "StmtLstNode.h"

#include <utility>

namespace SP {
StmtLstNode::StmtLstNode(std::vector<std::shared_ptr<Node>> stmtNodes)
    : Node(std::move(stmtNodes)) {}

void StmtLstNode::accept(DesignExtractor& extractor) {
  extractor.visitStmtList(this->shared_from_this());
}
}  // namespace SP
