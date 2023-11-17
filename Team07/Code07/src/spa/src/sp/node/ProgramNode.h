#pragma once

#include <memory>
#include <vector>

#include "ProcedureNode.h"
#include "sp/node/Node.h"

namespace SP {
class ProgramNode : public Node,
                    public std::enable_shared_from_this<ProgramNode> {
 public:
  ProgramNode(std::vector<std::shared_ptr<Node>> procedureNodes);
  void accept(DesignExtractor& extractor) override;
};
}  // namespace SP
