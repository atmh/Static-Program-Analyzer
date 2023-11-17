#pragma once

#include <string>

#include "common/exception/SemanticException.h"

namespace QPS {
class QPSValidatorException : public Common::SemanticException {
 public:
  explicit QPSValidatorException(const std::string& error_message);
};
}  // namespace QPS
