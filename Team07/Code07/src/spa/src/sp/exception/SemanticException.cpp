#include "SemanticException.h"

namespace SP {
SemanticException::SemanticException(const std::string& errorMessage)
    : Common::SemanticException(errorMessage) {}
}  // namespace SP
