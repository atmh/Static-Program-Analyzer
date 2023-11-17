#pragma once

#include <string>

#include "common/exception/TokenizerException.h"

namespace QPS {
class QPSTokenizerException : public Common::TokenizerException {
 public:
  explicit QPSTokenizerException(const std::string& error_message);
};
}  // namespace QPS
