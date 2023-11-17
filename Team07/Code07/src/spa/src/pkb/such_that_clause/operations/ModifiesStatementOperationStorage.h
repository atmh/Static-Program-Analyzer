//
// Created by Shi Zheng on 13/9/23.
//
#pragma once
#include "pkb/such_that_clause/SuchThatStorage.h"

namespace PKB {
class ModifiesStatementOperationStorage
    : public SuchThatStorage<int, std::string> {};
}  // namespace PKB
