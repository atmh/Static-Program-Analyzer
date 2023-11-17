#pragma once

#include <string>
#include <utility>
#include <vector>

#include "common/exception/Messages.h"
#include "common/exception/ParserException.h"
#include "common/token/Token.h"

namespace Common {
class Parser {
 private:
  std::vector<Token> tokens;
  int index = 0;

 protected:
  Token peek();
  Token get();

  bool hasNext();
  bool isCurrentType(TokenType type);
  bool isCurrentValue(const std::string& value);

  Token parseToken(TokenType type);
  Token parseToken(const std::string& value);

 public:
  virtual void parse() = 0;

  explicit Parser(std::vector<Token> tokens);
};
}  // namespace Common
