#pragma once

#include <memory>

#include "pkb/PKBStorageReadInterface.h"
#include "qps/evaluator/EvaluatorCache.h"
#include "qps/table/NormalizedDataStorage.h"
#include "qps/table/Table.h"

namespace QPS {

class Evaluator {
 public:
  // evaluate will query pkb and store results in table by using QPS data
  // normalizer
  virtual Table evaluate(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache = nullptr) = 0;
  virtual ~Evaluator() = 0;
};

}  // namespace QPS
