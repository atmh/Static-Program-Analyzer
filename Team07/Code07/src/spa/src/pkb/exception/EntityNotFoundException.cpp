#include "EntityNotFoundException.h"

namespace PKB {

EntityNotFoundException::EntityNotFoundException(
    const std::string& errorMessage)
    : std::runtime_error(errorMessage) {}
}  // namespace PKB
