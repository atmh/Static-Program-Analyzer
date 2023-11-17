#include "WhileDeclaration.h"

#include "qps/query/declaration/visitor/DeclarationVisitor.h"

namespace QPS {

WhileDeclaration::WhileDeclaration(const std::string& name,
                                   QPS::Declaration::Type type)
    : Declaration(name, type) {}

void WhileDeclaration::accept(DeclarationVisitor& visitor) const {
  visitor.visit(*this);
}

}  // namespace QPS
