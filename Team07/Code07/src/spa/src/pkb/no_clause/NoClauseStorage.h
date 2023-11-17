//
// Created by Ramapriyan Srivatsan PD on 4/9/23.
//
#pragma once
#include <string>

#include "pkb/no_clause/NoClauseReadInterface.h"
#include "pkb/no_clause/NoClauseWriteInterface.h"

namespace PKB {
template <typename T>
class NoClauseStorage : NoClauseReadInterface<T>, NoClauseWriteInterface<T> {
 private:
  std::unordered_set<T> entities;

 public:
  void storeEntity(T entity) override;
  bool contains(T entity) override;
  bool empty() override;
  const std::unordered_set<T>& getAllEntities() const override;
};
}  // namespace PKB
