//
// Created by Ramapriyan Srivatsan PD on 29/8/23.
//
#pragma once

namespace PKB {
template <typename T, typename U>
class SuchThatWriteInterface {
 public:
  virtual void storeInformation(T argOne, U argTwo) = 0;
};
}  // namespace PKB
