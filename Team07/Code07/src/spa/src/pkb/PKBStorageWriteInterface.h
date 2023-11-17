//
// Created by Ramapriyan Srivatsan PD on 5/9/23.
//
#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace PKB {

class PKBStorageWriteInterface {
 private:
 public:
  // Relationships
  virtual void addModifiesProcedureRelationship(const std::string& argOne,
                                                const std::string& argTwo) = 0;
  virtual void addModifiesStatementRelationship(const int& argOne,
                                                const std::string& argTwo) = 0;
  virtual void addParentRelationship(int argOne, int argTwo) = 0;
  virtual void addUsesProcedureRelationship(const std::string& argOne,
                                            const std::string& argTwo) = 0;
  virtual void addUsesStatementRelationship(const int& argOne,
                                            const std::string& argTwo) = 0;
  virtual void addFollowsRelationship(int argOne, int argTwo) = 0;
  virtual void addCallsRelationship(const std::string& argOne,
                                    const std::string& argTwo) = 0;
  virtual void addNextRelationship(int argOne, int argTwo) = 0;

  // Pattern
  virtual void addAssignPattern(int stmtNo, const std::string& lhsArg,
                                const std::vector<std::string>& rhsArg) = 0;
  virtual void addIfPattern(int stmtNo, const std::string& varArg) = 0;
  virtual void addWhilePattern(int stmtNo, const std::string& varArg) = 0;

  // Entity
  virtual void addAssignEntity(int stmtNo) = 0;
  virtual void addCallEntity(int stmtNo, const std::string& procName) = 0;
  virtual void addConstantEntity(const std::string& entity) = 0;
  virtual void addIfEntity(int stmtNo) = 0;
  virtual void addPrintEntity(int stmtNo, const std::string& varName) = 0;
  virtual void addProcedureEntity(const std::string& procName) = 0;
  virtual void addReadEntity(int stmtNo, const std::string& varName) = 0;
  virtual void addVariableEntity(const std::string& varName) = 0;
  virtual void addWhileEntity(int stmtNo) = 0;
  virtual ~PKBStorageWriteInterface() = 0;
};

inline PKBStorageWriteInterface::~PKBStorageWriteInterface() = default;

}  // namespace PKB
