#pragma once
#include "sp/extractor_adapter/ExtractorAdapter.h"
#include "sp/node/StmtNode.h"

namespace SP {
class NextAdapter : public ExtractorAdapter {
 public:
  NextAdapter(const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb);

  void adapt(
      std::vector<std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>>>
          nextRelationships);
};
}  // namespace SP
