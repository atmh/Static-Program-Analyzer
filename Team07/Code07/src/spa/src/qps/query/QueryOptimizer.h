#pragma once

#include "qps/query/Query.h"

namespace QPS {

class QueryOptimizer {
 public:
  QueryOptimizer(const Query& query);

  Query optimize(const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
                 const std::shared_ptr<NormalizedDataStorage>& dataStorage,
                 const std::shared_ptr<EvaluatorCache>& evaluatorCache);

 private:
  Query query;
};

}  // namespace QPS
