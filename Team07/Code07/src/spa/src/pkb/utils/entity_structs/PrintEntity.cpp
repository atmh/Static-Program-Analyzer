#include "pkb/utils/entity_structs/PrintEntity.h"

#include <iostream>

namespace PKB {

PrintEntity::PrintEntity(int stmtNo, const std::string& varName)
    : StmtEntity(stmtNo), varName(varName) {}

const std::string& PrintEntity::getVarName() const {
  return varName;
}
bool operator==(const PrintEntity& lhs, const PrintEntity& rhs) noexcept {
  return (lhs.stmtNo == rhs.stmtNo) && (lhs.varName == rhs.varName);
}

std::ostream& operator<<(std::ostream& s, const PrintEntity& printEntity) {
  return s << "(" << printEntity.stmtNo << ", " << printEntity.varName << ")";
}
}  // namespace PKB
