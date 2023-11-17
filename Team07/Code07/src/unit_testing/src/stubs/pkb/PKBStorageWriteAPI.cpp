#include "PKBStorageWriteAPI.h"

namespace PKB {
void PKBStorageWriteStub::addModifiesProcedureRelationship(
    const std::string& argOne, const std::string& argTwo) {
  modifiesProcedureStorage[argOne].insert(argTwo);
  return;
}

void PKBStorageWriteStub::addModifiesStatementRelationship(
    const int& argOne, const std::string& argTwo) {
  modifiesStatementStorage[argOne].insert(argTwo);
  return;
}

void PKBStorageWriteStub::addParentRelationship(int argOne, int argTwo) {
  parentStorage[argOne].insert(argTwo);
  return;
}

void PKBStorageWriteStub::addConstantEntity(const std::string& entity) {
  constantStorage.insert(entity);
}

void PKBStorageWriteStub::addUsesStatementRelationship(
    const int& argOne, const std::string& argTwo) {
  usesStatementStorage[argOne].insert(argTwo);
  return;
}

void PKBStorageWriteStub::addUsesProcedureRelationship(
    const std::string& argOne, const std::string& argTwo) {
  usesProcedureStorage[argOne].insert(argTwo);
  return;
}

void PKBStorageWriteStub::addFollowsRelationship(int argOne, int argTwo) {
  followsStorage[argOne] = argTwo;
  return;
}

void PKBStorageWriteStub::addCallsRelationship(const std::string& argOne,
                                               const std::string& argTwo) {
  callsStorage[argOne].insert(argTwo);
  return;
}

void PKBStorageWriteStub::addNextRelationship(int argOne, int argTwo) {
  nextStorage[argOne].insert(argTwo);
  return;
}

void PKBStorageWriteStub::addAssignEntity(int stmtNo) {
  assignStorage.insert(stmtNo);
}

void PKBStorageWriteStub::addCallEntity(int stmtNo,
                                        const std::string& procName) {
  callStorage.insert(stmtNo);
}

void PKBStorageWriteStub::addIfEntity(int stmtNo) {
  ifStorage.insert(stmtNo);
}

void PKBStorageWriteStub::addPrintEntity(int stmtNo,
                                         const std::string& varName) {
  printStorage.insert(stmtNo);
}

void PKBStorageWriteStub::addProcedureEntity(const std::string& procName) {
  procedureStorage.insert(procName);
}

void PKBStorageWriteStub::addReadEntity(int stmtNo,
                                        const std::string& varName) {
  readStorage.insert(stmtNo);
}

void PKBStorageWriteStub::addVariableEntity(const std::string& varName) {
  variableStorage.insert(varName);
}

void PKBStorageWriteStub::addWhileEntity(int stmtNo) {
  whileStorage.insert(stmtNo);
}

void PKBStorageWriteStub::addAssignPattern(
    int stmt, const std::string& argOne,
    const std::vector<std::string>& argTwo) {
  assignPatternStorage[argOne].emplace_back(std::make_pair(argTwo, stmt));
}
void PKBStorageWriteStub::addIfPattern(int stmt, const std::string& varArg) {
  ifPatternStorage[varArg].insert(stmt);
}
void PKBStorageWriteStub::addWhilePattern(int stmt, const std::string& varArg) {
  whilePatternStorage[varArg].insert(stmt);
}

}  // namespace PKB
