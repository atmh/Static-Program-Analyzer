//
// Created by Ramapriyan Srivatsan PD on 29/8/23.
//
#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace PKB {
template <typename T, typename U>
class SuchThatReadInterface {
 public:
  virtual bool getRelationshipExists(T argOne, U argTwo) = 0;
  virtual std::unordered_set<U> getFirstArgRelationships(T argOne) = 0;
  virtual std::unordered_set<T> getSecondArgRelationships(U argTwo) = 0;
  virtual bool empty() = 0;
};
}  // namespace PKB
