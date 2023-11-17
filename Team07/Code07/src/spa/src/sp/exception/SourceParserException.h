#pragma once

#include <string>

#include "common/exception/ParserException.h"

namespace SP {
class SourceParserException : public Common::ParserException {
 public:
  explicit SourceParserException(const std::string& errorMessage);
};
}  // namespace SP
