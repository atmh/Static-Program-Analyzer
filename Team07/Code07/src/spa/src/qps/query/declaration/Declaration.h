#pragma once

#include <iterator>
#include <string>

#include "pkb/PKBStorageReadInterface.h"
#include "qps/table/NormalizedDataStorage.h"

namespace QPS {

class DeclarationVisitor;

class Declaration {
 public:
  enum class Type {
    NAME,
    INTEGER,
  };

  explicit Declaration(const std::string& name, Type type);

  const std::string& name() const noexcept;

  Type type() const noexcept;

  virtual void accept(DeclarationVisitor& visitor) const = 0;

  virtual ~Declaration() = 0;

  friend bool operator==(const Declaration& lhs, const Declaration& rhs);

 private:
  std::string declarationName;
  Type type_;
};

}  // namespace QPS
