#include "SourceParserException.h"

namespace SP {
SourceParserException::SourceParserException(const std::string& errorMessage)
    : Common::ParserException(errorMessage) {}
}  // namespace SP
