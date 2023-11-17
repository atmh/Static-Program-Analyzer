//
// Created by Ramapriyan Srivatsan PD on 29/8/23.
//
#pragma once
#include "string"
#include "vector"

namespace PKB {

template <typename T, typename U>
class PatternWriteInterface {
 public:
  virtual void storeAssignPattern(int stmtNo, const T& lhsArg,
                                  const U& rhsArg) = 0;
  virtual void storeIfWhilePattern(int stmtNo, const T& varArg) = 0;
};

}  // namespace PKB
