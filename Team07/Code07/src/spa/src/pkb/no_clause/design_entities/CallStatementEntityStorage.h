//
// Created by Ramapriyan Srivatsan PD on 4/9/23.
//
#pragma once
#include "pkb/no_clause/design_entities/StatementEntityStorage.h"
#include "pkb/utils/entity_structs/CallEntity.h"
#include "unordered_set"

namespace PKB {
class CallStatementEntityStorage : public NoClauseStorage<PKB::CallEntity> {
  std::unordered_set<int> stmtNos;

 public:
  CallStatementEntityStorage();
  std::unordered_set<int>& getStmtNos();
  const std::string& getProcName(int stmtNo);
  void storeEntity(CallEntity callEntity);
};
}  // namespace PKB
