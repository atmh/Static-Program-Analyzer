#pragma once

#include <memory>
#include <string>
#include <vector>

#include "pkb/utils/entity_structs/StmtEntity.h"

namespace PKB {
class PrintEntity : public StmtEntity {
 public:
  const std::string varName;

  PrintEntity(int stmtNo, const std::string& varName);
  const std::string& getVarName() const;

  friend bool operator==(const PrintEntity& lhs,
                         const PrintEntity& rhs) noexcept;
  friend std::ostream& operator<<(std::ostream& s,
                                  const PrintEntity& printEntity);

  struct HashFunction {
    static size_t getValue(const PrintEntity& printEntity) {
      size_t stmtNoHash = std::hash<int>()(printEntity.stmtNo);
      size_t varNameHash = std::hash<std::string>()(printEntity.varName);
      return stmtNoHash ^ varNameHash;
    }
  };
};
}  // namespace PKB

namespace std {
template <>
struct hash<PKB::PrintEntity> {
  size_t operator()(PKB::PrintEntity printEntity) const {
    return std::hash<size_t>()(
        PKB::PrintEntity::HashFunction::getValue(printEntity));
  }
};
}  // namespace std
