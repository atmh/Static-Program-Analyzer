#include "Token.h"

namespace Common {

Token::Token(std::string val, TokenType tokenType)
    : val(std::move(val)), tokenType(tokenType) {}

const std::string& Token::getValue() const noexcept {
  return val;
}

TokenType Token::getType() const noexcept {
  return tokenType;
}

bool operator==(const Common::Token& a, const Common::Token& b) {
  return a.val == b.val && a.tokenType == b.tokenType;
}

}  // namespace Common
