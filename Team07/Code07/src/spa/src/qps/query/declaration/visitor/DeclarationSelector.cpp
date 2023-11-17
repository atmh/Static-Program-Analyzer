#include "DeclarationSelector.h"

namespace QPS {

DeclarationSelector::DeclarationSelector(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage)
    : pkb(pkb), dataStorage(dataStorage), result() {}

void DeclarationSelector::visit(const AssignDeclaration& assign) {
  result = dataStorage->encodeInts(pkb->getAssigns());
};

void DeclarationSelector::visit(const CallDeclaration& call) {
  result = dataStorage->encodeInts(pkb->getCalls());
};

void DeclarationSelector::visit(const ConstantDeclaration& constant) {
  result = dataStorage->encodeStrings(pkb->getConstants());
};

void DeclarationSelector::visit(const IfDeclaration& ifDeclaration) {
  result = dataStorage->encodeInts(pkb->getIfs());
};

void DeclarationSelector::visit(const PrintDeclaration& print) {
  result = dataStorage->encodeInts(pkb->getPrints());
};

void DeclarationSelector::visit(const ProcedureDeclaration& procedure) {
  result = dataStorage->encodeStrings(pkb->getProcedures());
};

void DeclarationSelector::visit(const ReadDeclaration& read) {
  result = dataStorage->encodeInts(pkb->getReads());
};

void DeclarationSelector::visit(const StatementDeclaration& stmt) {
  result = dataStorage->encodeInts(pkb->getStmts());
}

void DeclarationSelector::visit(const VariableDeclaration& variable) {
  result = dataStorage->encodeStrings(pkb->getVariables());
}

void DeclarationSelector::visit(const WhileDeclaration& whileDeclaration) {
  result = dataStorage->encodeInts(pkb->getWhiles());
};

const std::unordered_set<int>& DeclarationSelector::getResult() const noexcept {
  return result;
}

}  // namespace QPS
