#include "sp/extractor_adapter/adapters/EntityAdapterProxy.h"

namespace SP {
EntityAdapterProxy::EntityAdapterProxy(
    const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
    : pkb(pkb),
      assignAdapter(pkb),
      callAdapter(pkb),
      ifAdapter(pkb),
      printAdapter(pkb),
      procedureAdapter(pkb),
      readAdapter(pkb),
      whileAdapter(pkb) {}

void EntityAdapterProxy::adapt(
    std::vector<std::shared_ptr<AssignNode>> assigns) {
  assignAdapter.adapt(assigns);
}

void EntityAdapterProxy::adapt(std::vector<std::shared_ptr<CallNode>> calls) {
  callAdapter.adapt(calls);
}

void EntityAdapterProxy::adapt(std::vector<std::shared_ptr<IfNode>> ifs) {
  ifAdapter.adapt(ifs);
}

void EntityAdapterProxy::adapt(std::vector<std::shared_ptr<PrintNode>> prints) {
  printAdapter.adapt(prints);
}

void EntityAdapterProxy::adapt(
    std::vector<std::shared_ptr<ProcedureNode>> procedures) {
  procedureAdapter.adapt(procedures);
}

void EntityAdapterProxy::adapt(std::vector<std::shared_ptr<ReadNode>> reads) {
  readAdapter.adapt(reads);
}

void EntityAdapterProxy::adapt(std::vector<std::shared_ptr<WhileNode>> whiles) {
  whileAdapter.adapt(whiles);
}

}  // namespace SP
