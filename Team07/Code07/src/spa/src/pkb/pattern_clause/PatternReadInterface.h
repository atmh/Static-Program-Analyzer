//
// Created by Ramapriyan Srivatsan PD on 29/8/23.
//
#pragma once
#include <string>
#include <vector>

namespace PKB {

template <typename T, typename MapValueType>
class PatternReadInterface {
 public:
  virtual const MapValueType& getVector(const T& lhsArg) const = 0;
  virtual const MapValueType& getSet(const T& varArg) const = 0;
};
}  // namespace PKB
