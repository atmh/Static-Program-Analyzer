#pragma once

#include <memory>
#include <string>
#include <vector>

#include "sp/node/StmtNode.h"

namespace SP {
class PrintNode : public StmtNode,
                  public std::enable_shared_from_this<PrintNode> {
 public:
  const std::string name;

  PrintNode(int stmtNo, std::string name);
  void accept(DesignExtractor& extractor) override;
};
}  // namespace SP
