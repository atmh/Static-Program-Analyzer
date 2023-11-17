#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "pkb/PKBStorageReadInterface.h"

namespace PKB {

class PKBStorageReadStub : public PKB::PKBStorageReadInterface {
 public:
  PKBStorageReadStub() = default;

  PKBStorageReadStub& withAssigns(const std::vector<int>& assigns) {
    assigns_ = {assigns.begin(), assigns.end()};
    return *this;
  }

  PKBStorageReadStub& withCalls(const std::vector<int>& calls) {
    calls_ = {calls.begin(), calls.end()};
    return *this;
  }

  PKBStorageReadStub& withConstants(const std::vector<std::string>& constants) {
    constants_ = {constants.begin(), constants.end()};
    return *this;
  }

  PKBStorageReadStub& withIfs(const std::vector<int>& ifs) {
    ifs_ = {ifs.begin(), ifs.end()};
    return *this;
  }

  PKBStorageReadStub& withPrints(const std::vector<int>& prints) {
    prints_ = {prints.begin(), prints.end()};
    return *this;
  }

  PKBStorageReadStub& withProcedures(
      const std::vector<std::string>& procedures) {
    procedures_ = {procedures.begin(), procedures.end()};
    return *this;
  }

  PKBStorageReadStub& withReads(const std::vector<int>& reads) {
    reads_ = {reads.begin(), reads.end()};
    return *this;
  }

  PKBStorageReadStub& withStmts(const std::vector<int>& stmts) {
    stmts_ = {stmts.begin(), stmts.end()};
    return *this;
  }

  PKBStorageReadStub& withVariables(const std::vector<std::string>& variables) {
    variables_ = {variables.begin(), variables.end()};
    return *this;
  }

  PKBStorageReadStub& withWhiles(const std::vector<int>& whiles) {
    whiles_ = {whiles.begin(), whiles.end()};
    return *this;
  }

  PKBStorageReadStub& withFollowsRelationship(
      const std::unordered_map<int, std::unordered_set<int>>&
          followsRelationship) {
    followsRelationship_ = followsRelationship;
    return *this;
  }

  /*
   * Getters
   */
  virtual const std::unordered_set<int>& getAssigns() const noexcept override {
    return assigns_;
  }

  virtual const std::unordered_set<int>& getCalls() const noexcept override {
    return calls_;
  }

  virtual const std::unordered_set<std::string>& getConstants()
      const noexcept override {
    return constants_;
  }

  virtual const std::unordered_set<int>& getIfs() const noexcept override {
    return ifs_;
  }

  virtual const std::unordered_set<int>& getPrints() const noexcept override {
    return prints_;
  }

  virtual const std::unordered_set<std::string>& getProcedures()
      const noexcept override {
    return procedures_;
  }

  virtual const std::unordered_set<int>& getReads() const noexcept override {
    return reads_;
  }

  virtual const std::unordered_set<int>& getStmts() const noexcept override {
    return stmts_;
  }

  virtual const std::unordered_set<std::string>& getVariables()
      const noexcept override {
    return variables_;
  };

  virtual const std::unordered_set<int>& getWhiles() const noexcept override {
    return whiles_;
  }

  virtual bool getParentRelationshipExists(int argOne, int argTwo) override {
    return true;
  }

  virtual std::unordered_set<int> getParentFirstArgRelationships(
      int argOne) override {
    return parentFirstArgRelationships_;
  }

  virtual std::unordered_set<int> getParentSecondArgRelationships(
      int argTwo) override {
    return parentSecondArgRelationships_;
  }

  virtual bool hasParentRelationship() override { return true; }

  virtual bool getParentStarRelationshipExists(int argOne,
                                               int argTwo) override {
    return true;
  }

  virtual std::unordered_set<int> getParentStarFirstArgRelationships(
      int argOne) override {
    return parentStarFirstArgRelationships_;
  }

  virtual std::unordered_set<int> getParentStarSecondArgRelationships(
      int argTwo) override {
    return parentStarSecondArgRelationships_;
  }

  virtual bool hasParentStarRelationship() override { return true; }

