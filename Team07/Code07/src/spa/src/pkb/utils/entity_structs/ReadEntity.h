#pragma once

#include <memory>
#include <string>
#include <vector>

#include "pkb/utils/entity_structs/StmtEntity.h"

namespace PKB {
class ReadEntity : public StmtEntity {
 public:
  std::string varName;

  ReadEntity(int stmtNo, const std::string& varName);
  const std::string& getVarName() const;

  friend bool operator==(const ReadEntity& lhs, const ReadEntity& rhs) noexcept;
  friend std::ostream& operator<<(std::ostream& s,
                                  const ReadEntity& readEntity);

  struct HashFunction {
    static size_t getValue(const ReadEntity& readEntity) {
      size_t stmtNoHash = std::hash<int>()(readEntity.stmtNo);
      size_t varNameHash = std::hash<std::string>()(readEntity.varName);
      return stmtNoHash ^ varNameHash;
    }
  };
};
}  // namespace PKB

namespace std {
template <>
struct hash<PKB::ReadEntity> {
  size_t operator()(PKB::ReadEntity readEntity) const {
    return std::hash<size_t>()(
        PKB::ReadEntity::HashFunction::getValue(readEntity));
  }
};
}  // namespace std