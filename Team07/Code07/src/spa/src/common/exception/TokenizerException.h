#pragma once

#include <stdexcept>
#include <string>

#include "SyntaxException.h"

namespace Common {

class TokenizerException : public SyntaxException {
 public:
  explicit TokenizerException(const std::string& errorMessage);
};

}  // namespace Common
