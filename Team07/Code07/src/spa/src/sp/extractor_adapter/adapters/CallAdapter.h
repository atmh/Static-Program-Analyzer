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
class CallAdapter : public ExtractorAdapter {
 public:
  CallAdapter(const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb);
  void adapt(
      const std::vector<
          std::pair<std::shared_ptr<ProcedureNode>, std::shared_ptr<CallNode>>>&
          callRelationships);
};
}  // namespace SP
