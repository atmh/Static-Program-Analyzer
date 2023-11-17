#pragma once

#include <memory>
#include <string>
#include <vector>

#include "sp/node/StmtNode.h"

namespace SP {
class ReadNode : public StmtNode,
                 public std::enable_shared_from_this<ReadNode> {
 public:
  const std::string name;

  void accept(DesignExtractor& extractor) override;
  ReadNode(int stmtNo, std::string name);
};
}  // namespace SP
