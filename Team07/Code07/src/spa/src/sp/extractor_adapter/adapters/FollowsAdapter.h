#pragma once
#include <memory>

#include "sp/extractor_adapter/ExtractorAdapter.h"
#include "sp/node/StmtNode.h"

namespace SP {
class FollowsAdapter : public ExtractorAdapter {
 public:
  FollowsAdapter(const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb);
  void adapt(
      std::unordered_map<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>>
          followsRelationships);
};
}  // namespace SP
