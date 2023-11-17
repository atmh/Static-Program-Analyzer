#pragma once

#include "qps/query/declaration/Declaration.h"

namespace QPS {

class VariableDeclaration : public Declaration {
 public:
  explicit VariableDeclaration(const std::string& name, Type type = Type::NAME);

  virtual void accept(DeclarationVisitor& visitor) const override;

  virtual ~VariableDeclaration() = default;
};

}  // namespace QPS
