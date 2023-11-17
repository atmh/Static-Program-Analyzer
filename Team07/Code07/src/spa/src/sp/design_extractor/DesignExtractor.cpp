#include "sp/design_extractor/DesignExtractor.h"
#include "sp/node/ProcedureNode.h"
#include "sp/node/ProgramNode.h"
#include "sp/node/StmtLstNode.h"
#include "sp/node/stmt_nodes/AssignNode.h"
#include "sp/node/stmt_nodes/CallNode.h"
#include "sp/node/stmt_nodes/IfNode.h"
#include "sp/node/stmt_nodes/PrintNode.h"
#include "sp/node/stmt_nodes/ReadNode.h"
#include "sp/node/stmt_nodes/WhileNode.h"

namespace SP {
void DesignExtractor::visitRead(const std::shared_ptr<ReadNode>& node) {
  return;
}

void DesignExtractor::visitPrint(const std::shared_ptr<PrintNode>& node) {
  return;
}

void DesignExtractor::visitCall(const std::shared_ptr<CallNode>& node) {
  return;
}

void DesignExtractor::visitWhile(const std::shared_ptr<WhileNode>& node) {
  return;
}

void DesignExtractor::visitIf(const std::shared_ptr<IfNode>& node) {
  return;
}

void DesignExtractor::visitAssign(const std::shared_ptr<AssignNode>& node) {
  return;
}

void DesignExtractor::visitProcedure(
    const std::shared_ptr<ProcedureNode>& node) {
  return;
}

void DesignExtractor::visitStmtList(const std::shared_ptr<StmtLstNode>& node) {
  return;
}

void DesignExtractor::visitProgram(const std::shared_ptr<ProgramNode>& node) {
  return;
}

bool DesignExtractor::isSubtreeComputed(
    std::shared_ptr<Node> node, std::function<void(void)> postProcessingFn) {
  if (!visitedStack.empty() && node == visitedStack.top()) {
    visitedStack.pop();
    postProcessingFn();
    return true;
  }
  return false;
}

DesignExtractor::~DesignExtractor() = default;
}  // namespace SP
