#pragma once
#include <functional>
#include <memory>
#include <stack>
#include <unordered_map>

namespace SP {
// forward declaration
class Node;
class ReadNode;
class PrintNode;
class CallNode;
class WhileNode;
class IfNode;
class AssignNode;
class ProcedureNode;
class StmtLstNode;
class ProgramNode;

class DesignExtractor {
 protected:
  std::stack<std::shared_ptr<Node>> visitedStack;

  virtual bool isSubtreeComputed(
      std::shared_ptr<Node> node,
      std::function<void(void)> postProcessingFn = [] {});

 public:
  virtual void visitRead(const std::shared_ptr<ReadNode>& node);
  virtual void visitPrint(const std::shared_ptr<PrintNode>& node);
  virtual void visitCall(const std::shared_ptr<CallNode>& node);
  virtual void visitWhile(const std::shared_ptr<WhileNode>& node);
  virtual void visitIf(const std::shared_ptr<IfNode>& node);
  virtual void visitAssign(const std::shared_ptr<AssignNode>& node);
  virtual void visitProcedure(const std::shared_ptr<ProcedureNode>& node);
  virtual void visitStmtList(const std::shared_ptr<StmtLstNode>& node);
  virtual void visitProgram(const std::shared_ptr<ProgramNode>& node);

  virtual void sendDataToAdapter() = 0;

  virtual ~DesignExtractor() = 0;
};
}  // namespace SP
