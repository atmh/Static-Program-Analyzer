#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "qps/query/declaration/Declaration.h"

namespace QPS {

class Argument {
 public:
  struct ArgHash {
    size_t operator()(const Argument& arg) const noexcept;
  };

  enum class ArgumentType {
    SYNONYM,
    WILDCARD,
    STRING,
    INTEGER,
    EXPR,
  };

  // Wild card argument
  Argument()
      : argumentType(ArgumentType::WILDCARD),
        x(),
        str(),
        declaration(),
        expr(),
        exactMatch() {}

  // integer argument
  Argument(int x)
      : argumentType(ArgumentType::INTEGER),
        x(x),
        str(),
        declaration(),
        expr(),
        exactMatch() {}

  // string argument
  Argument(const std::string& str)
      : argumentType(ArgumentType::STRING),
        x(),
        str(str),
        declaration(),
        expr(),
        exactMatch() {}

  // synonym
  Argument(const std::shared_ptr<Declaration>& declaration)
      : argumentType(ArgumentType::SYNONYM),
        x(),
        str(),
        declaration(declaration),
        expr(),
        exactMatch() {}

  // tree
  Argument(const std::vector<std::string>& expr, bool exactMatch)
      : argumentType(ArgumentType::EXPR),
        x(),
        str(),
        declaration(),
        expr(expr),
        exactMatch(exactMatch) {}
  ArgumentType getArgumentType() const noexcept { return argumentType; }

  operator int() const { return x; }
  operator std::string() const { return str; }
  operator std::shared_ptr<Declaration>() const { return declaration; }
  operator std::pair<std::vector<std::string>, bool>() const {
    return {expr, exactMatch};
  }

  friend bool operator==(const Argument& lhs, const Argument& rhs) noexcept;

 private:
  ArgumentType argumentType;
  // not sure if this is ideal, leave it for now
  int x;
  std::string str;
  std::shared_ptr<Declaration> declaration;
  std::vector<std::string> expr;
  bool exactMatch;
};

}  // namespace QPS
