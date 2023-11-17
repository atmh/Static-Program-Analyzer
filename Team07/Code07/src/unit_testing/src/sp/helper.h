#pragma once
#include <unordered_set>
#include <vector>

#include "sp/node/Node.h"
#include "sp/node/ProcedureNode.h"
#include "sp/node/StmtLstNode.h"
#include "sp/node/StmtNode.h"
#include "sp/node/stmt_nodes/AssignNode.h"
#include "sp/node/stmt_nodes/CallNode.h"
#include "sp/node/stmt_nodes/IfNode.h"
#include "sp/node/stmt_nodes/PrintNode.h"
#include "sp/node/stmt_nodes/ReadNode.h"
#include "sp/node/stmt_nodes/WhileNode.h"

using namespace SP;

inline std::vector<std::shared_ptr<AssignNode>> makeAssignNodes(
    const std::vector<int>& stmtNums, const std::vector<std::string>& names,
    const std::vector<std::unordered_set<std::string>>& varNames,
    const std::vector<std::unordered_set<std::string>>& constants) {
  std::vector<std::shared_ptr<AssignNode>> assignNodes;
  for (int i = 0; i < stmtNums.size(); i++) {
    std::shared_ptr<AssignNode> assignNode = std::make_shared<AssignNode>(
        stmtNums[i], names[i], varNames[i], constants[i],
        std::vector<std::string>{""});
    assignNodes.push_back(assignNode);
  }
  return assignNodes;
}

inline std::vector<std::shared_ptr<IfNode>> makeIfNodes(
    const std::vector<int>& stmtNums,
    const std::vector<std::unordered_set<std::string>>& varNames,
    const std::vector<std::unordered_set<std::string>>& constants) {
  std::vector<std::shared_ptr<IfNode>> ifNodes;
  for (int i = 0; i < stmtNums.size(); i++) {
    std::shared_ptr<IfNode> ifNode = std::make_shared<IfNode>(
        stmtNums[i], varNames[i], constants[i],
        std::make_shared<StmtLstNode>(std::vector<std::shared_ptr<Node>>{}),
        std::make_shared<StmtLstNode>(std::vector<std::shared_ptr<Node>>{}));
    ifNodes.push_back(ifNode);
  }
  return ifNodes;
}

inline std::vector<std::shared_ptr<WhileNode>> makeWhileNodes(
    const std::vector<int>& stmtNums,
    const std::vector<std::unordered_set<std::string>>& varNames,
    const std::vector<std::unordered_set<std::string>>& constants) {
  std::vector<std::shared_ptr<WhileNode>> whileNodes;
  for (int i = 0; i < stmtNums.size(); i++) {
    std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(
        stmtNums[i], varNames[i], constants[i],
        std::make_shared<StmtLstNode>(std::vector<std::shared_ptr<Node>>{}));
    whileNodes.push_back(whileNode);
  }
  return whileNodes;
}

inline std::vector<std::shared_ptr<ProcedureNode>> makeProcedureNodes(
    const std::vector<std::string>& procNames) {
  std::vector<std::shared_ptr<ProcedureNode>> procedureNodes;
  for (auto& name : procNames) {
    std::shared_ptr<ProcedureNode> procedureNode =
        std::make_shared<ProcedureNode>(name,
                                        std::vector<std::shared_ptr<Node>>{});
    procedureNodes.push_back(procedureNode);
  }
  return procedureNodes;
}

// read(stmtNum, varName), print(stmtNum, varName), calls(stmtNum,
// varName)
template <typename T>
inline std::vector<std::shared_ptr<T>> makeNodes(
    const std::vector<int>& stmtNums,
    const std::vector<std::string>& varNames) {
  std::vector<std::shared_ptr<T>> nodes;
  for (int i = 0; i < stmtNums.size(); i++) {
    std::shared_ptr<T> node = std::make_shared<T>(stmtNums[i], varNames[i]);
    nodes.push_back(node);
  }
  return nodes;
}

class StmtNodeStub : public StmtNode {
 public:
  StmtNodeStub(int stmtNum)
      : StmtNode(stmtNum, std::vector<std ::shared_ptr<Node>>{}) {}

  void accept(DesignExtractor& extractor) override { return; }
};