  virtual bool getFollowsRelationshipExists(int argOne, int argTwo) override {
    auto it = followsRelationship_.find(argOne);
    if (it == followsRelationship_.end())
      return false;
    if (it->second.find(argTwo) == it->second.end())
      return false;
    return true;
  }

  virtual std::unordered_set<int> getFollowsFirstArgRelationships(
      int argOne) override {
    return followsFirstArgRelationships_;
  }

  virtual std::unordered_set<int> getFollowsSecondArgRelationships(
      int argTwo) override {
    return followsSecondArgRelationships_;
  }

  virtual bool hasFollowsRelationship() override { return true; }

  virtual bool getFollowsStarRelationshipExists(int argOne,
                                                int argTwo) override {
    return true;
  }

  virtual std::unordered_set<int> getFollowsStarFirstArgRelationships(
      int argOne) override {
    return followsStarFirstArgRelationships_;
  }

  virtual std::unordered_set<int> getFollowsStarSecondArgRelationships(
      int argTwo) override {
    return followsStarSecondArgRelationships_;
  }

  virtual bool hasFollowsStarRelationship() override { return true; }

  virtual bool getUsesStatementRelationshipExists(
      int argOne, const std::string& argTwo) override {
    return true;
  }

  virtual bool getUsesProcedureRelationshipExists(
      const std::string& argOne, const std::string& argTwo) override {
    return true;
  }

  std::unordered_set<std::string> getUsesStatementFirstArgRelationships(
      int argOne) override {
    return {};
  }

  std::unordered_set<std::string> getUsesProcedureFirstArgRelationships(
      const std::string& argOne) override {
    return {};
  }

  std::unordered_set<int> getUsesStatementSecondArgRelationships(
      const std::string& argTwo) override {
    return {};
  }

  std::unordered_set<std::string> getUsesProcedureSecondArgRelationships(
      const std::string& argTwo) override {
    return {};
  }

  virtual bool hasUsesStatementRelationship() override { return true; }

  virtual bool hasUsesProcedureRelationship() override { return true; }

  virtual bool getModifiesProcedureRelationshipExists(
      const std::string& argOne, const std::string& argTwo) override {
    return true;
  }

  virtual std::unordered_set<std::string>
  getModifiesProcedureFirstArgRelationships(
      const std::string& argOne) override {
    return modifiesFirstArgRelationships_;
  }

  virtual std::unordered_set<std::string>
  getModifiesProcedureSecondArgRelationships(
      const std::string& argTwo) override {
    return modifiesSecondArgRelationships_;
  }

  virtual bool hasModifiesProcedureRelationship() override { return true; }

  virtual bool getModifiesStatementRelationshipExists(
      const int& argOne, const std::string& argTwo) override {
    return true;
  }

  virtual std::unordered_set<std::string>
  getModifiesStatementFirstArgRelationships(const int& argOne) override {
    return modifiesStatementFirstArgRelationships_;
  }

  virtual std::unordered_set<int> getModifiesStatementSecondArgRelationships(
      const std::string& argTwo) override {
    return modifiesStatementSecondArgRelationships_;
  }

  virtual bool hasModifiesStatementRelationship() override { return true; }

  virtual bool getCallsRelationshipExists(const std::string& argOne,
                                          const std::string& argTwo) override {
    return true;
  }

  virtual std::unordered_set<std::string> getCallsFirstArgRelationships(
      const std::string& argOne) override {
    return callsFirstArgRelationships_;
  }

  virtual std::unordered_set<std::string> getCallsSecondArgRelationships(
      const std::string& argTwo) override {
    return callsSecondArgRelationships_;
  }

  virtual bool hasCallsRelationship() override { return true; }

  virtual bool getCallsStarRelationshipExists(
      const std::string& argOne, const std::string& argTwo) override {
    return true;
  }

  virtual std::unordered_set<std::string> getCallsStarFirstArgRelationships(
      const std::string& argOne) override {
    return callsStarFirstArgRelationships_;
  }

  virtual std::unordered_set<std::string> getCallsStarSecondArgRelationships(
      const std::string& argTwo) override {
    return callsStarSecondArgRelationships_;
  }

  virtual bool hasCallsStarRelationship() override { return true; }

  virtual bool getNextRelationshipExists(int argOne, int argTwo) override {
    return true;
  }

