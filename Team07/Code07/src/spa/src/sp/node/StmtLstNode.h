#pragma once

#include <memory>
#include <vector>

#include "sp/node/Node.h"

namespace SP {
class StmtLstNode : public Node,
                    public std::enable_shared_from_this<StmtLstNode> {
 public:
  StmtLstNode(std::vector<std::shared_ptr<Node>> stmtNodes);
  void accept(DesignExtractor& extractor) override;
};
}  // namespace SP
