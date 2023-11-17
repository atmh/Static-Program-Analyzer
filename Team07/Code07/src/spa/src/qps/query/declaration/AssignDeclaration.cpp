#include "AssignDeclaration.h"

#include "qps/query/declaration/visitor/DeclarationVisitor.h"

namespace QPS {

AssignDeclaration::AssignDeclaration(const std::string& name,
                                     QPS::Declaration::Type type)
    : Declaration(name, type) {}

void AssignDeclaration::accept(DeclarationVisitor& visitor) const {
  visitor.visit(*this);
}

}  // namespace QPS
