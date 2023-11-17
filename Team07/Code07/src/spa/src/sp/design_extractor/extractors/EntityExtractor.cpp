#include "sp//design_extractor/extractors/EntityExtractor.h"

namespace SP {
EntityExtractor::EntityExtractor(const EntityAdapterProxy& adapterProxy)
    : DesignExtractor(), adapterProxy(adapterProxy) {}

void EntityExtractor::sendDataToAdapter() {
  adapterProxy.adapt(assigns);
  adapterProxy.adapt(calls);
  adapterProxy.adapt(ifs);
  adapterProxy.adapt(prints);
  adapterProxy.adapt(procedures);
  adapterProxy.adapt(reads);
  adapterProxy.adapt(whiles);
}

void EntityExtractor::visitRead(const std::shared_ptr<ReadNode>& node) {
  if (isSubtreeComputed(node))
    return;

  reads.push_back(node);
  visitedStack.push(node);
}

void EntityExtractor::visitPrint(const std::shared_ptr<PrintNode>& node) {
  if (isSubtreeComputed(node))
    return;

  prints.push_back(node);
  visitedStack.push(node);
}

void EntityExtractor::visitCall(const std::shared_ptr<CallNode>& node) {
  if (isSubtreeComputed(node))
    return;

  calls.push_back(node);
  visitedStack.push(node);
}

void EntityExtractor::visitWhile(const std::shared_ptr<WhileNode>& node) {
  if (isSubtreeComputed(node))
    return;

  whiles.push_back(node);
  visitedStack.push(node);
}

void EntityExtractor::visitIf(const std::shared_ptr<IfNode>& node) {
  if (isSubtreeComputed(node))
    return;

  ifs.push_back(node);
  visitedStack.push(node);
}

void EntityExtractor::visitAssign(const std::shared_ptr<AssignNode>& node) {
  if (isSubtreeComputed(node))
    return;

  assigns.push_back(node);
  visitedStack.push(node);
}

void EntityExtractor::visitProcedure(
    const std::shared_ptr<ProcedureNode>& node) {
  if (isSubtreeComputed(node))
    return;

  procedures.push_back(node);
  visitedStack.push(node);
}
}  // namespace SP
