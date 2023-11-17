#include "WhilePatternClauseEvaluator.h"

namespace QPS {

bool WhilePatternClauseEvaluator::hasPattern(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb) {
  return !pkb->getWhilePatterns().empty();
}

std::vector<std::vector<int>> WhilePatternClauseEvaluator::getPatterns(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage) {
  auto res = pkb->getWhilePatterns();
  std::vector<std::vector<int>> ret;

  for (auto& [s, v] : res) {
    int sId = dataStorage->encodeString(s);
    for (auto stmt : v) {
      ret.push_back({dataStorage->encodeInt(stmt), sId});
    }
  }

  return ret;
}

std::vector<int> WhilePatternClauseEvaluator::getPatternStatementByValue(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  auto res = dataStorage->encodeInts(pkb->getWhileFirstArgPatterns(arg));
  return {res.begin(), res.end()};
}

}  // namespace QPS
