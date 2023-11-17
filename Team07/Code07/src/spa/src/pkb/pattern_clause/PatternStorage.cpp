//
// Created by Ramapriyan Srivatsan PD on 21/9/23.
//
#include "PatternStorage.h"

#include <unordered_set>

namespace PKB {

template <typename T, typename U, typename MapValueType>
void PatternStorage<T, U, MapValueType>::storeAssignPattern(int stmtNo,
                                                            const T& lhsArg,
                                                            const U& rhsArg) {
  auto pairToStore = std::make_pair(rhsArg, stmtNo);
  if constexpr (std::is_same_v<
                    MapValueType,
                    std::vector<std::pair<std::vector<std::string>, int>>>) {
    patternMap[lhsArg].push_back(pairToStore);
  }
}

template <typename T, typename U, typename MapValueType>
void PatternStorage<T, U, MapValueType>::storeIfWhilePattern(int stmtNo,
                                                             const T& varArg) {
  if constexpr (std::is_same_v<MapValueType, std::unordered_set<int>>) {
    patternMap[varArg].insert(stmtNo);
  }
}

template <typename T, typename U, typename MapValueType>
const MapValueType& PatternStorage<T, U, MapValueType>::getVector(
    const T& lhsArg) const {
  static const MapValueType emptyVector;
  auto it = patternMap.find(lhsArg);
  return (it != patternMap.end()) ? it->second : emptyVector;
}

template <typename T, typename U, typename MapValueType>
const MapValueType& PatternStorage<T, U, MapValueType>::getSet(
    const T& varArg) const {
  static const MapValueType emptySet;
  auto it = patternMap.find(varArg);
  return (it != patternMap.end()) ? it->second : emptySet;
}

template <typename T, typename U, typename MapValueType>
const std::unordered_map<T, MapValueType>&
PatternStorage<T, U, MapValueType>::getAllPatterns() const {
  return patternMap;
}

template class PatternStorage<
    std::string, std::vector<std::string>,
    std::vector<std::pair<std::vector<std::string>, int>>>;

template class PatternStorage<std::string, std::string,
                              std::unordered_set<int>>;

}  // namespace PKB
