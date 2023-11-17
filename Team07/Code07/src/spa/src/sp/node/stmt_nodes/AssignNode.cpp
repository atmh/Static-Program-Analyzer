#include "sp/node/stmt_nodes/AssignNode.h"

#include <utility>

namespace SP {
AssignNode::AssignNode(int stmtNo, std::string name,
                       std::unordered_set<std::string> exprVar,
                       std::unordered_set<std::string> exprCon,
                       std::vector<std::string> postfix)
    : StmtNode(stmtNo, std::vector<std ::shared_ptr<Node>>{}),
      name(std::move(name)),
      exprVar(std::move(exprVar)),
      exprCon(std::move(exprCon)),
      postfix(std::move(postfix)) {}

void AssignNode::accept(DesignExtractor& extractor) {
  extractor.visitAssign(this->shared_from_this());
}
}  // namespace SP
