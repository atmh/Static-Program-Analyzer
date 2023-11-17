#include "sp/node/StmtNode.h"

namespace SP {
StmtNode::StmtNode(int stmtNo, std::vector<std::shared_ptr<Node>> children)
    : Node(children), stmtNo(stmtNo) {}

StmtNode::~StmtNode() = default;
}  // namespace SP
