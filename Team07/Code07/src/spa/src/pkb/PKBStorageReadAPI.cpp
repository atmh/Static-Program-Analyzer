//
// Created by Ramapriyan Srivatsan PD on 19/9/23.
//
#include "PKBStorageReadAPI.h"

namespace PKB {

PKBStorageReadAPI::PKBStorageReadAPI(
    const std::shared_ptr<PKBStorage> pkbStoragePtr)
    : pkbStorage(pkbStoragePtr) {}

bool PKBStorageReadAPI::getModifiesProcedureRelationshipExists(
    const std::string& argOne, const std::string& argTwo) {
  return pkbStorage
      ->getRelationshipExists<PKBStorageType::Type::MODIFIES_PROCEDURE>(argOne,
                                                                        argTwo);
}

std::unordered_set<std::string>
PKBStorageReadAPI::getModifiesProcedureFirstArgRelationships(
    const std::string& argOne) {
  return pkbStorage
      ->getFirstArgRelationships<PKBStorageType::Type::MODIFIES_PROCEDURE>(
          argOne);
}

std::unordered_set<std::string>
PKBStorageReadAPI::getModifiesProcedureSecondArgRelationships(
    const std::string& argTwo) {
  return pkbStorage
      ->getSecondArgRelationships<PKBStorageType::Type::MODIFIES_PROCEDURE>(
          argTwo);
}

bool PKBStorageReadAPI::hasModifiesProcedureRelationship() {
  return pkbStorage
      ->hasRelationship<PKBStorageType::Type::MODIFIES_PROCEDURE>();
}

bool PKBStorageReadAPI::getModifiesStatementRelationshipExists(
    const int& argOne, const std::string& argTwo) {
  return pkbStorage
      ->getRelationshipExists<PKBStorageType::Type::MODIFIES_STATEMENT>(argOne,
                                                                        argTwo);
}

std::unordered_set<std::string>
PKBStorageReadAPI::getModifiesStatementFirstArgRelationships(
    const int& argOne) {
  return pkbStorage
      ->getFirstArgRelationships<PKBStorageType::Type::MODIFIES_STATEMENT>(
          argOne);
}

std::unordered_set<int>
PKBStorageReadAPI::getModifiesStatementSecondArgRelationships(
    const std::string& argTwo) {
  return pkbStorage
      ->getSecondArgRelationships<PKBStorageType::Type::MODIFIES_STATEMENT>(
          argTwo);
}

bool PKBStorageReadAPI::hasModifiesStatementRelationship() {
  return pkbStorage
      ->hasRelationship<PKBStorageType::Type::MODIFIES_STATEMENT>();
}

bool PKBStorageReadAPI::getParentRelationshipExists(int argOne, int argTwo) {
  return pkbStorage->getRelationshipExists<PKBStorageType::Type::PARENT>(
      argOne, argTwo);
}

std::unordered_set<int> PKBStorageReadAPI::getParentFirstArgRelationships(
    int argOne) {
  return pkbStorage->getFirstArgRelationships<PKBStorageType::Type::PARENT>(
      argOne);
}

std::unordered_set<int> PKBStorageReadAPI::getParentSecondArgRelationships(
    int argTwo) {
  return pkbStorage->getSecondArgRelationships<PKBStorageType::Type::PARENT>(
      argTwo);
}

bool PKBStorageReadAPI::hasParentRelationship() {
  return pkbStorage->hasRelationship<PKBStorageType::Type::PARENT>();
}

bool PKBStorageReadAPI::getParentStarRelationshipExists(int argOne,
                                                        int argTwo) {
  return pkbStorage->getStarRelationshipExists<PKBStorageType::Type::PARENT>(
      argOne, argTwo);
}

std::unordered_set<int> PKBStorageReadAPI::getParentStarFirstArgRelationships(
    int argOne) {
  return pkbStorage->getFirstArgStarRelationships<PKBStorageType::Type::PARENT>(
      argOne);
}

std::unordered_set<int> PKBStorageReadAPI::getParentStarSecondArgRelationships(
    int argTwo) {
  return pkbStorage
      ->getSecondArgStarRelationships<PKBStorageType::Type::PARENT>(argTwo);
}

bool PKBStorageReadAPI::hasParentStarRelationship() {
  return pkbStorage->hasStarRelationship<PKBStorageType::Type::PARENT>();
}

bool PKBStorageReadAPI::getUsesStatementRelationshipExists(
    int argOne, const std::string& argTwo) {
  return pkbStorage
      ->getRelationshipExists<PKBStorageType::Type::USES_STATEMENT>(argOne,
                                                                    argTwo);
}

bool PKBStorageReadAPI::getUsesProcedureRelationshipExists(
    const std::string& argOne, const std::string& argTwo) {
  return pkbStorage
      ->getRelationshipExists<PKBStorageType::Type::USES_PROCEDURE>(argOne,
                                                                    argTwo);
}

std::unordered_set<std::string>
PKBStorageReadAPI::getUsesStatementFirstArgRelationships(int argOne) {
  return pkbStorage
      ->getFirstArgRelationships<PKBStorageType::Type::USES_STATEMENT>(argOne);
}

std::unordered_set<std::string>
PKBStorageReadAPI::getUsesProcedureFirstArgRelationships(
    const std::string& argOne) {
  return pkbStorage
      ->getFirstArgRelationships<PKBStorageType::Type::USES_PROCEDURE>(argOne);
}

std::unordered_set<int>
PKBStorageReadAPI::getUsesStatementSecondArgRelationships(
    const std::string& argTwo) {
  return pkbStorage
      ->getSecondArgRelationships<PKBStorageType::Type::USES_STATEMENT>(argTwo);
}

std::unordered_set<std::string>
PKBStorageReadAPI::getUsesProcedureSecondArgRelationships(
    const std::string& argTwo) {
  return pkbStorage
      ->getSecondArgRelationships<PKBStorageType::Type::USES_PROCEDURE>(argTwo);
}

bool PKBStorageReadAPI::hasUsesProcedureRelationship() {
  return pkbStorage->hasRelationship<PKBStorageType::Type::USES_PROCEDURE>();
}

bool PKBStorageReadAPI::hasUsesStatementRelationship() {
  return pkbStorage->hasRelationship<PKBStorageType::Type::USES_STATEMENT>();
}

bool PKBStorageReadAPI::getFollowsRelationshipExists(int argOne, int argTwo) {
  return pkbStorage->getRelationshipExists<PKBStorageType::Type::FOLLOWS>(
      argOne, argTwo);
}

std::unordered_set<int> PKBStorageReadAPI::getFollowsFirstArgRelationships(
    int argOne) {
  return pkbStorage->getFirstArgRelationships<PKBStorageType::Type::FOLLOWS>(
      argOne);
}

std::unordered_set<int> PKBStorageReadAPI::getFollowsSecondArgRelationships(
    int argTwo) {
  return pkbStorage->getSecondArgRelationships<PKBStorageType::Type::FOLLOWS>(
      argTwo);
}

bool PKBStorageReadAPI::hasFollowsRelationship() {
  return pkbStorage->hasRelationship<PKBStorageType::Type::FOLLOWS>();
}

bool PKBStorageReadAPI::getFollowsStarRelationshipExists(int argOne,
                                                         int argTwo) {
  return pkbStorage->getStarRelationshipExists<PKBStorageType::Type::FOLLOWS>(
      argOne, argTwo);
}

std::unordered_set<int> PKBStorageReadAPI::getFollowsStarFirstArgRelationships(
    int argOne) {
  return pkbStorage
      ->getFirstArgStarRelationships<PKBStorageType::Type::FOLLOWS>(argOne);
}

std::unordered_set<int> PKBStorageReadAPI::getFollowsStarSecondArgRelationships(
    int argTwo) {
  return pkbStorage
      ->getSecondArgStarRelationships<PKBStorageType::Type::FOLLOWS>(argTwo);
}

bool PKBStorageReadAPI::hasFollowsStarRelationship() {
  return pkbStorage->hasStarRelationship<PKBStorageType::Type::FOLLOWS>();
}

bool PKBStorageReadAPI::getCallsRelationshipExists(const std::string& argOne,
                                                   const std::string& argTwo) {
  return pkbStorage->getRelationshipExists<PKBStorageType::Type::CALLS>(argOne,
                                                                        argTwo);
}

std::unordered_set<std::string>
PKBStorageReadAPI::getCallsFirstArgRelationships(const std::string& argOne) {
  return pkbStorage->getFirstArgRelationships<PKBStorageType::Type::CALLS>(
      argOne);
}

std::unordered_set<std::string>
PKBStorageReadAPI::getCallsSecondArgRelationships(const std::string& argTwo) {
  return pkbStorage->getSecondArgRelationships<PKBStorageType::Type::CALLS>(
      argTwo);
}

bool PKBStorageReadAPI::hasCallsRelationship() {
  return pkbStorage->hasRelationship<PKBStorageType::Type::CALLS>();
}

bool PKBStorageReadAPI::getCallsStarRelationshipExists(
    const std::string& argOne, const std::string& argTwo) {
  return pkbStorage->getStarRelationshipExists<PKBStorageType::Type::CALLS>(
      argOne, argTwo);
}

std::unordered_set<std::string>
PKBStorageReadAPI::getCallsStarFirstArgRelationships(
    const std::string& argOne) {
  return pkbStorage->getFirstArgStarRelationships<PKBStorageType::Type::CALLS>(
      argOne);
}

std::unordered_set<std::string>
PKBStorageReadAPI::getCallsStarSecondArgRelationships(
    const std::string& argTwo) {
  return pkbStorage->getSecondArgStarRelationships<PKBStorageType::Type::CALLS>(
      argTwo);
}

bool PKBStorageReadAPI::hasCallsStarRelationship() {
  return pkbStorage->hasRelationship<PKBStorageType::Type::CALLS>();
}

bool PKBStorageReadAPI::getNextRelationshipExists(int argOne, int argTwo) {
  return pkbStorage->getRelationshipExists<PKBStorageType::Type::NEXT>(argOne,
                                                                       argTwo);
}

std::unordered_set<int> PKBStorageReadAPI::getNextFirstArgRelationships(
    int argOne) {
  return pkbStorage->getFirstArgRelationships<PKBStorageType::Type::NEXT>(
      argOne);
}

std::unordered_set<int> PKBStorageReadAPI::getNextSecondArgRelationships(
    int argTwo) {
  return pkbStorage->getSecondArgRelationships<PKBStorageType::Type::NEXT>(
      argTwo);
}

bool PKBStorageReadAPI::hasNextRelationship() {
  return pkbStorage->hasRelationship<PKBStorageType::Type::NEXT>();
}

const std::unordered_set<int>& PKBStorageReadAPI::getAssigns() const noexcept {
  return pkbStorage->getAssigns();
}

const std::unordered_set<int>& PKBStorageReadAPI::getCalls() const noexcept {
  return pkbStorage->getCalls();
}

const std::string PKBStorageReadAPI::getCallProcName(
    int stmtNo) const noexcept {
  return pkbStorage->getCallProcName(stmtNo);
}

const std::unordered_set<std::string>& PKBStorageReadAPI::getConstants()
    const noexcept {
  return pkbStorage->getConstants();
}

const std::unordered_set<int>& PKBStorageReadAPI::getIfs() const noexcept {
  return pkbStorage->getIfs();
}

const std::unordered_set<int>& PKBStorageReadAPI::getPrints() const noexcept {
  return pkbStorage->getPrints();
}

const std::string PKBStorageReadAPI::getPrintVarName(
    int stmtNo) const noexcept {
  return pkbStorage->getPrintVarName(stmtNo);
}

const std::unordered_set<std::string>& PKBStorageReadAPI::getProcedures()
    const noexcept {
  return pkbStorage->getProcedures();
}

const std::unordered_set<int>& PKBStorageReadAPI::getReads() const noexcept {
  return pkbStorage->getReads();
}

const std::string PKBStorageReadAPI::getReadVarName(int stmtNo) const noexcept {
  return pkbStorage->getReadVarName(stmtNo);
}

const std::unordered_set<int>& PKBStorageReadAPI::getStmts() const noexcept {
  return pkbStorage->getStmts();
}

const std::unordered_set<std::string>& PKBStorageReadAPI::getVariables()
    const noexcept {
  return pkbStorage->getVariables();
}

const std::unordered_set<int>& PKBStorageReadAPI::getWhiles() const noexcept {
  return pkbStorage->getWhiles();
}

const std::unordered_map<std::string,
                         std::vector<std::pair<std::vector<std::string>, int>>>&
PKBStorageReadAPI::getAssignPatterns() const noexcept {
  return pkbStorage->getAssignPatterns();
}

const std::vector<std::pair<std::vector<std::string>, int>>&
PKBStorageReadAPI::getAssignFirstArgPatterns(
    const std::string& lhsArg) const noexcept {
  return pkbStorage->getAssignFirstArgPatterns(lhsArg);
}

const std::unordered_map<std::string, std::unordered_set<int>>&
PKBStorageReadAPI::getIfPatterns() const noexcept {
  return pkbStorage->getIfPatterns();
}

const std::unordered_set<int>& PKBStorageReadAPI::getIfFirstArgPatterns(
    const std::string& varArg) const noexcept {
  return pkbStorage->getIfFirstArgPatterns(varArg);
}

const std::unordered_map<std::string, std::unordered_set<int>>&
PKBStorageReadAPI::getWhilePatterns() const noexcept {
  return pkbStorage->getWhilePatterns();
}

const std::unordered_set<int>& PKBStorageReadAPI::getWhileFirstArgPatterns(
    const std::string& varArg) const noexcept {
  return pkbStorage->getWhileFirstArgPatterns(varArg);
}

}  // namespace PKB
