#include "ReadStatementEntityStorage.h"

#include "pkb/exception/EntityNotFoundException.h"
#include "pkb/exception/Messages.h"

namespace PKB {

ReadStatementEntityStorage::ReadStatementEntityStorage()
    : NoClauseStorage<PKB::ReadEntity>() {}

const std::unordered_set<int>& ReadStatementEntityStorage::getStmtNos() {
  return stmtNos;
}

const std::string& ReadStatementEntityStorage::getVarName(int stmtNo) {
  for (auto& elem : getAllEntities()) {
    if (elem.getStmtNo() == stmtNo) {
      return elem.getVarName();
    }
  }
  throw EntityNotFoundException(ENTITY_NOT_FOUND);
}

void ReadStatementEntityStorage::storeEntity(ReadEntity readEntity) {
  NoClauseStorage<ReadEntity>::storeEntity(readEntity);
  stmtNos.insert(readEntity.getStmtNo());
}
}  // namespace PKB
