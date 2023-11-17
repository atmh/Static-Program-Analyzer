#include "PKBStorageAPI.h"

namespace PKB {

PKBStorageAPI::PKBStorageAPI() : pkbStorage(std::make_shared<PKBStorage>()) {}

std::shared_ptr<PKBStorageWriteInterface> PKBStorageAPI::getWriteStorage() {
  return std::make_shared<PKBStorageWriteAPI>(pkbStorage);
}

std::shared_ptr<PKBStorageReadInterface> PKBStorageAPI::getReadStorage() {
  return std::make_shared<PKBStorageReadAPI>(pkbStorage);
}
}  // namespace PKB
