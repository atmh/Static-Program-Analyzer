#pragma once

#include <memory>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "sp/design_extractor/DesignExtractor.h"
#include "sp/extractor_adapter/adapters/FollowsAdapter.h"
#include "sp/node/StmtNode.h"

namespace SP {
class FollowsExtractor : public DesignExtractor {
 private:
  FollowsAdapter adapter;
  std::unordered_map<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>>
      storage;

 public:
  FollowsExtractor(const FollowsAdapter& adapter);

  void visitStmtList(const std::shared_ptr<StmtLstNode>& node) override;
  void sendDataToAdapter() override;
  std::unordered_map<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>>
  getStorage();
};
}  // namespace SP
