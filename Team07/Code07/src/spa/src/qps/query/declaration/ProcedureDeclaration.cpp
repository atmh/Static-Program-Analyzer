#include "ProcedureDeclaration.h"

#include "qps/query/declaration/visitor/DeclarationVisitor.h"

namespace QPS {

ProcedureDeclaration::ProcedureDeclaration(const std::string& name,
                                           QPS::Declaration::Type type)
    : Declaration(name, type) {}

void ProcedureDeclaration::accept(DeclarationVisitor& visitor) const {
  visitor.visit(*this);
}

}  // namespace QPS
