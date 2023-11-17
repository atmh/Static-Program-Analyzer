#pragma once
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "sp/design_extractor/DesignExtractor.h"
#include "sp/extractor_adapter/adapters/CallAdapter.h"
#include "sp/node/ProgramNode.h"

namespace SP {
class CallExtractor : public DesignExtractor {
 private:
  CallAdapter adapter;
  std::shared_ptr<ProcedureNode> currentProcedure;

  std::vector<std::string> procedures;  // nodes

  std::unordered_map<std::string, std::vector<std::string>> calls;  // edges

  std::vector<
      std::pair<std::shared_ptr<ProcedureNode>, std::shared_ptr<CallNode>>>
      callPairs;

  void doSemanticCheck();

  // recursive/cyclick call helper methods
  std::vector<std::string> toposort(
      std::unordered_set<std::string>& procedures,
      std::unordered_map<std::string, std::vector<std::string>>& calls);

  std::pair<std::queue<std::string>, std::unordered_map<std::string, int>>
  getIndegreeZeroNodes(
      std::unordered_set<std::string>& procedureSet,
      std::unordered_map<std::string, std::vector<std::string>> calls);

 public:
  CallExtractor(const CallAdapter& adapter);

  virtual void visitCall(const std::shared_ptr<CallNode>& node) override;
  virtual void visitProcedure(
      const std::shared_ptr<ProcedureNode>& node) override;
  virtual void visitProgram(const std::shared_ptr<ProgramNode>& node) override;

  void sendDataToAdapter() override;

  std::vector<
      std::pair<std::shared_ptr<ProcedureNode>, std::shared_ptr<CallNode>>>
  getStorage();
};
}  // namespace SP
