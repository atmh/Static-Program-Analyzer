#include "StatementDeclaration.h"

#include "qps/query/declaration/visitor/DeclarationVisitor.h"

namespace QPS {

StatementDeclaration::StatementDeclaration(const std::string& name,
                                           QPS::Declaration::Type type)
    : Declaration(name, type) {}

void StatementDeclaration::accept(DeclarationVisitor& visitor) const {
  visitor.visit(*this);
}

}  // namespace QPS
