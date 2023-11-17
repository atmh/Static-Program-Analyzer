#pragma once

#include <string>

#include "TokenType.h"

namespace Common {

class Token {
 public:
  Token(std::string val, TokenType tokenType);
  const std::string& getValue() const noexcept;
  TokenType getType() const noexcept;
  friend bool operator==(const Common::Token& a, const Common::Token& b);

 private:
  const std::string val;
  const TokenType tokenType;
};

}  // namespace Common
