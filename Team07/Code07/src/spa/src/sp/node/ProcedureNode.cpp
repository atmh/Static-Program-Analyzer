#include "ProcedureNode.h"

#include <utility>

namespace SP {
ProcedureNode::ProcedureNode(std::string name,
                             std::vector<std::shared_ptr<Node>> stmtLstNode)
    : name(std::move(name)), Node(std::move(stmtLstNode)) {}

void ProcedureNode::accept(DesignExtractor& extractor) {
  extractor.visitProcedure(this->shared_from_this());
}

}  // namespace SP
