#include "sp/node/stmt_nodes/CallNode.h"

#include <utility>

namespace SP {
CallNode::CallNode(int stmtNo, std::string name)
    : StmtNode(stmtNo, std::vector<std ::shared_ptr<Node>>{}),
      name(std::move(name)) {}

void CallNode::accept(DesignExtractor& extractor) {
  extractor.visitCall(this->shared_from_this());
}
}  // namespace SP
