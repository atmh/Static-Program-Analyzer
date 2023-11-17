#pragma once

#include <memory>

#include "pkb/PKBStorageReadInterface.h"
#include "qps/query/Query.h"
#include "qps/query/QueryResult.h"
#include "qps/table/Table.h"

namespace QPS {

class EvaluatorFacade {
 public:
  QueryResult evaluate(const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
                       const Query& query);
};

}  // namespace QPS
