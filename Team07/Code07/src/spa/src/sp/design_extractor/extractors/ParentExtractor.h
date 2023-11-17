#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "sp/design_extractor/DesignExtractor.h"
#include "sp/extractor_adapter/adapters/ParentAdapter.h"
#include "sp/node//stmt_nodes/WhileNode.h"
#include "sp/node/Node.h"
#include "sp/node/stmt_nodes/IfNode.h"

namespace SP {
class ParentExtractor : public DesignExtractor {
 private:
  ParentAdapter adapter;
  std::vector<std::pair<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>>>
      storage;

 public:
  ParentExtractor(const ParentAdapter& adapter);

  void visitIf(const std::shared_ptr<IfNode>& node) override;
  void visitWhile(const std::shared_ptr<WhileNode>& node) override;
  void sendDataToAdapter() override;

  std::vector<std::pair<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>>>
  getStorage();
};
}  // namespace SP
