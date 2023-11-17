#pragma once

#include "qps/query/declaration/Declaration.h"

namespace QPS {

class ConstantDeclaration : public Declaration {
 public:
  explicit ConstantDeclaration(const std::string& name,
                               Type type = Type::INTEGER);

  virtual void accept(DeclarationVisitor& visitor) const override;

  virtual ~ConstantDeclaration() = default;
};

}  // namespace QPS
