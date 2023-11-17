#include "SemanticException.h"

namespace Common {

SemanticException::SemanticException(const std::string& errorMessage)
    : std::runtime_error(errorMessage) {}

}  // namespace Common
