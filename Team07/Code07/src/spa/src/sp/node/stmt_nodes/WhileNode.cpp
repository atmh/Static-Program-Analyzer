#include "sp/node/stmt_nodes/WhileNode.h"

#include <utility>

namespace SP {
WhileNode::WhileNode(int stmtNo, std::unordered_set<std::string> exprVar,
                     std::unordered_set<std::string> exprCon,
                     std::shared_ptr<StmtLstNode> stmtLstNode)
    : StmtNode(stmtNo, std::vector<std::shared_ptr<Node>>{stmtLstNode}),
      exprVar(std::move(exprVar)),
      exprCon(std::move(exprCon)) {}

void WhileNode::accept(DesignExtractor& extractor) {
  extractor.visitWhile(this->shared_from_this());
}

}  // namespace SP
