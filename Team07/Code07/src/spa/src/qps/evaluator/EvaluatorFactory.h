#pragma once

#include <memory>

#include "qps/evaluator/Evaluator.h"

namespace QPS {

class EvaluatorFactory {
 public:
  virtual std::shared_ptr<Evaluator> createEvaluator() const = 0;
  virtual ~EvaluatorFactory() = 0;
};

}  // namespace QPS
