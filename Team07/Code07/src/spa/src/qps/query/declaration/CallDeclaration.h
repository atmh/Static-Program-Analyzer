#pragma once

#include "qps/query/declaration/Declaration.h"

namespace QPS {

class CallDeclaration : public Declaration {
 public:
  explicit CallDeclaration(const std::string& name, Type type = Type::INTEGER);

  virtual void accept(DeclarationVisitor& visitor) const override;

  virtual ~CallDeclaration() = default;
};

}  // namespace QPS
