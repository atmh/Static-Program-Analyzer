#pragma once

#include <list>
#include <memory>
#include <string>

#include "pkb/PKBStorage.h"
#include "pkb/PKBStorageAPI.h"
#include "sp/SPManager.h"

namespace SPA {

class SPA {
 public:
  SPA() : pkbStorageAPI(std::make_shared<PKB::PKBStorageAPI>()) {}
  void process(const std::string& filename);
  void evaluate(std::string query, std::list<std::string>& results);

 private:
  std::shared_ptr<PKB::PKBStorageAPI> pkbStorageAPI;
};

}  // namespace SPA
