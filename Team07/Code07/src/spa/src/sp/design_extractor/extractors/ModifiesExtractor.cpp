#include "sp/design_extractor/extractors/ModifiesExtractor.h"

#include "sp/node/ProcedureNode.h"
#include "sp/node/ProgramNode.h"
#include "sp/node/stmt_nodes/AssignNode.h"
#include "sp/node/stmt_nodes/CallNode.h"
#include "sp/node/stmt_nodes/IfNode.h"
#include "sp/node/stmt_nodes/ReadNode.h"
#include "sp/node/stmt_nodes/WhileNode.h"

namespace SP {
ModifiesExtractor::ModifiesExtractor(const ModifiesAdapter& adapter)
    : adapter(adapter) {}

void ModifiesExtractor::visitAssign(const std::shared_ptr<AssignNode>& node) {
  if (isSubtreeComputed(node))
    return;

  modifiesS[node].insert(node->name);
  modifiesP[currentProcedure].insert(node->name);

  for (const auto& nesting : ifWhileNests) {
    modifiesS[nesting].insert(node->name);
  }
  visitedStack.push(node);
}

void ModifiesExtractor::visitRead(const std::shared_ptr<ReadNode>& node) {
  if (isSubtreeComputed(node))
    return;

  modifiesS[node].insert(node->name);
  modifiesP[currentProcedure].insert(node->name);

  for (const auto& nesting : ifWhileNests) {
    modifiesS[nesting].insert(node->name);
  }
  visitedStack.push(node);
}

void ModifiesExtractor::visitWhile(const std::shared_ptr<WhileNode>& node) {
  if (isSubtreeComputed(node, [this]() { this->ifWhileNests.pop_back(); }))
    return;

  ifWhileNests.push_back(node);
  visitedStack.push(node);
}

void ModifiesExtractor::visitIf(const std::shared_ptr<IfNode>& node) {
  if (isSubtreeComputed(node, [this]() { this->ifWhileNests.pop_back(); }))
    return;

  ifWhileNests.push_back(node);
  visitedStack.push(node);
}

void ModifiesExtractor::visitProcedure(
    const std::shared_ptr<ProcedureNode>& node) {
  if (isSubtreeComputed(node))
    return;

  currentProcedure = node->name;

  // intentionally initialized to ensure call graph is complete with all
  // procedures.
  calls[currentProcedure] = {};
  visitedStack.push(node);
}

void ModifiesExtractor::visitCall(const std::shared_ptr<CallNode>& node) {
  if (isSubtreeComputed(node))
    return;

  calls[currentProcedure].insert(node->name);
  stmtToCalls[node].insert(node->name);

  for (const auto& nesting : ifWhileNests) {
    stmtToCalls[nesting].insert(node->name);
  }
  visitedStack.push(node);
}

void ModifiesExtractor::visitProgram(const std::shared_ptr<ProgramNode>& node) {
  if (isSubtreeComputed(node, [this]() { this->doMerge(); }))
    return;

  visitedStack.push(node);
}

void ModifiesExtractor::updateModifiesS() {
  for (const auto& [stmt, procedureCalls] : stmtToCalls) {
    for (const auto& procedure : procedureCalls) {
      modifiesS[stmt].insert(modifiesP[procedure].begin(),
                             modifiesP[procedure].end());
    }
  }
}

void ModifiesExtractor::doMerge() {
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
      updateModifiesP(p, visited);
  }

  updateModifiesS();
}

void ModifiesExtractor::updateModifiesP(
    std::string u, std::unordered_set<std::string>& visited) {
  if (visited.find(u) != visited.end()) {
    return;
  }

  visited.insert(u);
  for (const auto& v : calls[u]) {
    updateModifiesP(v, visited);
    modifiesP[u].insert(modifiesP[v].begin(), modifiesP[v].end());
  }
}

void ModifiesExtractor::sendDataToAdapter() {
  adapter.adapt(modifiesS, modifiesP);
}

ModifiesExtractor::StmtModifiesMap ModifiesExtractor::getStatementStorage() {
  return modifiesS;
}

ModifiesExtractor::ProcedureModifiesMap
ModifiesExtractor::getProcedureStorage() {
  return modifiesP;
}
}  // namespace SP
