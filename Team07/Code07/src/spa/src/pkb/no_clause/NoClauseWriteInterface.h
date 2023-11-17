//
// Created by Ramapriyan Srivatsan PD on 29/8/23.
//
#pragma once

namespace PKB {
template <typename T>
class NoClauseWriteInterface {
  virtual void storeEntity(T entity) = 0;
};
}  // namespace PKB
