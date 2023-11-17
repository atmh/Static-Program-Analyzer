#include "sp/design_extractor/extractors/ParentExtractor.h"

#include <cassert>

namespace SP {
ParentExtractor::ParentExtractor(const ParentAdapter& adapter)
    : DesignExtractor(), adapter{adapter} {}

std::vector<std::pair<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>>>
ParentExtractor::getStorage() {
  return storage;
}

void ParentExtractor::visitIf(const std::shared_ptr<IfNode>& node) {
  if (isSubtreeComputed(node))
    return;

  std::vector<std::shared_ptr<Node>> children = node->getChildren();

  assert(children.size() == 2);
  std::shared_ptr<StmtLstNode> thenStmts =
      std::dynamic_pointer_cast<StmtLstNode>(children[0]);
  std::shared_ptr<StmtLstNode> elseStmts =
      std::dynamic_pointer_cast<StmtLstNode>(children[1]);

  if (thenStmts == nullptr || elseStmts == nullptr) {
    return;
  }

  for (const auto& stmt : thenStmts->getChildren()) {
    std::shared_ptr<StmtNode> stmtNode =
        std::dynamic_pointer_cast<StmtNode>(stmt);
    if (stmtNode == nullptr)
      continue;

    storage.push_back(std::make_pair(node, stmtNode));
  }

  for (const auto& stmt : elseStmts->getChildren()) {
    std::shared_ptr<StmtNode> stmtNode =
        std::dynamic_pointer_cast<StmtNode>(stmt);
    if (stmtNode == nullptr)
      continue;

    storage.push_back(std::make_pair(node, stmtNode));
  }
  visitedStack.push(node);
}

void ParentExtractor::visitWhile(const std::shared_ptr<WhileNode>& node) {
  if (isSubtreeComputed(node))
    return;

  std::vector<std::shared_ptr<Node>> children = node->getChildren();

  std::shared_ptr<StmtLstNode> stmts =
      std::dynamic_pointer_cast<StmtLstNode>(children[0]);

  if (stmts == nullptr) {
    return;
  }

  for (const auto& stmt : stmts->getChildren()) {
    std::shared_ptr<StmtNode> stmtNode =
        std::dynamic_pointer_cast<StmtNode>(stmt);
    if (stmtNode == nullptr)
      continue;

    storage.push_back(std::make_pair(node, stmtNode));
  }
  visitedStack.push(node);
}

void ParentExtractor::sendDataToAdapter() {
  adapter.adapt(storage);
}
}  // namespace SP
