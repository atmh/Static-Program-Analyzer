#include "SourceTokenizer.h"

#include "common/token/Token.h"
#include "sp/exception/Messages.h"
#include "sp/exception/SourceTokenizerException.h"

namespace SP {
SourceTokenizer::SourceTokenizer(const std::istream* stream)
    : Common::Tokenizer(stream) {}

std::unordered_set<char> specialChar({'{', '}', '(', ')', ';', '%', '+', '-',
                                      '*', '/', '>', '<', '=', '!', '&', '|'});

std::unordered_set<char> firstChar({'&', '|', '>', '<', '=', '!'});

std::unordered_set<char> secondChar({'&', '|', '='});

std::unordered_set<char> validSingleChar({'>', '<', '=', '!'});

std::unordered_set<std::string> validDoubleChar({"&&", "||",
                                                 ">=", "<=", "==", "!="});

bool SourceTokenizer::isValidSpecial() {
  return specialChar.find(input[cur]) != specialChar.end();
}

std::string SourceTokenizer::getSpecial() {
  std::string res;
  char c = input[cur++];
  res += c;
  if (firstChar.find(c) ==
      firstChar.end()) { /* first char is not a double char */
    return res;
  }

  if (cur == input.size()) {
    throw SourceTokenizerException(TOKENIZER_INVALID_OPERATION);
  }

  if (secondChar.find(input[cur]) !=
      secondChar.end()) { /* if second char is a valid double */
    res += input[cur++];
    if (validDoubleChar.find(res) ==
        validDoubleChar.end()) { /* if double is not valid */
      throw SourceTokenizerException(TOKENIZER_INVALID_OPERATION);
    }
  } else if (validSingleChar.find(c) ==
             validSingleChar.end()) { /* if first char is not valid single op */
    throw SourceTokenizerException(TOKENIZER_INVALID_OPERATION);
  }

  return res;
}

Common::Token SourceTokenizer::readSpecialToken() {
  if (isValidSpecial()) {
    std::string res = getSpecial();
    return {res, Common::TokenType::special};
  } else {
    throw SourceTokenizerException(TOKENIZER_INVALID_SPECIAL_TOKEN);
  }
}

}  // namespace SP
