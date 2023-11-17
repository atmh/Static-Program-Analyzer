#pragma once

#include <memory>
#include <vector>

#include "qps/query/Query.h"
#include "qps/query/declaration/Declaration.h"

namespace QPS {
class Validator {
 public:
  explicit Validator(const Query& q,
                     const std::vector<std::string> declaredNames);
  bool validate();

 private:
  const Query& q;
  const std::vector<std::string> declaredNames;
};
}  // namespace QPS
