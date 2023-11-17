#include "SyntaxException.h"

namespace Common {

SyntaxException::SyntaxException(const std::string& errorMessage)
    : std::runtime_error(errorMessage) {}

}  // namespace Common
