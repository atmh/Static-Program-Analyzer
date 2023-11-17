#pragma once
#include <unordered_map>

#include "pkb/PKBStorageWriteInterface.h"

namespace SP {
class ExtractorAdapter {
 public:
  std::shared_ptr<PKB::PKBStorageWriteInterface> pkb;
  ExtractorAdapter(const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb);
};
}  // namespace SP
