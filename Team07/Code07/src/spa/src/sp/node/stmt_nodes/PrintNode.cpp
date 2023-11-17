#include "PrintNode.h"

#include <utility>

#include "memory"

namespace SP {
PrintNode::PrintNode(int stmtNo, std::string name)
    : StmtNode(stmtNo, std::vector<std ::shared_ptr<Node>>{}),
      name(std::move(name)) {}

void PrintNode::accept(DesignExtractor& extractor) {
  extractor.visitPrint(this->shared_from_this());
}

}  // namespace SP
