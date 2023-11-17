#include "sp/design_extractor/ExtractorManager.h"

namespace SP {

ExtractorManager::ExtractorManager(ExtractorFactory& extractorFactory)
    : extractorFactory(extractorFactory) {}

void ExtractorManager::dfs(
    const std::shared_ptr<Node>& node,
    const std::vector<std::shared_ptr<DesignExtractor>>& extractors) {
  if (node == nullptr)
    return;

  dispatchExtractors(node, extractors);
  for (const auto& child : node->getChildren()) {
    dfs(child, extractors);
  }

  dispatchExtractors(node, extractors);
}

void ExtractorManager::dispatchExtractors(
    const std::shared_ptr<Node>& node,
    const std::vector<std::shared_ptr<DesignExtractor>>& extractors) {
  for (const auto& extractor : extractors) {
    if (extractor == nullptr)
      return;

    node->accept(*extractor);
  }
}

void ExtractorManager::extract(
    const std::shared_ptr<ProgramNode>& programNode) {
  if (programNode == nullptr) {
    return;
  }
  std::vector<std::shared_ptr<DesignExtractor>> extractors =
      extractorFactory.getAllExtractors();
  dfs(programNode, extractors);

  for (const auto& extractor : extractors) {
    extractor->sendDataToAdapter();
  }
}
}  // namespace SP
