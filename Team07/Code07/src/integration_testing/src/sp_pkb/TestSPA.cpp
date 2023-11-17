//
// Created by Volunteer The on 22/9/23.
//
#include "TestSPA.h"

#include <memory>

#include "pkb/PKBStorageReadInterface.h"

void TestSPA::process(const std::string& filename) {
  // pkb pointer needs to be passed to sp manager for dependency injection.
  // require pointer because polymorphic
  SP::SPManager sp{pkbStorageAPI->getWriteStorage()};
  sp.process(filename);
}
