#include "QPSValidatorException.h"

namespace QPS {
QPSValidatorException::QPSValidatorException(const std::string& error_message)
    : Common::SemanticException(error_message) {}
}  // namespace QPS
