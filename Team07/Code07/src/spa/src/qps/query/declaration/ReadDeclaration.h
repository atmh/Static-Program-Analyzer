#pragma once

#include "qps/query/declaration/Declaration.h"

namespace QPS {

class ReadDeclaration : public Declaration {
 public:
  explicit ReadDeclaration(const std::string& name, Type type = Type::INTEGER);

  virtual void accept(DeclarationVisitor& visitor) const override;

  virtual ~ReadDeclaration() = default;
};

}  // namespace QPS
