#pragma once
#include <memory>
#include <string>
#include <vector>

#include "sp/extractor_adapter/adapters/EntityAdapters/AssignEntityAdapter.h"
#include "sp/extractor_adapter/adapters/EntityAdapters/CallEntityAdapter.h"
#include "sp/extractor_adapter/adapters/EntityAdapters/IfEntityAdapter.h"
#include "sp/extractor_adapter/adapters/EntityAdapters/PrintEntityAdapter.h"
#include "sp/extractor_adapter/adapters/EntityAdapters/ProcedureEntityAdapter.h"
#include "sp/extractor_adapter/adapters/EntityAdapters/ReadEntityAdapter.h"
#include "sp/extractor_adapter/adapters/EntityAdapters/WhileEntityAdapter.h"

namespace SP {
class EntityAdapterProxy {
 public:
  EntityAdapterProxy(const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb);

  void adapt(std::vector<std::shared_ptr<AssignNode>> assigns);
  void adapt(std::vector<std::shared_ptr<CallNode>> calls);
  void adapt(std::vector<std::shared_ptr<IfNode>> ifs);
  void adapt(std::vector<std::shared_ptr<PrintNode>> prints);
  void adapt(std::vector<std::shared_ptr<ProcedureNode>> procedures);
  void adapt(std::vector<std::shared_ptr<ReadNode>> reads);
  void adapt(std::vector<std::shared_ptr<WhileNode>> whiles);

 private:
  std::shared_ptr<PKB::PKBStorageWriteInterface> pkb;
  AssignEntityAdapter assignAdapter;
  CallEntityAdapter callAdapter;
  IfEntityAdapter ifAdapter;
  PrintEntityAdapter printAdapter;
  ProcedureEntityAdapter procedureAdapter;
  ReadEntityAdapter readAdapter;
  WhileEntityAdapter whileAdapter;
};
}  // namespace SP
