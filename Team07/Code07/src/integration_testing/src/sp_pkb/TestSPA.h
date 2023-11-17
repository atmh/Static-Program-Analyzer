//
// Created by Volunteer The on 22/9/23.
//
#pragma once

#include <list>
#include <memory>
#include <string>

#include "pkb/PKBStorage.h"
#include "pkb/PKBStorageAPI.h"
#include "sp/SPManager.h"

class TestSPA {
 public:
  TestSPA() : pkbStorageAPI(std::make_shared<PKB::PKBStorageAPI>()) {}
  void process(const std::string& filename);
  std::shared_ptr<PKB::PKBStorageAPI> pkbStorageAPI;
};
