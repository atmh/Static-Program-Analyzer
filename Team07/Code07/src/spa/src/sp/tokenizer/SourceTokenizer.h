#pragma once

#include <sstream>
#include <string>
#include <unordered_set>

#include "common/token/Token.h"
#include "common/tokenizer/Tokenizer.h"

namespace SP {

class SourceTokenizer : public Common::Tokenizer {
 private:
  bool isValidSpecial();
  std::string getSpecial();
  Common::Token readSpecialToken() override;

 public:
  SourceTokenizer(const std::istream* stream);
};

}  // namespace SP
