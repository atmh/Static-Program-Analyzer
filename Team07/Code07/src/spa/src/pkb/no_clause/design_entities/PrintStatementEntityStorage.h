//
// Created by Ramapriyan Srivatsan PD on 4/9/23.
//
#pragma once
#include "pkb/no_clause/design_entities/StatementEntityStorage.h"
#include "pkb/utils/entity_structs/PrintEntity.h"

namespace PKB {
class PrintStatementEntityStorage : public NoClauseStorage<PKB::PrintEntity> {
  std::unordered_set<int> stmtNos;

 public:
  PrintStatementEntityStorage();
  const std::unordered_set<int>& getStmtNos();
  const std::string& getVarName(int stmtNo);
  void storeEntity(PrintEntity printEntity);
};
}  // namespace PKB
