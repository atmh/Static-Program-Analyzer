//
// Created by Ramapriyan Srivatsan PD on 18/9/23.
//
#pragma once

#include <memory>
#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

#include "PKBStorage.h"
#include "PKBStorageReadInterface.h"
#include "PKBStorageWriteInterface.h"

namespace PKB {

class PKBStorageReadAPI : public PKBStorageReadInterface {
 private:
  std::shared_ptr<PKBStorage> pkbStorage;

 public:
  explicit PKBStorageReadAPI(const std::shared_ptr<PKBStorage> pkbStoragePtr);

  bool getModifiesProcedureRelationshipExists(
      const std::string& argOne, const std::string& argTwo) override;
  std::unordered_set<std::string> getModifiesProcedureFirstArgRelationships(
      const std::string& argOne) override;
  std::unordered_set<std::string> getModifiesProcedureSecondArgRelationships(
      const std::string& argTwo) override;
  bool hasModifiesProcedureRelationship() override;
  bool getModifiesStatementRelationshipExists(
      const int& argOne, const std::string& argTwo) override;
  std::unordered_set<std::string> getModifiesStatementFirstArgRelationships(
      const int& argOne) override;
  std::unordered_set<int> getModifiesStatementSecondArgRelationships(
      const std::string& argTwo) override;
  bool hasModifiesStatementRelationship() override;
  bool getParentRelationshipExists(int argOne, int argTwo) override;
  std::unordered_set<int> getParentFirstArgRelationships(int argOne) override;
  std::unordered_set<int> getParentSecondArgRelationships(int argTwo) override;
  bool hasParentRelationship() override;
  bool getParentStarRelationshipExists(int argOne, int argTwo) override;
  std::unordered_set<int> getParentStarFirstArgRelationships(
      int argOne) override;
  std::unordered_set<int> getParentStarSecondArgRelationships(
      int argTwo) override;
  bool hasParentStarRelationship() override;
  bool getUsesStatementRelationshipExists(int argOne,
                                          const std::string& argTwo) override;
  bool getUsesProcedureRelationshipExists(const std::string& argOne,
                                          const std::string& argTwo) override;
  std::unordered_set<std::string> getUsesStatementFirstArgRelationships(
      int argOne) override;
  std::unordered_set<std::string> getUsesProcedureFirstArgRelationships(
      const std::string& argOne) override;
  std::unordered_set<int> getUsesStatementSecondArgRelationships(
      const std::string& argTwo) override;
  std::unordered_set<std::string> getUsesProcedureSecondArgRelationships(
      const std::string& argTwo) override;
  bool hasUsesProcedureRelationship() override;
  bool hasUsesStatementRelationship() override;
  bool getFollowsRelationshipExists(int argOne, int argTwo) override;
  std::unordered_set<int> getFollowsFirstArgRelationships(int argOne) override;
  std::unordered_set<int> getFollowsSecondArgRelationships(int argTwo) override;
  bool hasFollowsRelationship() override;
  bool getFollowsStarRelationshipExists(int argOne, int argTwo) override;
  std::unordered_set<int> getFollowsStarFirstArgRelationships(
      int argOne) override;
  std::unordered_set<int> getFollowsStarSecondArgRelationships(
      int argTwo) override;
  bool hasFollowsStarRelationship() override;
  bool getCallsRelationshipExists(const std::string& argOne,
                                  const std::string& argTwo) override;
  std::unordered_set<std::string> getCallsFirstArgRelationships(
      const std::string& argOne) override;
  std::unordered_set<std::string> getCallsSecondArgRelationships(
      const std::string& argTwo) override;
  bool hasCallsRelationship() override;
  bool getCallsStarRelationshipExists(const std::string& argOne,
                                      const std::string& argTwo) override;
  std::unordered_set<std::string> getCallsStarFirstArgRelationships(
      const std::string& argOne) override;
  std::unordered_set<std::string> getCallsStarSecondArgRelationships(
      const std::string& argTwo) override;
  bool hasCallsStarRelationship() override;
  bool getNextRelationshipExists(int argOne, int argTwo) override;
  std::unordered_set<int> getNextFirstArgRelationships(int argOne) override;
  std::unordered_set<int> getNextSecondArgRelationships(int argTwo) override;
  bool hasNextRelationship() override;

  const std::unordered_set<int>& getAssigns() const noexcept override;
  const std::unordered_set<int>& getCalls() const noexcept override;
  const std::string getCallProcName(int stmtNo) const noexcept override;
  const std::unordered_set<std::string>& getConstants() const noexcept override;
  const std::unordered_set<int>& getIfs() const noexcept override;
  const std::unordered_set<int>& getPrints() const noexcept override;
  const std::string getPrintVarName(int stmtNo) const noexcept override;
  const std::unordered_set<std::string>& getProcedures()
      const noexcept override;
  const std::unordered_set<int>& getReads() const noexcept override;
  const std::string getReadVarName(int stmtNo) const noexcept override;
  const std::unordered_set<int>& getStmts() const noexcept override;
  const std::unordered_set<std::string>& getVariables() const noexcept override;
  const std::unordered_set<int>& getWhiles() const noexcept override;

  const std::unordered_map<
      std::string, std::vector<std::pair<std::vector<std::string>, int>>>&
  getAssignPatterns() const noexcept override;
  const std::vector<std::pair<std::vector<std::string>, int>>&
  getAssignFirstArgPatterns(const std::string& lhsArg) const noexcept override;
  virtual const std::unordered_map<std::string, std::unordered_set<int>>&
  getIfPatterns() const noexcept override;
  virtual const std::unordered_set<int>& getIfFirstArgPatterns(
      const std::string& varArg) const noexcept override;
  virtual const std::unordered_map<std::string, std::unordered_set<int>>&
  getWhilePatterns() const noexcept override;
  virtual const std::unordered_set<int>& getWhileFirstArgPatterns(
      const std::string& varArg) const noexcept override;

  virtual ~PKBStorageReadAPI() = default;
};
}  // namespace PKB
