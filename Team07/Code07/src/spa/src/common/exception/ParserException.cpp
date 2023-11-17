#include "ParserException.h"

namespace Common {

ParserException::ParserException(const std::string& errorMessage)
    : SyntaxException(errorMessage) {}

}  // namespace Common
