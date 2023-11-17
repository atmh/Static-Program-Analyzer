#pragma once

#include "Node.h"

namespace SP {
class StmtNode : public Node {
 public:
  const int stmtNo;

  StmtNode(int stmtNo, std::vector<std::shared_ptr<Node>> children);

  virtual ~StmtNode() = 0;
};
}  // namespace SP
