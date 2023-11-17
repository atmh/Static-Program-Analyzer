#include "ProgramNode.h"

namespace SP {
ProgramNode::ProgramNode(std::vector<std::shared_ptr<Node>> procedureNodes)
    : Node(std::move(procedureNodes)) {}

void ProgramNode::accept(DesignExtractor& extractor) {
  extractor.visitProgram(this->shared_from_this());
}
}  // namespace SP
