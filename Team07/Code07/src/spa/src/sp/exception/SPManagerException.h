#pragma once

#include <stdexcept>
#include <string>

namespace SP {

class SPManagerException : public std::runtime_error {
 public:
  explicit SPManagerException(const std::string& errorMessage);
};

}  // namespace SP
