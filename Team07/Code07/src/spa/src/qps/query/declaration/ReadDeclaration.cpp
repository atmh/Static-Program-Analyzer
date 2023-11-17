#include "ReadDeclaration.h"

#include "qps/query/declaration/visitor/DeclarationVisitor.h"

namespace QPS {

ReadDeclaration::ReadDeclaration(const std::string& name,
                                 QPS::Declaration::Type type)
    : Declaration(name, type) {}

void ReadDeclaration::accept(DeclarationVisitor& visitor) const {
  visitor.visit(*this);
}

}  // namespace QPS
