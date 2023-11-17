#pragma once

#include <memory>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "common/exception/Messages.h"
#include "common/exception/ShuntingYardException.h"
#include "common/token/Token.h"

/**
 * Adapted from these referrences:
 * https://cp-algorithms.com/string/expression_parsing.html#parsing-of-simple-expressions
 * https://en.wikipedia.org/wiki/Shunting_yard_algorithm
 */

namespace Common {

class ShuntingYard {
 public:
  // math expression
  static std::vector<std::string> evalMath(
      std::vector<Token> exprs,
      const std::shared_ptr<std::unordered_set<std::string>>& exprVar,
      const std::shared_ptr<std::unordered_set<std::string>>& exprCon);

  // math expression
  static std::vector<std::string> evalMath(std::vector<Token> exprs);

  // condtional expression
  static void evalCond(
      std::vector<Token> exprs,
      const std::shared_ptr<std::unordered_set<std::string>>& exprVar,
      const std::shared_ptr<std::unordered_set<std::string>>& exprCon);

 private:
  static inline std::unordered_map<std::string, int> rank = {
      {"&&", 1}, {"||", 1}, {"!", 1}, {"<", 2}, {"<=", 2}, {">", 2}, {">=", 2},
      {"==", 2}, {"!=", 2}, {"+", 3}, {"-", 3}, {"*", 4},  {"/", 4}, {"%", 4}};

  static inline std::unordered_set<std::string> mathOp = {"+", "-", "*", "/",
                                                          "%", "(", ")"};

  static inline std::unordered_set<std::string> condOp = {
      "+",  "-", "*",  "/",  "%",  "(",  ")",  ">",
      ">=", "<", "<=", "==", "!=", "&&", "||", "!"};

  static inline std::unordered_set<std::string> relOp = {">",  ">=", "<",
                                                         "<=", "==", "!="};

  static inline std::unordered_set<std::string> binaryLogicalOp = {"&&", "||"};

  static inline std::unordered_set<std::string> unaryLogicalOp = {"!"};

  static inline std::unordered_set<std::string> logicalOp = {"&&", "||", "!"};

  static inline std::unordered_set<std::string> booleanOp = {
      ">", ">=", "<", "<=", "==", "!=", "&&", "||", "!"};

  static std::vector<std::string> eval(
      std::vector<Token> exprs,
      const std::shared_ptr<std::unordered_set<std::string>>& exprVar,
      const std::shared_ptr<std::unordered_set<std::string>>& exprCon,
      bool (*isValidOp)(std::string),
      void (*finalCheck)(int, const std::vector<std::string>&, bool&));

  static bool isValidMathOp(std::string value);

  static bool isValidCondOp(std::string value);

  static bool isRelOp(std::string value);

  static bool isBinaryLogicalOp(std::string value);

  static bool isUnaryLogicalOp(std::string value);

  static bool isLogicalOp(std::string value);

  static bool isBooleanOp(std::string value);

  static void finalCheckMath(int size, const std::vector<std::string>& postfix,
                             bool& mustBeLogical);

  static void finalCheckCond(int size, const std::vector<std::string>& postfix,
                             bool& mustBeLogical);

  static void processConOrVar(
      std::string expr, bool& isPrevOp, bool& isPrevLogical,
      std::vector<std::string>& postfix,
      const std::shared_ptr<std::unordered_set<std::string>>& exprCon,
      int& size);

  static void processOpOrBracket(std::string expr,
                                 std::stack<std::string>& opStack,
                                 bool& isPrevOp, bool& isPrevLogical,
                                 bool& mustBeLogical,
                                 std::vector<std::string>& postfix, int& size);

  static void processOp(std::stack<std::string>& opStack,
                        std::vector<std::string>& postfix, bool& mustBeLogical,
                        int& size);
};

}  // namespace Common
