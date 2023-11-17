#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "sp/design_extractor/DesignExtractor.h"
#include "sp/extractor_adapter/adapters/UseAdapter.h"
#include "sp/node//stmt_nodes/WhileNode.h"
#include "sp/node/Node.h"
#include "sp/node/stmt_nodes/IfNode.h"

namespace SP {
class UseExtractor : public DesignExtractor {
 private:
  using StmtUsesMap = std::unordered_map<std::shared_ptr<StmtNode>,
                                         std::unordered_set<std::string>>;
  using ProcedureUsesMap =
      std::unordered_map<std::string, std::unordered_set<std::string>>;

  using CallGraph =
      std::unordered_map<std::string, std::unordered_set<std::string>>;

  using StmtToCallsMap = std::unordered_map<std::shared_ptr<StmtNode>,
                                            std::unordered_set<std::string>>;

  UseAdapter adapter;
  StmtUsesMap usesS;
  ProcedureUsesMap usesP;

  StmtToCallsMap stmtToCalls;
  CallGraph calls;

  std::vector<std::shared_ptr<StmtNode>> ifWhileNests;
  std::string currentProcedure;

  void doMerge();
  void updateUsesP(std::string u, std::unordered_set<std::string>& visited);
  void updateUsesS();

 public:
  UseExtractor(const UseAdapter& adapter);

  void visitAssign(const std::shared_ptr<AssignNode>& node) override;
  void visitPrint(const std::shared_ptr<PrintNode>& node) override;
  void visitWhile(const std::shared_ptr<WhileNode>& node) override;
  void visitIf(const std::shared_ptr<IfNode>& node) override;
  void visitProcedure(const std::shared_ptr<ProcedureNode>& node) override;
  void visitCall(const std::shared_ptr<CallNode>& node) override;
  void visitProgram(const std::shared_ptr<ProgramNode>& node) override;

  void sendDataToAdapter() override;

  StmtUsesMap getStatementStorage();
  ProcedureUsesMap getProcedureStorage();
};
}  // namespace SP
