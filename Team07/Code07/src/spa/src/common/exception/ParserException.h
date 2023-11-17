#pragma once

#include <stdexcept>
#include <string>

#include "SyntaxException.h"

namespace Common {

class ParserException : public SyntaxException {
 public:
  explicit ParserException(const std::string& errorMessage);
};

}  // namespace Common
