#include "SPManagerException.h"

namespace SP {

SPManagerException::SPManagerException(const std::string& errorMessage)
    : std::runtime_error(errorMessage) {}

}  // namespace SP
