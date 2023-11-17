#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "pkb/PKBStorageWriteInterface.h"

namespace PKB {

class PKBStorageWriteStub : public PKB::PKBStorageWriteInterface {
 public:
  // entity
  std::unordered_set<std::string> procedureStorage;
  std::unordered_set<int> readStorage;
  std::unordered_set<int> printStorage;
  std::unordered_set<int> callStorage;
  std::unordered_set<int> whileStorage;
  std::unordered_set<int> ifStorage;
  std::unordered_set<int> assignStorage;
  std::unordered_set<std::string> variableStorage;
  std::unordered_set<std::string> constantStorage;
  std::unordered_set<int> statementStorage;

  // relationship
  std::unordered_map<std::string, std::unordered_set<std::string>>
      usesProcedureStorage;
  std::unordered_map<int, std::unordered_set<std::string>> usesStatementStorage;
  std::unordered_map<std::string, std::unordered_set<std::string>>
      modifiesProcedureStorage;
  std::unordered_map<int, std::unordered_set<std::string>>
      modifiesStatementStorage;
  std::unordered_map<int, int> followsStorage;
  std::unordered_map<int, std::unordered_set<int>> parentStorage;
  std::unordered_map<std::string, std::unordered_set<std::string>> callsStorage;
  std::unordered_map<int, std::unordered_set<int>> nextStorage;

  // Pattern
  std::unordered_map<std::string,
                     std::vector<std::pair<std::vector<std::string>, int>>>
      assignPatternStorage;

  std::unordered_map<std::string, std::unordered_set<int>> ifPatternStorage;
  std::unordered_map<std::string, std::unordered_set<int>> whilePatternStorage;

  // Relationship
  void addModifiesProcedureRelationship(const std::string& argOne,
                                        const std::string& argTwo) override;
  void addModifiesStatementRelationship(const int& argOne,
                                        const std::string& argTwo) override;
  void addParentRelationship(int argOne, int argTwo) override;
  void addUsesStatementRelationship(const int& argOne,
                                    const std::string& argTwo) override;
  void addUsesProcedureRelationship(const std::string& argOne,
                                    const std::string& argTwo) override;
  void addFollowsRelationship(int argOne, int argTwo) override;
  void addCallsRelationship(const std::string& argOne,
                            const std::string& argTwo) override;
  void addNextRelationship(int argOne, int argTwo) override;

  // Entity
  void addAssignEntity(int stmtNo) override;
  void addCallEntity(int stmtNo, const std::string& procName) override;
  void addConstantEntity(const std::string& entity) override;
  void addIfEntity(int stmtNo) override;
  void addPrintEntity(int stmtNo, const std::string& varName) override;
  void addProcedureEntity(const std::string& procName) override;
  void addReadEntity(int stmtNo, const std::string& varName) override;
  void addVariableEntity(const std::string& varName) override;
  void addWhileEntity(int stmtNo) override;

  // Pattern
  virtual void addAssignPattern(
      int stmtNo, const std::string& argOne,
      const std::vector<std::string>& argTwo) override;
  virtual void addIfPattern(int stmtNo, const std::string& varArg) override;
  virtual void addWhilePattern(int stmtNo, const std::string& varArg) override;

  ~PKBStorageWriteStub() = default;
};

}  // namespace PKB
