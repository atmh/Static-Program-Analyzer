#include "ShuntingYardException.h"

namespace Common {

ShuntingYardException::ShuntingYardException(const std::string& errorMessage)
    : SyntaxException(errorMessage) {}

}  // namespace Common
