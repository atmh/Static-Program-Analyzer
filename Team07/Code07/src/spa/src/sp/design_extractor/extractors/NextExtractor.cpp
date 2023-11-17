#include "sp//design_extractor/extractors/NextExtractor.h"

#include <cassert>

#include "sp/node/StmtLstNode.h"
#include "sp/node/StmtNode.h"
#include "sp/node/stmt_nodes/IfNode.h"
#include "sp/node/stmt_nodes/WhileNode.h"

namespace SP {
NextExtractor::NextExtractor(const NextAdapter& adapter) : adapter(adapter) {}

void NextExtractor::visitStmtList(const std::shared_ptr<StmtLstNode>& node) {
  if (isSubtreeComputed(node))
    return;

  std::shared_ptr<Node> prevStmt = nullptr;
  auto children = node->getChildren();
  for (auto& stmt : children) {
    if (prevStmt == nullptr) {
      prevStmt = stmt;
      continue;
    }

    // add post if link
    std::shared_ptr<IfNode> prev = std::dynamic_pointer_cast<IfNode>(prevStmt);
    if (prev != nullptr) {
      postIfLink.insert(std::make_pair(prev, stmt));
    } else {
      storage.push_back(std::make_pair(prevStmt, stmt));
    }

    prevStmt = stmt;
  }

  visitedStack.push(node);
}

void NextExtractor::visitWhile(const std::shared_ptr<WhileNode>& node) {
  if (isSubtreeComputed(node))
    return;

  assert(node->getChildren().size() == 1);

  auto stmtLst = node->getChildren()[0];
  auto children = stmtLst->getChildren();
  if (children.size() == 0) {
    return;
  }

  auto firstStmt = children[0];
  auto lastStmt = children[children.size() - 1];

  storage.push_back(std::make_pair(node, firstStmt));
  auto last = std::dynamic_pointer_cast<IfNode>(lastStmt);
  if (last == nullptr) {
    storage.push_back(std::make_pair(lastStmt, node));
  } else {
    postIfLink.insert(std::make_pair(last, node));
  }

  visitedStack.push(node);
}

void NextExtractor::visitIf(const std::shared_ptr<IfNode>& node) {
  if (isSubtreeComputed(node))
    return;

  assert(node->getChildren().size() == 2);

  auto addPreAndPostIfLinks = [&](const std::shared_ptr<Node>& stmtLst) {
    auto children = stmtLst->getChildren();
    if (children.size() == 0) {
      return;
    }

    auto firstStmt = children[0];
    auto lastStmt = children[children.size() - 1];
    storage.push_back(std::make_pair(node, firstStmt));
    auto last = std::dynamic_pointer_cast<IfNode>(lastStmt);

    if (postIfLink.find(node) == postIfLink.end()) {
      return;
    }

    if (last == nullptr) {
      storage.push_back(std::make_pair(lastStmt, postIfLink[node]));
    } else {
      postIfLink.insert(std::make_pair(last, postIfLink[node]));
      postIfLink.insert(std::make_pair(last, postIfLink[node]));
    }
  };

  auto thenStmtLst = node->getChildren()[0];
  auto elseStmtLst = node->getChildren()[1];

  addPreAndPostIfLinks(thenStmtLst);
  addPreAndPostIfLinks(elseStmtLst);

  visitedStack.push(node);
}

void NextExtractor::sendDataToAdapter() {
  adapter.adapt(storage);
}

NextExtractor::NextPairs NextExtractor::getStorage() {
  return storage;
}

}  // namespace SP
