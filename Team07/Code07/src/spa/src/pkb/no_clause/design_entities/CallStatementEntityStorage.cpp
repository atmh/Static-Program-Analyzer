#include "CallStatementEntityStorage.h"

#include "pkb/exception/EntityNotFoundException.h"
#include "pkb/exception/Messages.h"

namespace PKB {

CallStatementEntityStorage::CallStatementEntityStorage()
    : NoClauseStorage<PKB::CallEntity>() {}

std::unordered_set<int>& CallStatementEntityStorage::getStmtNos() {
  return stmtNos;
}

const std::string& CallStatementEntityStorage::getProcName(int stmtNo) {
  for (auto& elem : getAllEntities()) {
    if (elem.getStmtNo() == stmtNo) {
      return elem.getProcName();
    }
  }
  throw EntityNotFoundException(ENTITY_NOT_FOUND);
}

void CallStatementEntityStorage::storeEntity(CallEntity callEntity) {
  NoClauseStorage<CallEntity>::storeEntity(callEntity);
  stmtNos.insert(callEntity.getStmtNo());
}
}  // namespace PKB
