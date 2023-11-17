#pragma once
#include <memory>
#include <queue>

#include "sp/design_extractor/ExtractorFactory.h"
#include "sp/node/ProgramNode.h"

namespace SP {
class ExtractorManager {
 private:
  ExtractorFactory extractorFactory;

  void dfs(const std::shared_ptr<Node>& node,
           const std::vector<std::shared_ptr<DesignExtractor>>& extractors);
  void dispatchExtractors(
      const std::shared_ptr<Node>& node,
      const std::vector<std::shared_ptr<DesignExtractor>>& extractors);

 public:
  ExtractorManager(ExtractorFactory& extractorFactory);
  void extract(const std::shared_ptr<ProgramNode>& programNode);
};
}  // namespace SP
