//
// Created by Ramapriyan Srivatsan PD on 1/9/23.
//
#pragma once
#include <cassert>
#include "PKBStorageReadInterface.h"
#include "PKBStorageType.h"
#include "PKBStorageWriteInterface.h"
#include "no_clause/design_entities/AssignEntityStorage.h"
#include "no_clause/design_entities/CallStatementEntityStorage.h"
#include "no_clause/design_entities/ConstantEntityStorage.h"
#include "no_clause/design_entities/IfEntityStorage.h"
#include "no_clause/design_entities/PrintStatementEntityStorage.h"
#include "no_clause/design_entities/ProcedureEntityStorage.h"
#include "no_clause/design_entities/ReadStatementEntityStorage.h"
#include "no_clause/design_entities/StatementEntityStorage.h"
#include "no_clause/design_entities/VariableEntityStorage.h"
#include "no_clause/design_entities/WhileEntityStorage.h"
#include "pattern_clause/patterns/AssignPatternStorage.h"
#include "pattern_clause/patterns/IfPatternStorage.h"
#include "pattern_clause/patterns/WhilePatternStorage.h"
#include "pkb/such_that_clause/operations/CallsOperationStorage.h"
#include "pkb/such_that_clause/operations/NextOperationStorage.h"
#include "such_that_clause/SuchThatStorage.h"
#include "such_that_clause/operations/FollowsOperationStorage.h"
#include "such_that_clause/operations/ModifiesProcedureOperationStorage.h"
#include "such_that_clause/operations/ModifiesStatementOperationStorage.h"
#include "such_that_clause/operations/ParentOperationStorage.h"
#include "such_that_clause/operations/UsesProcedureOperationStorage.h"
#include "such_that_clause/operations/UsesStatementOperationStorage.h"

namespace PKB {

class PKBStorage {
 protected:
  std::shared_ptr<FollowsOperationStorage> followsStorage;
  std::shared_ptr<ParentOperationStorage> parentStorage;
  std::shared_ptr<UsesProcedureOperationStorage> usesProcedureStorage;
  std::shared_ptr<UsesStatementOperationStorage> usesStatementStorage;
  std::shared_ptr<ModifiesProcedureOperationStorage> modifiesProcedureStorage;
  std::shared_ptr<ModifiesStatementOperationStorage> modifiesStatementStorage;
  std::shared_ptr<CallsOperationStorage> callsStorage;
  std::shared_ptr<NextOperationStorage> nextStorage;

  std::shared_ptr<AssignEntityStorage> assignStorage;
  std::shared_ptr<CallStatementEntityStorage> callStatementStorage;
  std::shared_ptr<ConstantEntityStorage> constantStorage;
  std::shared_ptr<IfEntityStorage> ifStorage;
  std::shared_ptr<PrintStatementEntityStorage> printStatementStorage;
  std::shared_ptr<ProcedureEntityStorage> procedureStorage;
  std::shared_ptr<ReadStatementEntityStorage> readStatementStorage;
  std::shared_ptr<StatementEntityStorage> statementStorage;
  std::shared_ptr<VariableEntityStorage> variableStorage;
  std::shared_ptr<WhileEntityStorage> whileStorage;

  std::shared_ptr<AssignPatternStorage> assignPatternStorage;
  std::shared_ptr<IfPatternStorage> ifPatternStorage;
  std::shared_ptr<WhilePatternStorage> whilePatternStorage;

 private:
  void addStatementEntity(int stmtNo);

 public:
  explicit PKBStorage();

  // Read API

  const std::unordered_set<int>& getAssigns() const noexcept;
  const std::unordered_set<int>& getCalls() const noexcept;
  const std::string getCallProcName(int stmtNo) const noexcept;
  const std::unordered_set<std::string>& getConstants() const noexcept;
  const std::unordered_set<int>& getIfs() const noexcept;
  const std::unordered_set<int>& getPrints() const noexcept;
  const std::string getPrintVarName(int stmtNo) const noexcept;
  const std::unordered_set<std::string>& getProcedures() const noexcept;
  const std::unordered_set<int>& getReads() const noexcept;
  const std::string getReadVarName(int stmtNo) const noexcept;
  const std::unordered_set<int>& getStmts() const noexcept;
  const std::unordered_set<std::string>& getVariables() const noexcept;
  const std::unordered_set<int>& getWhiles() const noexcept;

