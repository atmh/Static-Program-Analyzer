#pragma once

#include <stdexcept>
#include <string>

#include "common/exception/SemanticException.h"

namespace SP {

class SemanticException : public Common::SemanticException {
 public:
  explicit SemanticException(const std::string& errorMessage);
};

}  // namespace SP
