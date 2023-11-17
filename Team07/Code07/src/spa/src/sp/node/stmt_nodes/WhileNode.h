#pragma once

#include <memory>
#include <string>
#include <unordered_set>

#include "sp/node/StmtLstNode.h"
#include "sp/node/StmtNode.h"

namespace SP {
class WhileNode : public StmtNode,
                  public std::enable_shared_from_this<WhileNode> {
 public:
  const std::unordered_set<std::string> exprVar;
  const std::unordered_set<std::string> exprCon;

  WhileNode(int stmtNo, std::unordered_set<std::string> exprVar,
            std::unordered_set<std::string> exprCon,
            std::shared_ptr<StmtLstNode> stmtLstNode);

  void accept(DesignExtractor& extractor) override;
};
}  // namespace SP
