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

class PKBStorageWriteAPI : public PKBStorageWriteInterface {
 private:
  std::shared_ptr<PKBStorage> pkbStorage;

 public:
  explicit PKBStorageWriteAPI(const std::shared_ptr<PKBStorage>& pkbStoragePtr);

  void addModifiesProcedureRelationship(const std::string& argOne,
                                        const std::string& argTwo) override;
  void addModifiesStatementRelationship(const int& argOne,
                                        const std::string& argTwo) override;
  void addParentRelationship(int argOne, int argTwo) override;
  void addUsesProcedureRelationship(const std::string& argOne,
                                    const std::string& argTwo) override;
  void addUsesStatementRelationship(const int& argOne,
                                    const std::string& argTwo) override;
  void addFollowsRelationship(int argOne, int argTwo) override;
  void addCallsRelationship(const std::string& argOne,
                            const std::string& argTwo) override;
  void addNextRelationship(int argOne, int argTwo) override;

  void addAssignEntity(int stmtNo) override;
  void addCallEntity(int stmtNo, const std::string& procName) override;
  void addConstantEntity(const std::string& entity) override;
  void addIfEntity(int stmtNo) override;
  void addPrintEntity(int stmtNo, const std::string& varName) override;
  void addProcedureEntity(const std::string& procName) override;
  void addReadEntity(int stmtNo, const std::string& varName) override;
  void addVariableEntity(const std::string& varName) override;
  void addWhileEntity(int stmtNo) override;

  void addAssignPattern(int stmtNo, const std::string& lhsArg,
                        const std::vector<std::string>& rhsArg) override;
  void addIfPattern(int stmtNo, const std::string& varArg) override;
  void addWhilePattern(int stmt, const std::string& varArg) override;
  virtual ~PKBStorageWriteAPI() = default;
};
}  // namespace PKB
