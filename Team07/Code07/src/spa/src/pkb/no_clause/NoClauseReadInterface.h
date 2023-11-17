//
// Created by Ramapriyan Srivatsan PD on 29/8/23.
//
#pragma once
#include "unordered_set"

namespace PKB {
template <typename T>
class NoClauseReadInterface {
 public:
  virtual bool contains(T entity) = 0;
  virtual bool empty() = 0;
  virtual const std::unordered_set<T>& getAllEntities() const = 0;
};
}  // namespace PKB
