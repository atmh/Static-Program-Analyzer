#pragma once
#include "sp/extractor_adapter/ExtractorAdapter.h"
#include "sp/node/ProcedureNode.h"
#include "sp/node/stmt_nodes/AssignNode.h"
#include "sp/node/stmt_nodes/CallNode.h"
#include "sp/node/stmt_nodes/IfNode.h"
#include "sp/node/stmt_nodes/PrintNode.h"
#include "sp/node/stmt_nodes/ReadNode.h"
#include "sp/node/stmt_nodes/WhileNode.h"

namespace SP {
class IfEntityAdapter : public ExtractorAdapter {
 public:
  IfEntityAdapter(const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb);
  void adapt(std::vector<std::shared_ptr<IfNode>> ifs);
};
}  // namespace SP
