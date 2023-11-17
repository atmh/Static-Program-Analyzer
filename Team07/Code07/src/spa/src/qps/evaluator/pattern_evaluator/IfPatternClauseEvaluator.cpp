#include "IfPatternClauseEvaluator.h"

namespace QPS {

bool IfPatternClauseEvaluator::hasPattern(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb) {
  return !pkb->getIfPatterns().empty();
}

std::vector<std::vector<int>> IfPatternClauseEvaluator::getPatterns(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage) {
  auto res = pkb->getIfPatterns();
  std::vector<std::vector<int>> ret;

  for (auto& [s, v] : res) {
    int sId = dataStorage->encodeString(s);
    for (auto stmt : v) {
      ret.push_back({dataStorage->encodeInt(stmt), sId});
    }
  }

  return ret;
}

std::vector<int> IfPatternClauseEvaluator::getPatternStatementByValue(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const Argument& arg) {
  auto res = dataStorage->encodeInts(pkb->getIfFirstArgPatterns(arg));
  return {res.begin(), res.end()};
}

}  // namespace QPS
