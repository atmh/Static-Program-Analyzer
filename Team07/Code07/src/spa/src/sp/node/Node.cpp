#include "sp/node/Node.h"

namespace SP {
Node::Node(const std::vector<std::shared_ptr<Node>> children)
    : children(children){};

Node::~Node() = default;

std::vector<std::shared_ptr<Node>> Node::getChildren() {
  return children;
}
}  // namespace SP
