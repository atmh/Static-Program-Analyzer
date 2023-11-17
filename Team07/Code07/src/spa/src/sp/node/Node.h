#pragma once
#include <memory>
#include <vector>

#include "sp/design_extractor/DesignExtractor.h"

namespace SP {
class DesignExtractor;

class Node {
 protected:
  std::vector<std::shared_ptr<Node>> children;

 public:
  Node(const std::vector<std::shared_ptr<Node>> children);

  virtual void accept(DesignExtractor& extractor) = 0;
  std::vector<std::shared_ptr<Node>> getChildren();

  virtual ~Node() = 0;
};
}  // namespace SP
