#include "TokenizerException.h"

namespace Common {

TokenizerException::TokenizerException(const std::string& errorMessage)
    : SyntaxException(errorMessage) {}

}  // namespace Common
