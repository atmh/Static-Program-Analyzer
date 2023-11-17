#include "DeclarationStringSerializer.h"

#include <cassert>

namespace QPS {

DeclarationStringSerializer::DeclarationStringSerializer(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    int declarationId)
    : pkb(pkb),
      dataStorage(dataStorage),
      result(),
      declarationId(declarationId) {}

void DeclarationStringSerializer::visit(const AssignDeclaration& assign) {
  decodeInt();
}
void DeclarationStringSerializer::visit(const CallDeclaration& call) {
  switch (call.type()) {
    case Declaration::Type::INTEGER:
      return decodeInt();
    case Declaration::Type::NAME: {
      result = pkb->getCallProcName(
          std::stoi(dataStorage->decodeInt(declarationId)));
      return;
    }
    default:
      assert(false && "call declaration is either integer or name type");
  }
}
void DeclarationStringSerializer::visit(const ConstantDeclaration& constant) {
  decodeString();
}
void DeclarationStringSerializer::visit(const IfDeclaration& ifDeclaration) {
  decodeInt();
}
void DeclarationStringSerializer::visit(const PrintDeclaration& print) {
  switch (print.type()) {
    case Declaration::Type::INTEGER:
      return decodeInt();
    case Declaration::Type::NAME: {
      result = pkb->getPrintVarName(
          std::stoi(dataStorage->decodeInt(declarationId)));
      return;
    }
    default:
      assert(false && "print declaration is either integer or name type");
  }
}
void DeclarationStringSerializer::visit(const ProcedureDeclaration& procedure) {
  decodeString();
}
void DeclarationStringSerializer::visit(const ReadDeclaration& read) {
  switch (read.type()) {
    case Declaration::Type::INTEGER:
      return decodeInt();
    case Declaration::Type::NAME: {
      result =
          pkb->getReadVarName(std::stoi(dataStorage->decodeInt(declarationId)));
      return;
    }
    default:
      assert(false && "read declaration is either integer or name type");
  }
}
void DeclarationStringSerializer::visit(const StatementDeclaration& stmt) {
  decodeInt();
}
void DeclarationStringSerializer::visit(const VariableDeclaration& variable) {
  decodeString();
}
void DeclarationStringSerializer::visit(
    const WhileDeclaration& whileDeclaration) {
  decodeInt();
}

const std::string& DeclarationStringSerializer::getResult() const noexcept {
  return result;
}

void DeclarationStringSerializer::decodeInt() {
  result = dataStorage->decodeInt(declarationId);
}

void DeclarationStringSerializer::decodeString() {
  result = dataStorage->decodeString(declarationId);
}

}  // namespace QPS
