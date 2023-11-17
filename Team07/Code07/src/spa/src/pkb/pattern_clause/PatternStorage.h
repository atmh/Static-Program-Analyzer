#pragma once
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "PatternReadInterface.h"
#include "PatternWriteInterface.h"
#include "unordered_set"

namespace PKB {

template <typename T, typename U, typename MapValueType>
class PatternStorage : public PatternReadInterface<T, MapValueType>,
                       public PatternWriteInterface<T, U> {
 private:
  std::unordered_map<T, MapValueType> patternMap;

 public:
  void storeAssignPattern(int stmtNo, const T& lhsArg,
                          const U& rhsArg) override;
  void storeIfWhilePattern(int stmtNo, const T& varArg) override;
  const MapValueType& getVector(const T& lhsArg) const override;
  const MapValueType& getSet(const T& varArg) const override;
  const std::unordered_map<T, MapValueType>& getAllPatterns() const;
};

}  // namespace PKB
