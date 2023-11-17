#include "QPSParserException.h"

namespace QPS {
QPSParserException::QPSParserException(const std::string& error_message)
    : Common::ParserException(error_message) {}
}  // namespace QPS
