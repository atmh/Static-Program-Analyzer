#include "IfNode.h"

#include <utility>

namespace SP {
IfNode::IfNode(int stmtNo, std::unordered_set<std::string> exprVar,
               std::unordered_set<std::string> exprCon,
               std::shared_ptr<StmtLstNode> thenStmtLstNode,
               std::shared_ptr<StmtLstNode> elseStmtLstNode)
    : StmtNode(stmtNo, std::vector<std::shared_ptr<Node>>{thenStmtLstNode,
                                                          elseStmtLstNode}),
      exprVar(std::move(exprVar)),
      exprCon(std::move(exprCon)) {}

void IfNode::accept(DesignExtractor& extractor) {
  extractor.visitIf(this->shared_from_this());
}
}  // namespace SP
