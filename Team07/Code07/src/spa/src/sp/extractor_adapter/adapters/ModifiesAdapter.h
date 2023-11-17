#pragma once
#include "sp/extractor_adapter/ExtractorAdapter.h"
#include "sp/node/StmtNode.h"

namespace SP {
class ModifiesAdapter : public ExtractorAdapter {
 public:
  ModifiesAdapter(const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb);

  void adapt(std::unordered_map<std::shared_ptr<StmtNode>,
                                std::unordered_set<std::string>>
                 modifiesS,
             std::unordered_map<std::string, std::unordered_set<std::string>>
                 modifiesP);
};
}  // namespace SP
