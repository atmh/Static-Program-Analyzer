#include "sp/design_extractor/extractors/CallExtractor.h"

#include <algorithm>

#include "sp/exception/Messages.h"
#include "sp/exception/SemanticException.h"

namespace SP {
CallExtractor::CallExtractor(const CallAdapter& adapter) : adapter(adapter) {}

void CallExtractor::sendDataToAdapter() {
  adapter.adapt(callPairs);
}

std::vector<
    std::pair<std::shared_ptr<ProcedureNode>, std::shared_ptr<CallNode>>>
CallExtractor::getStorage() {
  return callPairs;
}

void CallExtractor::visitProcedure(const std::shared_ptr<ProcedureNode>& node) {
  if (isSubtreeComputed(node))
    return;

  currentProcedure = node;
  procedures.push_back(node->name);
  visitedStack.push(node);
}

void CallExtractor::visitCall(const std::shared_ptr<CallNode>& node) {
  if (isSubtreeComputed(node))
    return;

  calls[currentProcedure->name].push_back(node->name);
  callPairs.push_back(std::make_pair(currentProcedure, node));
  visitedStack.push(node);
}

void CallExtractor::visitProgram(const std::shared_ptr<ProgramNode>& node) {
  if (isSubtreeComputed(node, [this]() { this->doSemanticCheck(); }))
    return;

  visitedStack.push(node);
}

std::pair<std::queue<std::string>, std::unordered_map<std::string, int>>
CallExtractor::getIndegreeZeroNodes(
    std::unordered_set<std::string>& procedureSet,
    std::unordered_map<std::string, std::vector<std::string>> calls) {
  std::queue<std::string> result{};
  std::unordered_map<std::string, int> indegrees;

  for (const auto& [_, procedureCalls] : calls) {
    for (const auto& call : procedureCalls) {
      if (procedureSet.find(call) == procedureSet.end()) {
        throw SemanticException(CALL_NON_EXSISTENT_PROCEDURE);
      }
      indegrees[call]++;
    }
  }

  for (const auto& procedure : procedures) {
    if (indegrees[procedure] == 0) {
      result.push(procedure);
    }
  }

  return std::make_pair(result, indegrees);
}

std::vector<std::string> CallExtractor::toposort(
    std::unordered_set<std::string>& procedureSet,
    std::unordered_map<std::string, std::vector<std::string>>& calls) {
  std::vector<std::string> sorted{};

  auto [q, indegrees] = getIndegreeZeroNodes(procedureSet, calls);
  while (!q.empty()) {
    auto curr = q.front();
    q.pop();
    sorted.push_back(curr);
    for (auto& v : calls[curr]) {
      --indegrees[v];
      if (indegrees[v] == 0) {
        q.push(v);
      }
    }
  }

  return sorted;
}

void CallExtractor::doSemanticCheck() {
  // checks if all procedure names are unique
  std::unordered_set<std::string> procedureSet;
  for (const auto& procedure : procedures) {
    if (procedureSet.find(procedure) != procedureSet.end()) {
      throw SemanticException(DUPLICATED_PROCEDURE);
    }
    procedureSet.insert(procedure);
  }

  std::vector<std::string> sorted = toposort(procedureSet, calls);
  if (sorted.size() != procedures.size()) {
    throw SemanticException(RECURSIVE_OR_CYCLIC_CALL);
  }
}

}  // namespace SP
