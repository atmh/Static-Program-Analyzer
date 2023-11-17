#include "ConstantDeclaration.h"

#include "qps/query/declaration/visitor/DeclarationVisitor.h"

namespace QPS {

ConstantDeclaration::ConstantDeclaration(const std::string& name,
                                         QPS::Declaration::Type type)
    : Declaration(name, type) {}

void ConstantDeclaration::accept(DeclarationVisitor& visitor) const {
  visitor.visit(*this);
}

}  // namespace QPS
