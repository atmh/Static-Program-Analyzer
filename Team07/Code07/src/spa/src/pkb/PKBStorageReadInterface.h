//
// Created by Ramapriyan Srivatsan PD on 5/9/23.
//
#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace PKB {

class PKBStorageReadInterface {
 public:
  virtual bool getFollowsRelationshipExists(int argOne, int argTwo) = 0;
  virtual std::unordered_set<int> getFollowsFirstArgRelationships(
      int argOne) = 0;
  virtual std::unordered_set<int> getFollowsSecondArgRelationships(
      int argTwo) = 0;
  virtual bool hasFollowsRelationship() = 0;
  virtual bool getFollowsStarRelationshipExists(int argOne, int argTwo) = 0;
  virtual std::unordered_set<int> getFollowsStarFirstArgRelationships(
      int argOne) = 0;
  virtual std::unordered_set<int> getFollowsStarSecondArgRelationships(
      int argTwo) = 0;
  virtual bool hasFollowsStarRelationship() = 0;

  virtual bool getModifiesProcedureRelationshipExists(
      const std::string& argOne, const std::string& argTwo) = 0;
  virtual std::unordered_set<std::string>
  getModifiesProcedureFirstArgRelationships(const std::string& argOne) = 0;
  virtual std::unordered_set<std::string>
  getModifiesProcedureSecondArgRelationships(const std::string& argTwo) = 0;
  virtual bool hasModifiesProcedureRelationship() = 0;

  virtual bool getModifiesStatementRelationshipExists(
      const int& argOne, const std::string& argTwo) = 0;
  virtual std::unordered_set<std::string>
  getModifiesStatementFirstArgRelationships(const int& argOne) = 0;
  virtual std::unordered_set<int> getModifiesStatementSecondArgRelationships(
      const std::string& argTwo) = 0;
  virtual bool hasModifiesStatementRelationship() = 0;

  virtual bool getParentRelationshipExists(int argOne, int argTwo) = 0;
  virtual std::unordered_set<int> getParentFirstArgRelationships(
      int argOne) = 0;
  virtual std::unordered_set<int> getParentSecondArgRelationships(
      int argTwo) = 0;
  virtual bool hasParentRelationship() = 0;
  virtual bool getParentStarRelationshipExists(int argOne, int argTwo) = 0;
  virtual std::unordered_set<int> getParentStarFirstArgRelationships(
      int argOne) = 0;
  virtual std::unordered_set<int> getParentStarSecondArgRelationships(
      int argTwo) = 0;
  virtual bool hasParentStarRelationship() = 0;

  virtual bool getUsesStatementRelationshipExists(
      int argOne, const std::string& argTwo) = 0;
  virtual std::unordered_set<std::string> getUsesStatementFirstArgRelationships(
      int argOne) = 0;
  virtual std::unordered_set<int> getUsesStatementSecondArgRelationships(
      const std::string& argTwo) = 0;
  virtual bool getUsesProcedureRelationshipExists(
      const std::string& argOne, const std::string& argTwo) = 0;
  virtual std::unordered_set<std::string> getUsesProcedureFirstArgRelationships(
      const std::string& argOne) = 0;
  virtual std::unordered_set<std::string>
  getUsesProcedureSecondArgRelationships(const std::string& argTwo) = 0;
  virtual bool hasUsesProcedureRelationship() = 0;
  virtual bool hasUsesStatementRelationship() = 0;

  virtual bool getCallsRelationshipExists(const std::string& argOne,
                                          const std::string& argTwo) = 0;
  virtual std::unordered_set<std::string> getCallsFirstArgRelationships(
      const std::string& argOne) = 0;
  virtual std::unordered_set<std::string> getCallsSecondArgRelationships(
      const std::string& argTwo) = 0;
  virtual bool hasCallsRelationship() = 0;
  virtual bool getCallsStarRelationshipExists(const std::string& argOne,
                                              const std::string& argTwo) = 0;
  virtual std::unordered_set<std::string> getCallsStarFirstArgRelationships(
      const std::string& argOne) = 0;
  virtual std::unordered_set<std::string> getCallsStarSecondArgRelationships(
      const std::string& argTwo) = 0;
  virtual bool hasCallsStarRelationship() = 0;

  virtual bool getNextRelationshipExists(int argOne, int argTwo) = 0;
  virtual std::unordered_set<int> getNextFirstArgRelationships(int argOne) = 0;
  virtual std::unordered_set<int> getNextSecondArgRelationships(int argTwo) = 0;
  virtual bool hasNextRelationship() = 0;

  virtual const std::unordered_set<int>& getAssigns() const noexcept = 0;
  virtual const std::unordered_set<int>& getCalls() const noexcept = 0;
  virtual const std::string getCallProcName(int stmtNo) const noexcept = 0;
  virtual const std::unordered_set<std::string>& getConstants()
      const noexcept = 0;
  virtual const std::unordered_set<int>& getIfs() const noexcept = 0;
  virtual const std::unordered_set<int>& getPrints() const noexcept = 0;
  virtual const std::string getPrintVarName(int stmtNo) const noexcept = 0;
  virtual const std::unordered_set<std::string>& getProcedures()
      const noexcept = 0;
  virtual const std::unordered_set<int>& getReads() const noexcept = 0;
  virtual const std::string getReadVarName(int stmtNo) const noexcept = 0;
  virtual const std::unordered_set<int>& getStmts() const noexcept = 0;
  virtual const std::unordered_set<std::string>& getVariables()
      const noexcept = 0;
  virtual const std::unordered_set<int>& getWhiles() const noexcept = 0;
  virtual const std::unordered_map<
      std::string, std::vector<std::pair<std::vector<std::string>, int>>>&
  getAssignPatterns() const noexcept = 0;
  virtual const std::vector<std::pair<std::vector<std::string>, int>>&
  getAssignFirstArgPatterns(const std::string& lhsArg) const noexcept = 0;
  virtual const std::unordered_map<std::string, std::unordered_set<int>>&
  getIfPatterns() const noexcept = 0;
  virtual const std::unordered_set<int>& getIfFirstArgPatterns(
      const std::string& varArg) const noexcept = 0;
  virtual const std::unordered_map<std::string, std::unordered_set<int>>&
  getWhilePatterns() const noexcept = 0;
  virtual const std::unordered_set<int>& getWhileFirstArgPatterns(
      const std::string& varArg) const noexcept = 0;

  virtual ~PKBStorageReadInterface() = 0;
};

inline PKBStorageReadInterface::~PKBStorageReadInterface() = default;

}  // namespace PKB
