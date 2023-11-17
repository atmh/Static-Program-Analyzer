#pragma once

#include <memory>
#include <string>

#include "pkb/PKBStorageReadInterface.h"
#include "qps/query/declaration/visitor/DeclarationVisitor.h"

namespace QPS {

class DeclarationStringSerializer : public DeclarationVisitor {
 public:
  explicit DeclarationStringSerializer(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      int declarationId);

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

  const std::string& getResult() const noexcept;

  virtual ~DeclarationStringSerializer() = default;

 private:
  void decodeInt();
  void decodeString();

 private:
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb;
  std::shared_ptr<NormalizedDataStorage> dataStorage;
  std::string result;
  int declarationId;
};

}  // namespace QPS
