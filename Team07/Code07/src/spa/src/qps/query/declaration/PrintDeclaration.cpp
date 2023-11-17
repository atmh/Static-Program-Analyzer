#include "PrintDeclaration.h"

#include "qps/query/declaration/visitor/DeclarationVisitor.h"

namespace QPS {

PrintDeclaration::PrintDeclaration(const std::string& name,
                                   QPS::Declaration::Type type)
    : Declaration(name, type) {}

void PrintDeclaration::accept(DeclarationVisitor& visitor) const {
  visitor.visit(*this);
}

}  // namespace QPS
