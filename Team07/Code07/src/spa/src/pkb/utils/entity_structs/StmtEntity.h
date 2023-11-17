#pragma once

#include <string>

namespace PKB {
class StmtEntity {
 public:
  const int stmtNo;
  StmtEntity(int stmtNo);
  int getStmtNo() const;

  bool operator==(const StmtEntity& other) const {
    return (stmtNo == other.stmtNo);
  }

  struct HashFunction {
    static size_t getValue(const StmtEntity& stmtEntity) {
      size_t stmtNoHash = std::hash<int>()(stmtEntity.stmtNo);
      return stmtNoHash;
    }
  };
};
}  // namespace PKB

namespace std {
template <>
struct hash<PKB::StmtEntity> {
  size_t operator()(PKB::StmtEntity stmtEntity) const {
    return std::hash<size_t>()(
        PKB::StmtEntity::HashFunction::getValue(stmtEntity));
  }
};
}  // namespace std