#include "sp/node/stmt_nodes/ReadNode.h"

#include <utility>

namespace SP {
ReadNode::ReadNode(int stmtNo, std::string name)
    : StmtNode(stmtNo, std::vector<std ::shared_ptr<Node>>{}),
      name(std::move(name)) {}

void ReadNode::accept(DesignExtractor& extractor) {
  extractor.visitRead(this->shared_from_this());
}
}  // namespace SP