  virtual std::unordered_set<int> getNextFirstArgRelationships(
      int argOne) override {
    return nextFirstArgRelationships_;
  }

  virtual std::unordered_set<int> getNextSecondArgRelationships(
      int argTwo) override {
    return nextSecondArgRelationships_;
  }

  virtual bool hasNextRelationship() override { return true; }

  virtual const std::unordered_map<
      std::string, std::vector<std::pair<std::vector<std::string>, int>>>&
  getAssignPatterns() const noexcept override {
    return assignPatterns;
  }

  virtual const std::vector<std::pair<std::vector<std::string>, int>>&
  getAssignFirstArgPatterns(const std::string& lhsArg) const noexcept override {
    return assignVector;
  }

  virtual const std::unordered_map<std::string, std::unordered_set<int>>&
  getIfPatterns() const noexcept override {
    return ifPatterns;
  }

  virtual const std::unordered_set<int>& getIfFirstArgPatterns(
      const std::string& lhsArg) const noexcept override {
    return ifFirstArgs;
  }

  virtual const std::unordered_map<std::string, std::unordered_set<int>>&
  getWhilePatterns() const noexcept override {
    return whilePatterns;
  }

  virtual const std::unordered_set<int>& getWhileFirstArgPatterns(
      const std::string& lhsArg) const noexcept override {
    return whileFirstArgs;
  }

  virtual const std::string getCallProcName(
      int stmtNo) const noexcept override {
    return placeholder;
  }

  virtual const std::string getPrintVarName(
      int stmtNo) const noexcept override {
    return placeholder;
  }

  virtual const std::string getReadVarName(int stmtNo) const noexcept override {
    return placeholder;
  }

  virtual ~PKBStorageReadStub() = default;

 private:
  std::unordered_set<int> assigns_;
  std::unordered_set<int> calls_;
  std::unordered_set<std::string> constants_;
  std::unordered_set<int> ifs_;
  std::unordered_set<int> prints_;
  std::unordered_set<std::string> procedures_;
  std::unordered_set<int> reads_;
  std::unordered_set<int> stmts_;
  std::unordered_set<std::string> variables_;
  std::unordered_set<int> whiles_;
  std::unordered_set<int> parentFirstArgRelationships_;
  std::unordered_set<int> parentSecondArgRelationships_;
  std::unordered_set<int> parentStarFirstArgRelationships_;
  std::unordered_set<int> parentStarSecondArgRelationships_;
  std::unordered_set<int> followsFirstArgRelationships_;
  std::unordered_set<int> followsSecondArgRelationships_;
  std::unordered_set<int> followsStarFirstArgRelationships_;
  std::unordered_set<int> followsStarSecondArgRelationships_;
  std::unordered_set<std::string> usesFirstArgRelationships_;
  std::unordered_set<std::string> usesSecondArgRelationships_;
  std::unordered_set<std::string> modifiesFirstArgRelationships_;
  std::unordered_set<std::string> modifiesSecondArgRelationships_;
  std::unordered_set<std::string> modifiesStatementFirstArgRelationships_;
  std::unordered_set<int> modifiesStatementSecondArgRelationships_;
  std::unordered_set<std::string> callsFirstArgRelationships_;
  std::unordered_set<std::string> callsSecondArgRelationships_;
  std::unordered_set<std::string> callsStarFirstArgRelationships_;
  std::unordered_set<std::string> callsStarSecondArgRelationships_;
  std::unordered_set<int> nextFirstArgRelationships_;
  std::unordered_set<int> nextSecondArgRelationships_;
  std::unordered_map<std::string,
                     std::vector<std::pair<std::vector<std::string>, int>>>
      assignPatterns;
  std::vector<std::pair<std::vector<std::string>, int>> assignVector;
  std::unordered_map<std::string, std::unordered_set<int>> ifPatterns;
  std::unordered_set<int> ifFirstArgs;
  std::unordered_map<std::string, std::unordered_set<int>> whilePatterns;
  std::unordered_set<int> whileFirstArgs;

  // follows relationship map
  std::unordered_map<int, std::unordered_set<int>> followsRelationship_;

  //
  const std::string placeholder = "PLACEHOLDER";
};

}  // namespace PKB
