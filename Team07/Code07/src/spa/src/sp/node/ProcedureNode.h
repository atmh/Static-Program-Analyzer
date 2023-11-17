#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Node.h"
#include "StmtLstNode.h"

namespace SP {
class ProcedureNode : public Node,
                      public std::enable_shared_from_this<ProcedureNode> {
 public:
  const std::string name;

  ProcedureNode(std::string name,
                std::vector<std::shared_ptr<Node>> stmtLstNode);
  void accept(DesignExtractor& extractor) override;
};
}  // namespace SP
