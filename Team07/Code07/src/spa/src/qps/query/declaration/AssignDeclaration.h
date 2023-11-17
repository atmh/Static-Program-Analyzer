#pragma once

#include "qps/query/declaration/Declaration.h"

namespace QPS {

class AssignDeclaration : public Declaration {
 public:
  explicit AssignDeclaration(const std::string& name,
                             Type type = Type::INTEGER);

  virtual void accept(DeclarationVisitor& visitor) const override;

  virtual ~AssignDeclaration() = default;
};

}  // namespace QPS
