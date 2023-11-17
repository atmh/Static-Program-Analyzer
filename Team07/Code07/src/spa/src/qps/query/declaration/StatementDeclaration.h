#pragma once

#include "qps/query/declaration/Declaration.h"

namespace QPS {

class StatementDeclaration : public Declaration {
 public:
  explicit StatementDeclaration(const std::string& name,
                                Type type = Type::INTEGER);

  virtual void accept(DeclarationVisitor& visitor) const override;

  virtual ~StatementDeclaration() = default;
};

}  // namespace QPS
