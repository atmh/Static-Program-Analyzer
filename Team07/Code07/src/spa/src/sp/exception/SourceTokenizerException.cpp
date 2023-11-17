#include "SourceTokenizerException.h"

namespace SP {
SourceTokenizerException::SourceTokenizerException(
    const std::string& errorMessage)
    : Common::TokenizerException(errorMessage) {}
}  // namespace SP
