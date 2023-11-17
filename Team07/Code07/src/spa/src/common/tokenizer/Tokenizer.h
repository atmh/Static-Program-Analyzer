#pragma once

#include <istream>
#include <sstream>
#include <string>
#include <vector>

#include "common/exception/Messages.h"
#include "common/exception/TokenizerException.h"
#include "common/token/Token.h"

namespace Common {

class Tokenizer {
 protected:
  std::string input;
  int cur;

  Token readInteger();
  Token readName();
  virtual Token readSpecialToken() = 0;
  virtual void handleSpecialTerminal(std::string& s){};

 public:
  Tokenizer(std::string input);
  Tokenizer(const std::istream* stream);
  virtual ~Tokenizer() = 0;
  std::vector<Token> tokenize();
};

inline Tokenizer::~Tokenizer() = default;

}  // namespace Common
