#pragma once

#include <string>

#include "common/exception/ParserException.h"

namespace QPS {
class QPSParserException : public Common::ParserException {
 public:
  explicit QPSParserException(const std::string& error_message);
};
}  // namespace QPS
