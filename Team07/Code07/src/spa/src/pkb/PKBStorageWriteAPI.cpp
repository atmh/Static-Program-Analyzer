//
// Created by Ramapriyan Srivatsan PD on 21/9/23.
//
#include "PKBStorageWriteAPI.h"

namespace PKB {

PKBStorageWriteAPI::PKBStorageWriteAPI(
    const std::shared_ptr<PKBStorage>& pkbStoragePtr)
    : pkbStorage(pkbStoragePtr) {}

void PKBStorageWriteAPI::addModifiesProcedureRelationship(
    const std::string& argOne, const std::string& argTwo) {
  pkbStorage->addRelationship<PKBStorageType::Type::MODIFIES_PROCEDURE>(argOne,
                                                                        argTwo);
}

void PKBStorageWriteAPI::addModifiesStatementRelationship(
    const int& argOne, const std::string& argTwo) {
  pkbStorage->addRelationship<PKBStorageType::Type::MODIFIES_STATEMENT>(argOne,
                                                                        argTwo);
}

void PKBStorageWriteAPI::addParentRelationship(int argOne, int argTwo) {
  pkbStorage->addRelationship<PKBStorageType::Type::PARENT>(argOne, argTwo);
}

void PKBStorageWriteAPI::addUsesProcedureRelationship(
    const std::string& argOne, const std::string& argTwo) {
  pkbStorage->addRelationship<PKBStorageType::Type::USES_PROCEDURE>(argOne,
                                                                    argTwo);
}

void PKBStorageWriteAPI::addUsesStatementRelationship(
    const int& argOne, const std::string& argTwo) {
  pkbStorage->addRelationship<PKBStorageType::Type::USES_STATEMENT>(argOne,
                                                                    argTwo);
}

void PKBStorageWriteAPI::addFollowsRelationship(int argOne, int argTwo) {
  pkbStorage->addRelationship<PKBStorageType::Type::FOLLOWS>(argOne, argTwo);
}

void PKBStorageWriteAPI::addCallsRelationship(const std::string& argOne,
                                              const std::string& argTwo) {
  pkbStorage->addRelationship<PKBStorageType::Type::CALLS>(argOne, argTwo);
}

void PKBStorageWriteAPI::addNextRelationship(int argOne, int argTwo) {
  pkbStorage->addRelationship<PKBStorageType::Type::NEXT>(argOne, argTwo);
}

void PKBStorageWriteAPI::addAssignEntity(int entity) {
  pkbStorage->addAssignEntity(entity);
}

void PKBStorageWriteAPI::addAssignPattern(
    int stmtNo, const std::string& lhsArg,
    const std::vector<std::string>& rhsArg) {
  pkbStorage->addAssignPattern(stmtNo, lhsArg, rhsArg);
}

void PKBStorageWriteAPI::addIfPattern(int stmtNo, const std::string& varArg) {
  pkbStorage->addIfPattern(stmtNo, varArg);
}

void PKBStorageWriteAPI::addWhilePattern(int stmtNo,
                                         const std::string& varArg) {
  pkbStorage->addWhilePattern(stmtNo, varArg);
}

void PKBStorageWriteAPI::addCallEntity(int entity,
                                       const std::string& procName) {
  pkbStorage->addCallEntity(entity, procName);
}

void PKBStorageWriteAPI::addConstantEntity(const std::string& entity) {
  pkbStorage->addConstantEntity(entity);
}

void PKBStorageWriteAPI::addIfEntity(int entity) {
  pkbStorage->addIfEntity(entity);
}

void PKBStorageWriteAPI::addPrintEntity(int entity,
                                        const std::string& varName) {
  pkbStorage->addPrintEntity(entity, varName);
}

void PKBStorageWriteAPI::addProcedureEntity(const std::string& entity) {
  pkbStorage->addProcedureEntity(entity);
}

void PKBStorageWriteAPI::addReadEntity(int entity, const std::string& varName) {
  pkbStorage->addReadEntity(entity, varName);
}

void PKBStorageWriteAPI::addVariableEntity(const std::string& entity) {
  pkbStorage->addVariableEntity(entity);
}

void PKBStorageWriteAPI::addWhileEntity(int entity) {
  pkbStorage->addWhileEntity(entity);
}
}  // namespace PKB