#pragma once

#include <memory>
#include <vector>

#include "pkb/PKBStorageReadInterface.h"
#include "qps/query/declaration/visitor/DeclarationVisitor.h"
#include "qps/table/NormalizedDataStorage.h"

namespace QPS {

// Select all
class DeclarationSelector : public DeclarationVisitor {
 public:
  explicit DeclarationSelector(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage);

  virtual void visit(const AssignDeclaration& assign) override;
  virtual void visit(const CallDeclaration& call) override;
  virtual void visit(const ConstantDeclaration& constant) override;
  virtual void visit(const IfDeclaration& ifDeclaration) override;
  virtual void visit(const PrintDeclaration& print) override;
  virtual void visit(const ProcedureDeclaration& procedure) override;
  virtual void visit(const ReadDeclaration& read) override;
  virtual void visit(const StatementDeclaration& stmt) override;
  virtual void visit(const VariableDeclaration& variable) override;
  virtual void visit(const WhileDeclaration& whileDeclaration) override;

  const std::unordered_set<int>& getResult() const noexcept;

  virtual ~DeclarationSelector() = default;

 private:
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb;
  std::shared_ptr<NormalizedDataStorage> dataStorage;
  std::unordered_set<int> result;
};

}  // namespace QPS
