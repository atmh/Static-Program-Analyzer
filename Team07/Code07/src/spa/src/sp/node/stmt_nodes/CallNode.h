#pragma once

#include <memory>
#include <string>
#include <vector>

#include "sp/node/StmtNode.h"

namespace SP {
class CallNode : public StmtNode,
                 public std::enable_shared_from_this<CallNode> {
 public:
  const std::string name;

  CallNode(int stmtNo, std::string name);

  void accept(DesignExtractor& extractor) override;
};
}  // namespace SP
