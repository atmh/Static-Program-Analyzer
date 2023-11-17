#include "sp/design_extractor/extractors/UseExtractor.h"

#include "sp/node/ProcedureNode.h"
#include "sp/node/ProgramNode.h"
#include "sp/node/stmt_nodes/AssignNode.h"
#include "sp/node/stmt_nodes/CallNode.h"
#include "sp/node/stmt_nodes/IfNode.h"
#include "sp/node/stmt_nodes/PrintNode.h"
#include "sp/node/stmt_nodes/WhileNode.h"

namespace SP {
UseExtractor::UseExtractor(const UseAdapter& adapter) : adapter(adapter) {}

void UseExtractor::sendDataToAdapter() {
  adapter.adapt(usesS, usesP);
}

UseExtractor::StmtUsesMap UseExtractor::getStatementStorage() {
  return usesS;
}

UseExtractor::ProcedureUsesMap UseExtractor::getProcedureStorage() {
  return usesP;
}

void UseExtractor::doMerge() {
  std::unordered_set<std::string> visited{};
  std::unordered_map<std::string, int> indeg{};
  for (const auto& [u, nei] : calls) {
    // Intentionally here to ensure all procedures are included in indeg.
    indeg[u] += 0;
    for (const auto& v : nei) {
      indeg[v]++;
    }
  }

  for (const auto& [p, v] : indeg) {
    if (v == 0)
      updateUsesP(p, visited);
  }

  updateUsesS();
}

void UseExtractor::updateUsesP(std::string u,
                               std::unordered_set<std::string>& visited) {
  if (visited.find(u) != visited.end()) {
    return;
  }

  visited.insert(u);
  for (const auto& v : calls[u]) {
    updateUsesP(v, visited);
    usesP[u].insert(usesP[v].begin(), usesP[v].end());
  }
}

void UseExtractor::updateUsesS() {
  for (const auto& [stmt, procedureCalls] : stmtToCalls) {
    for (const auto& procedure : procedureCalls) {
      usesS[stmt].insert(usesP[procedure].begin(), usesP[procedure].end());
    }
  }
}

void UseExtractor::visitAssign(const std::shared_ptr<AssignNode>& node) {
  if (isSubtreeComputed(node))
    return;

  usesS[node].insert(node->exprVar.begin(), node->exprVar.end());
  usesP[currentProcedure].insert(node->exprVar.begin(), node->exprVar.end());

  for (const auto& nesting : ifWhileNests) {
    usesS[nesting].insert(node->exprVar.begin(), node->exprVar.end());
  }
  visitedStack.push(node);
}

void UseExtractor::visitPrint(const std::shared_ptr<PrintNode>& node) {
  if (isSubtreeComputed(node))
    return;

  usesS[node].insert(node->name);
  usesP[currentProcedure].insert(node->name);

  for (const auto& nesting : ifWhileNests) {
    usesS[nesting].insert(node->name);
  }
  visitedStack.push(node);
}

void UseExtractor::visitWhile(const std::shared_ptr<WhileNode>& node) {
  if (isSubtreeComputed(node, [this]() { this->ifWhileNests.pop_back(); }))
    return;

  ifWhileNests.push_back(node);
  usesP[currentProcedure].insert(node->exprVar.begin(), node->exprVar.end());

  for (const auto& nesting : ifWhileNests) {
    usesS[nesting].insert(node->exprVar.begin(), node->exprVar.end());
  }
  visitedStack.push(node);
}

void UseExtractor::visitIf(const std::shared_ptr<IfNode>& node) {
  if (isSubtreeComputed(node, [this]() { this->ifWhileNests.pop_back(); }))
    return;

  ifWhileNests.push_back(node);
  usesP[currentProcedure].insert(node->exprVar.begin(), node->exprVar.end());

  for (const auto& nesting : ifWhileNests) {
    usesS[nesting].insert(node->exprVar.begin(), node->exprVar.end());
  }
  visitedStack.push(node);
}

void UseExtractor::visitProcedure(const std::shared_ptr<ProcedureNode>& node) {
  if (isSubtreeComputed(node))
    return;

  currentProcedure = node->name;

  // intentionally initialized to ensure call graph is complete with all
  // procedures.
  calls[currentProcedure] = {};
  visitedStack.push(node);
}

void UseExtractor::visitCall(const std::shared_ptr<CallNode>& node) {
  if (isSubtreeComputed(node))
    return;

  calls[currentProcedure].insert(node->name);
  stmtToCalls[node].insert(node->name);

  for (const auto& nesting : ifWhileNests) {
    stmtToCalls[nesting].insert(node->name);
  }
  visitedStack.push(node);
}

void UseExtractor::visitProgram(const std::shared_ptr<ProgramNode>& node) {
  if (isSubtreeComputed(node, [this]() { this->doMerge(); }))
    return;

  visitedStack.push(node);
}

}  // namespace SP
