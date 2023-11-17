#pragma once

#include <sstream>
#include <string>
#include <unordered_set>

#include "common/token/Token.h"
#include "common/tokenizer/Tokenizer.h"

namespace QPS {
class QPSTokenizer : public Common::Tokenizer {
 public:
  explicit QPSTokenizer(std::string s);

 private:
  bool isValidSpecial();
  Common::Token readSpecialToken() override;
  void handleSpecialTerminal(std::string& s) override;
};

}  // namespace QPS
