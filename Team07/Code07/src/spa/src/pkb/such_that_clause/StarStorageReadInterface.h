//
// Created by Ramapriyan Srivatsan PD on 6/9/23.
//
#pragma once
#include "unordered_set"

namespace PKB {
template <typename T>
class StarStorageReadInterface {
 public:
  virtual bool getStarRelationshipExists(T argOne, T argTwo) = 0;
  virtual std::unordered_set<T> getFirstArgStarRelationships(T argOne) = 0;
  virtual std::unordered_set<T> getSecondArgStarRelationships(T argTwo) = 0;
  virtual bool starEmpty() = 0;
};
}  // namespace PKB
