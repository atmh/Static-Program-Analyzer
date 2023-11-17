#include "pkb/utils/entity_structs/StmtEntity.h"

namespace PKB {
StmtEntity::StmtEntity(int stmtNo) : stmtNo(stmtNo) {}

int StmtEntity::getStmtNo() const {
  return stmtNo;
}
}  // namespace PKB
