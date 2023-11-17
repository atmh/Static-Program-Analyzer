//
// Created by Ramapriyan Srivatsan PD on 1/9/23.
//
#pragma once
#include "pkb/such_that_clause/SuchThatStorage.h"

namespace PKB {
class ModifiesProcedureOperationStorage
    : public SuchThatStorage<std::string, std::string> {};
}  // namespace PKB
