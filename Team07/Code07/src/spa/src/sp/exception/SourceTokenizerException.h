#pragma once

#include <string>

#include "common/exception/TokenizerException.h"

namespace SP {

class SourceTokenizerException : public Common::TokenizerException {
 public:
  explicit SourceTokenizerException(const std::string& errorMessage);
};

}  // namespace SP
