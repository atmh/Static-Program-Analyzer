#include "VariableDeclaration.h"

#include "qps/query/declaration/visitor/DeclarationVisitor.h"

namespace QPS {

VariableDeclaration::VariableDeclaration(const std::string& name,
                                         QPS::Declaration::Type type)
    : Declaration(name, type) {}

void VariableDeclaration::accept(DeclarationVisitor& visitor) const {
  visitor.visit(*this);
}

}  // namespace QPS
