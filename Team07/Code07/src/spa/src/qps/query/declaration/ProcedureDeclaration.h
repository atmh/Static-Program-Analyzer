#pragma once

#include "qps/query/declaration/Declaration.h"

namespace QPS {

class ProcedureDeclaration : public Declaration {
 public:
  explicit ProcedureDeclaration(const std::string& name,
                                Type type = Type::NAME);

  virtual void accept(DeclarationVisitor& visitor) const override;

  virtual ~ProcedureDeclaration() = default;
};

}  // namespace QPS
