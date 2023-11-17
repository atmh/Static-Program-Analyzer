#include "pkb/utils/entity_structs/CallEntity.h"

#include <iostream>
#include <utility>

namespace PKB {

CallEntity::CallEntity(int stmtNo, const std::string& procName)
    : StmtEntity(stmtNo), procName(procName) {}

const std::string& CallEntity::getProcName() const {
  return procName;
}

bool operator==(const CallEntity& lhs, const CallEntity& rhs) noexcept {
  return (lhs.stmtNo == rhs.stmtNo) && (lhs.procName == rhs.procName);
}

std::ostream& operator<<(std::ostream& s, const CallEntity& callEntity) {
  return s << "(" << callEntity.stmtNo << ", " << callEntity.procName << ")";
}
}  // namespace PKB
