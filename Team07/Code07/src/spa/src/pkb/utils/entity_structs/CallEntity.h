#pragma once

#include <memory>
#include <string>
#include <vector>

#include "pkb/utils/entity_structs/StmtEntity.h"

namespace PKB {
class CallEntity : public StmtEntity {
 public:
  const std::string procName;

  CallEntity(int stmtNo, const std::string& procName);
  const std::string& getProcName() const;

  friend bool operator==(const CallEntity& lhs, const CallEntity& rhs) noexcept;
  friend std::ostream& operator<<(std::ostream& s,
                                  const CallEntity& callEntity);

  struct HashFunction {
    static size_t getValue(const CallEntity& callEntity) {
      size_t stmtNoHash = std::hash<int>()(callEntity.stmtNo);
      size_t procName = std::hash<std::string>()(callEntity.procName);
      return stmtNoHash ^ procName;
    }
  };
};
}  // namespace PKB

namespace std {
template <>
struct hash<PKB::CallEntity> {
  size_t operator()(PKB::CallEntity callEntity) const {
    return std::hash<size_t>()(
        PKB::CallEntity::HashFunction::getValue(callEntity));
  }
};
}  // namespace std
