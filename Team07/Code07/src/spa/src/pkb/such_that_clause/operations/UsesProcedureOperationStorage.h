//
// Created by Volunteer The on 14/9/23.
//
#pragma once
#include "pkb/such_that_clause/SuchThatStorage.h"

namespace PKB {
class UsesProcedureOperationStorage
    : public SuchThatStorage<std::string, std::string> {};
}  // namespace PKB
