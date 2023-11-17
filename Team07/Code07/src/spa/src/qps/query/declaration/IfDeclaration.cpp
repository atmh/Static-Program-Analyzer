#include "IfDeclaration.h"

#include "qps/query/declaration/visitor/DeclarationVisitor.h"

namespace QPS {

IfDeclaration::IfDeclaration(const std::string& name,
                             QPS::Declaration::Type type)
    : Declaration(name, type) {}

void IfDeclaration::accept(DeclarationVisitor& visitor) const {
  visitor.visit(*this);
}

}  // namespace QPS
