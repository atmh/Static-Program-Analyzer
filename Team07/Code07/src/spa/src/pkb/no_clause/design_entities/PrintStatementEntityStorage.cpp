#include "pkb/no_clause/design_entities/PrintStatementEntityStorage.h"

#include "pkb/exception/EntityNotFoundException.h"
#include "pkb/exception/Messages.h"

namespace PKB {

PrintStatementEntityStorage::PrintStatementEntityStorage()
    : NoClauseStorage<PKB::PrintEntity>() {}

const std::unordered_set<int>& PrintStatementEntityStorage::getStmtNos() {
  return stmtNos;
}

const std::string& PrintStatementEntityStorage::getVarName(int stmtNo) {
  for (auto& elem : getAllEntities()) {
    if (elem.getStmtNo() == stmtNo) {
      return elem.getVarName();
    }
  }
  throw EntityNotFoundException(ENTITY_NOT_FOUND);
}

void PrintStatementEntityStorage::storeEntity(PrintEntity printEntity) {
  NoClauseStorage<PrintEntity>::storeEntity(printEntity);
  stmtNos.insert(printEntity.getStmtNo());
}
}  // namespace PKB
