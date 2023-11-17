#include "Tokenizer.h"

namespace Common {
Token Tokenizer::readInteger() {
  std::string res;

  for (; cur < input.size() && isalnum(input[cur]); cur++) {
    if (!isdigit(input[cur]))
      throw TokenizerException(TOKENIZER_INVALID_INTEGER);
    res += input[cur];
  }

  // Ensure no leading zeros
  if (res.size() > 1 && res[0] == '0')
    throw TokenizerException(TOKENIZER_INVALID_LEADING_ZERO);
  else if (res.empty())
    throw TokenizerException(TOKENIZER_INVALID_INPUT);

  return {res, TokenType::integer};
}

Token Tokenizer::readName() {
  std::string res;

  if (cur < input.size() && !isalpha(input[cur]))
    throw TokenizerException(TOKENIZER_INVALID_NAME);

  for (; cur < input.size() && isalnum(input[cur]); cur++) {
    res += input[cur];
  }

  if (res.empty())
    throw TokenizerException(TOKENIZER_INVALID_INPUT);
  handleSpecialTerminal(res);

  return {res, TokenType::name};
}

Tokenizer::Tokenizer(const std::istream* stream) : cur(0) {
  std::ostringstream sstr;
  sstr << stream->rdbuf();
  input = sstr.str();
}

Tokenizer::Tokenizer(std::string input) : cur(0), input(std::move(input)) {}

std::vector<Token> Tokenizer::tokenize() {
  std::vector<Token> tokens;
  while (cur < input.size()) {
    char c = input[cur];
    if (isspace(c)) {
      cur++;
      continue;
    }

    if (isalpha(c)) {
      tokens.push_back(readName());
    } else if (isdigit(c)) {
      tokens.push_back(readInteger());
    } else {
      tokens.push_back(readSpecialToken());
    }
  }
  return tokens;
}
}  // namespace Common
