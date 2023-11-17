#pragma once

#include <stdexcept>
#include <string>

#include "SyntaxException.h"

namespace Common {

class ShuntingYardException : public SyntaxException {
 public:
  explicit ShuntingYardException(const std::string& errorMessage);
};

}  // namespace Common
