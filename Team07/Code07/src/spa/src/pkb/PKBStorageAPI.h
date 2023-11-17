//
// Created by Ramapriyan Srivatsan PD on 1/9/23.
//
#pragma once

#include <memory>
#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

#include "PKBStorage.h"
#include "PKBStorageReadAPI.h"
#include "PKBStorageReadInterface.h"
#include "PKBStorageWriteAPI.h"
#include "PKBStorageWriteInterface.h"

namespace PKB {

class PKBStorageAPI {
 private:
  std::shared_ptr<PKBStorage> pkbStorage;

 public:
  explicit PKBStorageAPI();
  std::shared_ptr<PKBStorageWriteInterface> getWriteStorage();
  std::shared_ptr<PKBStorageReadInterface> getReadStorage();
  virtual ~PKBStorageAPI() = default;
};
}  // namespace PKB