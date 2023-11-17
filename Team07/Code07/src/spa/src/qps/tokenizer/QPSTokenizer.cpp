#include "QPSTokenizer.h"

#include "common/token/Token.h"
#include "qps/exception/Messages.h"
#include "qps/exception/QPSTokenizerException.h"

namespace QPS {
const char asterisk = '*';
const char hashtag = '#';

const std::unordered_set<std::string> entitiesFollowedByAsterisk{
    "Follows", "Parent", "Calls", "Next"};
const std::unordered_set<char> specialChars{
    '(', ')', '_', '"', '+', '-', '*', '/', '%', ',', ';', '<', '>', '.', '='};
const std::string prefixAllowedForHashTag = "stmt";

QPSTokenizer::QPSTokenizer(std::string s) : Common::Tokenizer(std::move(s)) {}

bool QPSTokenizer::isValidSpecial() {
  return specialChars.find(input[cur]) != specialChars.end();
}

Common::Token QPSTokenizer::readSpecialToken() {
  if (isValidSpecial()) {
    return {std::string(1, input[cur++]), Common::TokenType::special};
  } else {
    throw QPS::QPSTokenizerException(INVALID_TOKEN);
  }
}

void QPSTokenizer::handleSpecialTerminal(std::string& s) {
  if (cur >= input.size())
    return;
  else if (input[cur] == asterisk && entitiesFollowedByAsterisk.find(s) !=
                                         entitiesFollowedByAsterisk.end())
    s += input[cur++];
  else if (input[cur] == hashtag) {
    if (s != prefixAllowedForHashTag)
      throw QPS::QPSTokenizerException(INVALID_TOKEN);
    else
      s += input[cur++];
  }
}
};  // namespace QPS
