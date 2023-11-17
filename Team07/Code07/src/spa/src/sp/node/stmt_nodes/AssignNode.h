#pragma once

#include <string>
#include <unordered_set>

#include "sp/node/StmtNode.h"

namespace SP {

class AssignNode : public StmtNode,
                   public std::enable_shared_from_this<AssignNode> {
 public:
  const std::string name;
  const std::unordered_set<std::string> exprVar;
  const std::unordered_set<std::string> exprCon;
  const std::vector<std::string> postfix;

  explicit AssignNode(int stmtNo, std::string name,
                      std::unordered_set<std::string> exprVar,
                      std::unordered_set<std::string> exprCon,
                      std::vector<std::string> postfix);

  void accept(DesignExtractor& extractor) override;
};
}  // namespace SP
