#pragma once

#include <memory>
#include <string>
#include <unordered_set>

#include "sp/node/StmtLstNode.h"
#include "sp/node/StmtNode.h"

namespace SP {
class IfNode : public StmtNode, public std::enable_shared_from_this<IfNode> {
 public:
  const std::unordered_set<std::string> exprVar;
  const std::unordered_set<std::string> exprCon;

  IfNode(int stmtNo, std::unordered_set<std::string> exprVar,
         std::unordered_set<std::string> exprCon,
         std::shared_ptr<StmtLstNode> thenStmtLstNode,
         std::shared_ptr<StmtLstNode> elseStmtLstNode);

  void accept(DesignExtractor& extractor) override;
};
}  // namespace SP
