#pragma once

#include <stdexcept>
#include <string>

namespace Common {

class SyntaxException : public std::runtime_error {
 public:
  explicit SyntaxException(const std::string& errorMessage);
};

}  // namespace Common
