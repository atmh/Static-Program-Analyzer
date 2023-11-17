#pragma once

#include <stdexcept>
#include <string>

namespace Common {

class SemanticException : public std::runtime_error {
 public:
  explicit SemanticException(const std::string& errorMessage);
};

}  // namespace Common
