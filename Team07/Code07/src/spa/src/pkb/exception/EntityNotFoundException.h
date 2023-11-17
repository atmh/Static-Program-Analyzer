#pragma once

#include <stdexcept>
#include <string>

namespace PKB {

class EntityNotFoundException : public std::runtime_error {
 public:
  explicit EntityNotFoundException(const std::string& errorMessage);
};

}  // namespace PKB
