#pragma once
#include "sp/extractor_adapter/ExtractorAdapter.h"
#include "sp/node/StmtNode.h"

namespace SP {
class UseAdapter : public ExtractorAdapter {
 public:
  UseAdapter(const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb);

  void adapt(
      std::unordered_map<std::shared_ptr<StmtNode>,
                         std::unordered_set<std::string>>
          usesS,
      std::unordered_map<std::string, std::unordered_set<std::string>> usesP);
};
}  // namespace SP
