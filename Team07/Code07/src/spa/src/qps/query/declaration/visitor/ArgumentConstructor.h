#pragma once

#include <memory>

#include "pkb/PKBStorageReadInterface.h"
#include "qps/query/clauses/Argument.h"
#include "qps/query/declaration/visitor/DeclarationVisitor.h"

namespace QPS {

class ArgumentConstructor : public DeclarationVisitor {
 public:
  ArgumentConstructor(
      int id, const std::shared_ptr<NormalizedDataStorage>& dataStorage);

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

  operator Argument();

  virtual ~ArgumentConstructor() = default;

 private:
  int id;
  std::shared_ptr<NormalizedDataStorage> dataStorage;
  Argument arg;
};

}  // namespace QPS
