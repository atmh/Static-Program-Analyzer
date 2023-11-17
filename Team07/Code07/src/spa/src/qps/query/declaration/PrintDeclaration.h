#pragma once

#include "qps/query/declaration/Declaration.h"

namespace QPS {

class PrintDeclaration : public Declaration {
 public:
  explicit PrintDeclaration(const std::string& name, Type type = Type::INTEGER);

  virtual void accept(DeclarationVisitor& visitor) const override;

  virtual ~PrintDeclaration() = default;
};

}  // namespace QPS