  const std::unordered_map<
      std::string, std::vector<std::pair<std::vector<std::string>, int>>>&
  getAssignPatterns() const noexcept;
  const std::vector<std::pair<std::vector<std::string>, int>>&
  getAssignFirstArgPatterns(const std::string& lhsArg) const noexcept;
  virtual const std::unordered_map<std::string, std::unordered_set<int>>&
  getIfPatterns() const noexcept;
  virtual const std::unordered_set<int>& getIfFirstArgPatterns(
      const std::string& varArg) const noexcept;
  virtual const std::unordered_map<std::string, std::unordered_set<int>>&
  getWhilePatterns() const noexcept;
  virtual const std::unordered_set<int>& getWhileFirstArgPatterns(
      const std::string& varArg) const noexcept;

  void addAssignEntity(int stmtNo);
  void addCallEntity(int stmtNo, const std::string& procName);
  void addConstantEntity(const std::string& entity);
  void addIfEntity(int stmtNo);
  void addPrintEntity(int stmtNo, const std::string& varName);
  void addProcedureEntity(const std::string& procName);
  void addReadEntity(int stmtNo, const std::string& varName);
  void addVariableEntity(const std::string& varName);
  void addWhileEntity(int stmtNo);

  void addAssignPattern(int stmtNo, const std::string& lhsArg,
                        const std::vector<std::string>& rhsArg);
  void addIfPattern(int stmtNo, const std::string& varArg);
  void addWhilePattern(int stmtNo, const std::string& varArg);

  template <PKBStorageType::Type type>
  inline auto getSuchThatStorage() {
    if constexpr (type == PKBStorageType::Type::FOLLOWS) {
      return followsStorage;
    } else if constexpr (type == PKBStorageType::Type::PARENT) {
      return parentStorage;
    } else if constexpr (type == PKBStorageType::Type::NEXT) {
      return nextStorage;
    } else if constexpr (type == PKBStorageType::Type::MODIFIES_PROCEDURE) {
      return modifiesProcedureStorage;
    } else if constexpr (type == PKBStorageType::Type::USES_PROCEDURE) {
      return usesProcedureStorage;
    } else if constexpr (type == PKBStorageType::Type::CALLS) {
      return callsStorage;
    } else if constexpr (type == PKBStorageType::Type::MODIFIES_STATEMENT) {
      return modifiesStatementStorage;
    } else if constexpr (type == PKBStorageType::Type::USES_STATEMENT) {
      return usesStatementStorage;
    } else {
      assert(false);
    }
  }

  template <PKBStorageType::Type type, typename T, typename U>
  inline bool getRelationshipExists(T argOne, U argTwo) {
    auto storageObject = getSuchThatStorage<type>();
    return storageObject->getRelationshipExists(argOne, argTwo);
  };

  template <PKBStorageType::Type type, typename T>
  inline auto getFirstArgRelationships(T argOne) {
    auto storageObject = getSuchThatStorage<type>();
    return storageObject->getFirstArgRelationships(argOne);
  }

  template <PKBStorageType::Type type, typename U>
  inline auto getSecondArgRelationships(U argOne) {
    auto storageObject = getSuchThatStorage<type>();
    return storageObject->getSecondArgRelationships(argOne);
  }

  template <PKBStorageType::Type type>
  inline bool hasRelationship() {
    auto storageObject = getSuchThatStorage<type>();
    return !storageObject->empty();
  }

  template <PKBStorageType::Type type, typename T, typename U>
  inline bool getStarRelationshipExists(T argOne, U argTwo) {
    auto storageObject = getSuchThatStorage<type>();
    return storageObject->getStarRelationshipExists(argOne, argTwo);
  };

  template <PKBStorageType::Type type, typename T>
  inline auto getFirstArgStarRelationships(T argOne) {
    auto storageObject = getSuchThatStorage<type>();
    return storageObject->getFirstArgStarRelationships(argOne);
  }

  template <PKBStorageType::Type type, typename U>
  inline auto getSecondArgStarRelationships(U argOne) {
    auto storageObject = getSuchThatStorage<type>();
    return storageObject->getSecondArgStarRelationships(argOne);
  }

  template <PKBStorageType::Type type>
  inline bool hasStarRelationship() {
    auto storageObject = getSuchThatStorage<type>();
    return !storageObject->starEmpty();
  }

  template <PKBStorageType::Type type, typename T, typename U>
  inline void addRelationship(T argOne, U argTwo) {
    auto storageObject = getSuchThatStorage<type>();
    storageObject->storeInformation(argOne, argTwo);
  }
};
}  // namespace PKB
