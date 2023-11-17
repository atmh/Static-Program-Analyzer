//
// Created by Ramapriyan Srivatsan PD on 19/9/23.
//
#include "PKBStorage.h"

namespace PKB {

PKBStorage::PKBStorage() {
  // add constructor to initialize various storages
  followsStorage = std::make_shared<FollowsOperationStorage>();
  modifiesProcedureStorage =
      std::make_shared<ModifiesProcedureOperationStorage>();
  modifiesStatementStorage =
      std::make_shared<ModifiesStatementOperationStorage>();
  parentStorage = std::make_shared<ParentOperationStorage>();
  usesProcedureStorage = std::make_shared<UsesProcedureOperationStorage>();
  usesStatementStorage = std::make_shared<UsesStatementOperationStorage>();
  callsStorage = std::make_shared<CallsOperationStorage>();
  nextStorage = std::make_shared<NextOperationStorage>();

  assignStorage = std::make_shared<AssignEntityStorage>();
  callStatementStorage = std::make_shared<CallStatementEntityStorage>();
  constantStorage = std::make_shared<ConstantEntityStorage>();
  ifStorage = std::make_shared<IfEntityStorage>();
  printStatementStorage = std::make_shared<PrintStatementEntityStorage>();
  procedureStorage = std::make_shared<ProcedureEntityStorage>();
  readStatementStorage = std::make_shared<ReadStatementEntityStorage>();
  statementStorage = std::make_shared<StatementEntityStorage>();
  variableStorage = std::make_shared<VariableEntityStorage>();
  whileStorage = std::make_shared<WhileEntityStorage>();

  assignPatternStorage = std::make_shared<AssignPatternStorage>();
  ifPatternStorage = std::make_shared<IfPatternStorage>();
  whilePatternStorage = std::make_shared<WhilePatternStorage>();
}

const std::unordered_set<int>& PKBStorage::getAssigns() const noexcept {
  return assignStorage->getAllEntities();
}

const std::unordered_set<int>& PKBStorage::getCalls() const noexcept {
  return callStatementStorage->getStmtNos();
}

const std::string PKBStorage::getCallProcName(int stmtNo) const noexcept {
  return callStatementStorage->getProcName(stmtNo);
}

const std::unordered_set<std::string>& PKBStorage::getConstants()
    const noexcept {
  return constantStorage->getAllEntities();
}

const std::unordered_set<int>& PKBStorage::getIfs() const noexcept {
  return ifStorage->getAllEntities();
}

const std::unordered_set<int>& PKBStorage::getPrints() const noexcept {
  return printStatementStorage->getStmtNos();
}

const std::string PKBStorage::getPrintVarName(int stmtNo) const noexcept {
  return printStatementStorage->getVarName(stmtNo);
}

const std::unordered_set<std::string>& PKBStorage::getProcedures()
    const noexcept {
  return procedureStorage->getAllEntities();
}

const std::unordered_set<int>& PKBStorage::getReads() const noexcept {
  return readStatementStorage->getStmtNos();
}

const std::string PKBStorage::getReadVarName(int stmtNo) const noexcept {
  return readStatementStorage->getVarName(stmtNo);
}

const std::unordered_set<int>& PKBStorage::getStmts() const noexcept {
  return statementStorage->getAllEntities();
}

const std::unordered_set<std::string>& PKBStorage::getVariables()
    const noexcept {
  return variableStorage->getAllEntities();
};

const std::unordered_set<int>& PKBStorage::getWhiles() const noexcept {
  return whileStorage->getAllEntities();
}

const std::unordered_map<std::string,
                         std::vector<std::pair<std::vector<std::string>, int>>>&
PKBStorage::getAssignPatterns() const noexcept {
  return assignPatternStorage->getAllPatterns();
}

const std::vector<std::pair<std::vector<std::string>, int>>&
PKBStorage::getAssignFirstArgPatterns(
    const std::string& lhsArg) const noexcept {
  return assignPatternStorage->getVector(lhsArg);
}

const std::unordered_map<std::string, std::unordered_set<int>>&
PKBStorage::getIfPatterns() const noexcept {
  return ifPatternStorage->getAllPatterns();
}

const std::unordered_set<int>& PKBStorage::getIfFirstArgPatterns(
    const std::string& varArg) const noexcept {
  return ifPatternStorage->getSet(varArg);
}

const std::unordered_map<std::string, std::unordered_set<int>>&
PKBStorage::getWhilePatterns() const noexcept {
  return whilePatternStorage->getAllPatterns();
}

const std::unordered_set<int>& PKBStorage::getWhileFirstArgPatterns(
    const std::string& varArg) const noexcept {
  return whilePatternStorage->getSet(varArg);
}

void PKBStorage::addStatementEntity(int entity) {
  statementStorage->storeEntity(entity);
}

void PKBStorage::addAssignEntity(int stmtNo) {
  assignStorage->storeEntity(stmtNo);
  addStatementEntity(stmtNo);
}

void PKBStorage::addAssignPattern(int stmtNo, const std::string& lhsArg,
                                  const std::vector<std::string>& rhsArg) {
  assignPatternStorage->storeAssignPattern(stmtNo, lhsArg, rhsArg);
}

void PKBStorage::addIfPattern(int stmtNo, const std::string& varArg) {
  ifPatternStorage->storeIfWhilePattern(stmtNo, varArg);
}

void PKBStorage::addWhilePattern(int stmtNo, const std::string& varArg) {
  whilePatternStorage->storeIfWhilePattern(stmtNo, varArg);
}

void PKBStorage::addCallEntity(int stmtNo, const std::string& procName) {
  callStatementStorage->storeEntity(CallEntity(stmtNo, procName));
  addStatementEntity(stmtNo);
}

void PKBStorage::addConstantEntity(const std::string& entity) {
  constantStorage->storeEntity(entity);
}

void PKBStorage::addIfEntity(int stmtNo) {
  ifStorage->storeEntity(stmtNo);
  addStatementEntity(stmtNo);
}

void PKBStorage::addPrintEntity(int stmtNo, const std::string& varName) {
  printStatementStorage->storeEntity(PrintEntity(stmtNo, varName));
  addStatementEntity(stmtNo);
}

void PKBStorage::addProcedureEntity(const std::string& procName) {
  procedureStorage->storeEntity(procName);
}

void PKBStorage::addReadEntity(int stmtNo, const std::string& varName) {
  readStatementStorage->storeEntity(ReadEntity(stmtNo, varName));
  addStatementEntity(stmtNo);
}

void PKBStorage::addVariableEntity(const std::string& varName) {
  variableStorage->storeEntity(varName);
}

void PKBStorage::addWhileEntity(int stmtNo) {
  whileStorage->storeEntity(stmtNo);
  addStatementEntity(stmtNo);
}
}  // namespace PKB
