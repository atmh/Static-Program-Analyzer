#pragma once
#include "sp/extractor_adapter/ExtractorAdapter.h"
#include "sp/node/StmtNode.h"

namespace SP {
class ParentAdapter : public ExtractorAdapter {
 public:
  ParentAdapter(const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb);

  void adapt(std::vector<
             std::pair<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>>>
                 parentRelationships);
};
}  // namespace SP
