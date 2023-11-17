#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "sp/design_extractor/DesignExtractor.h"
#include "sp/extractor_adapter/adapters/EntityAdapterProxy.h"

namespace SP {
class EntityExtractor : public DesignExtractor {
 private:
  EntityAdapterProxy adapterProxy;

 public:
  std::vector<std::shared_ptr<ProcedureNode>> procedures;
  // std::vector<StmtNode> stmts;
  std::vector<std::shared_ptr<ReadNode>> reads;
  std::vector<std::shared_ptr<PrintNode>> prints;
  std::vector<std::shared_ptr<CallNode>> calls;
  std::vector<std::shared_ptr<WhileNode>> whiles;
  std::vector<std::shared_ptr<IfNode>> ifs;
  std::vector<std::shared_ptr<AssignNode>> assigns;

  EntityExtractor(const EntityAdapterProxy& adapterProxy);

  virtual void visitRead(const std::shared_ptr<ReadNode>& node) override;
  virtual void visitPrint(const std::shared_ptr<PrintNode>& node) override;
  virtual void visitCall(const std::shared_ptr<CallNode>& node) override;
  virtual void visitWhile(const std::shared_ptr<WhileNode>& node) override;
  virtual void visitIf(const std::shared_ptr<IfNode>& node) override;
  virtual void visitAssign(const std::shared_ptr<AssignNode>& node) override;
  virtual void visitProcedure(
      const std::shared_ptr<ProcedureNode>& node) override;

  void sendDataToAdapter() override;
};
}  // namespace SP
