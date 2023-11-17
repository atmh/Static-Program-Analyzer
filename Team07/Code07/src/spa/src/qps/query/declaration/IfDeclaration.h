#pragma once

#include "qps/query/declaration/Declaration.h"

namespace QPS {

class IfDeclaration : public Declaration {
 public:
  explicit IfDeclaration(const std::string& name, Type type = Type::INTEGER);

  virtual void accept(DeclarationVisitor& visitor) const override;

  virtual ~IfDeclaration() = default;
};

}  // namespace QPS
