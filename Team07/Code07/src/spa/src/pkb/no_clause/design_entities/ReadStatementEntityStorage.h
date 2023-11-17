//
// Created by Ramapriyan Srivatsan PD on 4/9/23.
//
#pragma once
#include "pkb/no_clause/design_entities/StatementEntityStorage.h"
#include "pkb/utils/entity_structs/ReadEntity.h"

namespace PKB {
class ReadStatementEntityStorage : public NoClauseStorage<PKB::ReadEntity> {
  std::unordered_set<int> stmtNos;

 public:
  ReadStatementEntityStorage();
  const std::unordered_set<int>& getStmtNos();
  const std::string& getVarName(int stmtNo);
  void storeEntity(ReadEntity readEntity);
};
}  // namespace PKB
