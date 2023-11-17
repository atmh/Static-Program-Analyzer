#pragma once

#include <memory>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "sp/design_extractor/DesignExtractor.h"
#include "sp/extractor_adapter/adapters/NextAdapter.h"
#include "sp/node/Node.h"
#include "sp/node/StmtNode.h"

namespace SP {
class NextExtractor : public DesignExtractor {
 private:
  using NextPairs =
      std::vector<std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>>>;

  std::unordered_map<std::shared_ptr<IfNode>, std::shared_ptr<Node>> postIfLink;

  NextAdapter adapter;
  NextPairs storage;

 public:
  NextExtractor(const NextAdapter& adapter);

  void visitStmtList(const std::shared_ptr<StmtLstNode>& node) override;
  void visitWhile(const std::shared_ptr<WhileNode>& node) override;
  void visitIf(const std::shared_ptr<IfNode>& node) override;

  void sendDataToAdapter() override;
  NextPairs getStorage();
};
}  // namespace SP
