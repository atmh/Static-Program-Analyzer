#include "ArgumentConstructor.h"

#include <string>

namespace QPS {

ArgumentConstructor::ArgumentConstructor(
    int id, const std::shared_ptr<NormalizedDataStorage>& dataStorage)
    : id(id), dataStorage(dataStorage), arg() {}

void ArgumentConstructor::visit(const AssignDeclaration& assign) {
  arg = std::stoi(dataStorage->decodeInt(id));
}

void ArgumentConstructor::visit(const CallDeclaration& call) {
  arg = std::stoi(dataStorage->decodeInt(id));
}

void ArgumentConstructor::visit(const ConstantDeclaration& constant) {
  arg = dataStorage->decodeString(id);
}

void ArgumentConstructor::visit(const IfDeclaration& ifDeclaration) {
  arg = std::stoi(dataStorage->decodeInt(id));
}

void ArgumentConstructor::visit(const PrintDeclaration& print) {
  arg = std::stoi(dataStorage->decodeInt(id));
}

void ArgumentConstructor::visit(const ProcedureDeclaration& procedure) {
  arg = dataStorage->decodeString(id);
}

void ArgumentConstructor::visit(const ReadDeclaration& read) {
  arg = std::stoi(dataStorage->decodeInt(id));
}

void ArgumentConstructor::visit(const StatementDeclaration& stmt) {
  arg = std::stoi(dataStorage->decodeInt(id));
}

void ArgumentConstructor::visit(const VariableDeclaration& variable) {
  arg = dataStorage->decodeString(id);
}

void ArgumentConstructor::visit(const WhileDeclaration& whileDeclaration) {
  arg = std::stoi(dataStorage->decodeInt(id));
}

ArgumentConstructor::operator Argument() {
  return arg;
}

}  // namespace QPS
