#include "QPSTokenizerException.h"

namespace QPS {
QPSTokenizerException::QPSTokenizerException(const std::string& error_message)
    : Common::TokenizerException(error_message) {}
}  // namespace QPS
