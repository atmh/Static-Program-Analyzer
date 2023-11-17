#pragma once

#include "qps/query/declaration/Declaration.h"

namespace QPS {

class WhileDeclaration : public Declaration {
 public:
  explicit WhileDeclaration(const std::string& name, Type type = Type::INTEGER);

  virtual void accept(DeclarationVisitor& visitor) const override;

  virtual ~WhileDeclaration() = default;
};

}  // namespace QPS
