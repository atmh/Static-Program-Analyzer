#pragma once

#include <fstream>
#include <memory>
#include <string>

#include "pkb/PKBStorageWriteInterface.h"
#include "sp/design_extractor/ExtractorManager.h"
#include "sp/exception/Messages.h"
#include "sp/exception/SPManagerException.h"
#include "sp/parser/SourceParser.h"
#include "sp/tokenizer/SourceTokenizer.h"

namespace SP {

class SPManager {
 public:
  SPManager(const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb);
  void process(const std::string& filename);

 private:
  std::shared_ptr<PKB::PKBStorageWriteInterface> pkb;
};

}  // namespace SP
