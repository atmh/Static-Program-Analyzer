#include <memory>

#include "AssignDeclaration.h"
#include "CallDeclaration.h"
#include "ConstantDeclaration.h"
#include "DeclarationCreator.h"
#include "IfDeclaration.h"
#include "PrintDeclaration.h"
#include "ProcedureDeclaration.h"
#include "ReadDeclaration.h"
#include "StatementDeclaration.h"
#include "VariableDeclaration.h"
#include "WhileDeclaration.h"

namespace QPS {

const std::string procName = "procName";
const std::string varName = "varName";
const std::string constValue = "value";
const std::string stmtNo = "stmt#";

template class DeclarationCreator<AssignDeclaration>;
template <>
const std::optional<std::string>
    DeclarationCreator<AssignDeclaration>::nameAttr{};
template <>
const std::optional<std::string>
    DeclarationCreator<AssignDeclaration>::integerAttr{stmtNo};

template class DeclarationCreator<CallDeclaration>;
template <>
const std::optional<std::string> DeclarationCreator<CallDeclaration>::nameAttr{
    procName};
template <>
const std::optional<std::string>
    DeclarationCreator<CallDeclaration>::integerAttr{stmtNo};

template class DeclarationCreator<ConstantDeclaration>;
template <>
const std::optional<std::string>
    DeclarationCreator<ConstantDeclaration>::nameAttr{};
template <>
const std::optional<std::string>
    DeclarationCreator<ConstantDeclaration>::integerAttr{constValue};

template class DeclarationCreator<IfDeclaration>;
template <>
const std::optional<std::string> DeclarationCreator<IfDeclaration>::nameAttr{};
template <>
const std::optional<std::string> DeclarationCreator<IfDeclaration>::integerAttr{
    stmtNo};

template class DeclarationCreator<PrintDeclaration>;
template <>
const std::optional<std::string> DeclarationCreator<PrintDeclaration>::nameAttr{
    varName};
template <>
const std::optional<std::string>
    DeclarationCreator<PrintDeclaration>::integerAttr{stmtNo};

template class DeclarationCreator<ProcedureDeclaration>;
template <>
const std::optional<std::string>
    DeclarationCreator<ProcedureDeclaration>::nameAttr{procName};
template <>
const std::optional<std::string>
    DeclarationCreator<ProcedureDeclaration>::integerAttr{};

template class DeclarationCreator<ReadDeclaration>;
template <>
const std::optional<std::string> DeclarationCreator<ReadDeclaration>::nameAttr{
    varName};
template <>
const std::optional<std::string>
    DeclarationCreator<ReadDeclaration>::integerAttr{stmtNo};

template class DeclarationCreator<StatementDeclaration>;
template <>
const std::optional<std::string>
    DeclarationCreator<StatementDeclaration>::nameAttr{};
template <>
const std::optional<std::string>
    DeclarationCreator<StatementDeclaration>::integerAttr{stmtNo};

template class DeclarationCreator<VariableDeclaration>;
template <>
const std::optional<std::string>
    DeclarationCreator<VariableDeclaration>::nameAttr{varName};
template <>
const std::optional<std::string>
    DeclarationCreator<VariableDeclaration>::integerAttr{};

template class DeclarationCreator<WhileDeclaration>;
template <>
const std::optional<std::string>
    DeclarationCreator<WhileDeclaration>::nameAttr{};
template <>
const std::optional<std::string>
    DeclarationCreator<WhileDeclaration>::integerAttr{stmtNo};

template <typename DeclarationType>
std::shared_ptr<Declaration>
DeclarationCreator<DeclarationType>::createDeclaration(
    const std::string& name) const {
  return std::make_shared<DeclarationType>(name);
}

template <typename DeclarationType>
std::shared_ptr<Declaration>
DeclarationCreator<DeclarationType>::createDeclaration(
    const std::string& name, const std::string& attr) const {
  if (nameAttr && attr == *nameAttr)
    return std::make_shared<DeclarationType>(name, Declaration::Type::NAME);
  else if (integerAttr && attr == *integerAttr)
    return std::make_shared<DeclarationType>(name, Declaration::Type::INTEGER);
  return nullptr;
}

}  // namespace QPS
