#include "SPManager.h"

namespace SP {

SPManager::SPManager(const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
    : pkb(pkb) {}

void SPManager::process(const std::string& filename) {
  std::ifstream input(filename);

  if (!input) {
    throw SPManagerException(SP_MANAGER_INVALID_FILE);
  }

  std::vector<Common::Token> tokens = SourceTokenizer(&input).tokenize();

  SourceParser sourceParser = SourceParser(tokens);
  sourceParser.parse();
  std::shared_ptr<ProgramNode> root = sourceParser.getRoot();

  ExtractorFactory factory{pkb};
  ExtractorManager(factory).extract(root);

  input.close();
}

}  // namespace SP
