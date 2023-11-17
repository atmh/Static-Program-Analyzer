#include "pkb/utils/entity_structs/ReadEntity.h"

#include <iostream>

namespace PKB {

ReadEntity::ReadEntity(int stmtNo, const std::string& varName)
    : StmtEntity(stmtNo), varName(varName) {}

const std::string& ReadEntity::getVarName() const {
  return varName;
}
bool operator==(const ReadEntity& lhs, const ReadEntity& rhs) noexcept {
  return (lhs.stmtNo == rhs.stmtNo) && (lhs.varName == rhs.varName);
}

std::ostream& operator<<(std::ostream& s, const ReadEntity& readEntity) {
  return s << "(" << readEntity.stmtNo << ", " << readEntity.varName << ")";
}
}  // namespace PKB