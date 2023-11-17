#include "ShuntingYard.h"

namespace Common {

constexpr auto OPEN_BRACKET = "(";
constexpr auto CLOSED_BRACKET = ")";
constexpr auto EXCL = "!";

std::vector<std::string> ShuntingYard::eval(
    std::vector<Token> exprs,
    const std::shared_ptr<std::unordered_set<std::string>>& exprVar,
    const std::shared_ptr<std::unordered_set<std::string>>& exprCon,
    bool (*isValidOp)(std::string),
    void (*finalCheck)(int, const std::vector<std::string>&, bool&)) {
  bool isPrevOp = true;

  // for logical operator, LHS and RHS must be bracketed
  bool isPrevLogical = false;

  // if relation operator is within bracket, next must be logical operator
  bool mustBeLogical = false;

  std::vector<std::string> postfix;
  std::stack<std::string> opStack;
  int size = 0;

  for (const auto& expr : exprs) {
    if (expr.getType() == TokenType::integer) {
      processConOrVar(expr.getValue(), isPrevOp, isPrevLogical, postfix,
                      exprCon, size);
    } else if (expr.getType() == TokenType::name) {
      processConOrVar(expr.getValue(), isPrevOp, isPrevLogical, postfix,
                      exprVar, size);
    } else if (expr.getType() == TokenType::special &&
               isValidOp(expr.getValue())) {
      processOpOrBracket(expr.getValue(), opStack, isPrevOp, isPrevLogical,
                         mustBeLogical, postfix, size);
    } else {
      throw ShuntingYardException(SHUNTING_YARD_INVALID_EXPR_OP);
    }
  }

  while (!opStack.empty()) {
    processOp(opStack, postfix, mustBeLogical, size);
  }

  finalCheck(size, postfix, mustBeLogical);

  return postfix;
}

void ShuntingYard::processConOrVar(
    std::string expr, bool& isPrevOp, bool& isPrevLogical,
    std::vector<std::string>& postfix,
    const std::shared_ptr<std::unordered_set<std::string>>& exprSet,
    int& size) {
  if (!isPrevOp || isPrevLogical)
    throw ShuntingYardException(SHUNTING_YARD_INVALID_EXPR);
  postfix.emplace_back(expr);
  size++;
  exprSet->insert(expr);
  isPrevOp = false;
}

void ShuntingYard::processOpOrBracket(std::string expr,
                                      std::stack<std::string>& opStack,
                                      bool& isPrevOp, bool& isPrevLogical,
                                      bool& mustBeLogical,
                                      std::vector<std::string>& postfix,
                                      int& size) {
  if (expr == OPEN_BRACKET) {
    opStack.push(expr);
  } else if (expr == CLOSED_BRACKET) {
    bool haveLogical = false;
    while (!opStack.empty() && opStack.top() != OPEN_BRACKET) {
      std::string top = opStack.top();
      if (isLogicalOp(top)) {
        haveLogical = true;
      }
      processOp(opStack, postfix, mustBeLogical, size);
      if (isRelOp(top)) {
        mustBeLogical = true;
      }
    }
    if (opStack.empty())
      throw ShuntingYardException(SHUNTING_YARD_INVALID_EXPR);

    opStack.pop();
    if (haveLogical && (opStack.empty() || !isLogicalOp(opStack.top()))) {
      mustBeLogical = true;
    }
  } else {
    if (isBinaryLogicalOp(expr)) {
      mustBeLogical = false;
      if (size < 1 || !isBooleanOp(postfix[postfix.size() - 1]))
        throw ShuntingYardException(SHUNTING_YARD_INVALID_EXPR);
    } else {
      if (mustBeLogical)
        throw ShuntingYardException(SHUNTING_YARD_INVALID_EXPR);
    }
    if (isLogicalOp(expr) && !opStack.empty() && isLogicalOp(opStack.top()))
      throw ShuntingYardException(SHUNTING_YARD_INVALID_EXPR);

    while (!opStack.empty() && rank[opStack.top()] >= rank[expr]) {
      processOp(opStack, postfix, mustBeLogical, size);
    }
    opStack.push(expr);
  }
  if (isLogicalOp(expr)) {
    isPrevLogical = true;
  } else {
    isPrevLogical = false;
  }
  isPrevOp = true;
}

void ShuntingYard::processOp(std::stack<std::string>& opStack,
                             std::vector<std::string>& postfix,
                             bool& mustBeLogical, int& size) {
  if (isUnaryLogicalOp(opStack.top())) {
    if (size < 1 || !isBooleanOp(postfix[postfix.size() - 1]))
      throw ShuntingYardException(SHUNTING_YARD_INVALID_EXPR);
    postfix.emplace_back(opStack.top());
    opStack.pop();
    mustBeLogical = false;
    return;
  }
  if (size < 2)
    throw ShuntingYardException(SHUNTING_YARD_INVALID_EXPR);
  if (isBinaryLogicalOp(opStack.top())) {
    mustBeLogical = false;
    if (!isBooleanOp(postfix[postfix.size() - 1]))
      throw ShuntingYardException(SHUNTING_YARD_INVALID_EXPR);
  }

  if (isRelOp(opStack.top()) && isRelOp(postfix[postfix.size() - 1]))
    throw ShuntingYardException(SHUNTING_YARD_INVALID_EXPR);

  postfix.emplace_back(opStack.top());
  opStack.pop();
  size--;
}

bool ShuntingYard::isValidMathOp(std::string value) {
  return mathOp.find(value) != mathOp.end();
}

bool ShuntingYard::isValidCondOp(std::string value) {
  return condOp.find(value) != condOp.end();
}

bool ShuntingYard::isRelOp(std::string value) {
  return relOp.find(value) != relOp.end();
}

bool ShuntingYard::isBinaryLogicalOp(std::string value) {
  return binaryLogicalOp.find(value) != binaryLogicalOp.end();
}

bool ShuntingYard::isUnaryLogicalOp(std::string value) {
  return unaryLogicalOp.find(value) != unaryLogicalOp.end();
}

bool ShuntingYard::isLogicalOp(std::string value) {
  return logicalOp.find(value) != logicalOp.end();
}

bool ShuntingYard::isBooleanOp(std::string value) {
  return booleanOp.find(value) != booleanOp.end();
}

void ShuntingYard::finalCheckMath(int size, const std::vector<std::string>&,
                                  bool&) {
  if (size != 1) {
    throw ShuntingYardException(SHUNTING_YARD_INVALID_EXPR);
  }
}

void ShuntingYard::finalCheckCond(int size,
                                  const std::vector<std::string>& postfix,
                                  bool& mustBeLogical) {
  // last operation must be boolean operator
  if (size != 1 || !isBooleanOp(postfix[postfix.size() - 1]) || mustBeLogical) {
    throw ShuntingYardException(SHUNTING_YARD_INVALID_EXPR);
  }
}

std::vector<std::string> ShuntingYard::evalMath(
    std::vector<Token> exprs,
    const std::shared_ptr<std::unordered_set<std::string>>& exprVar,
    const std::shared_ptr<std::unordered_set<std::string>>& exprCon) {
  return eval(exprs, exprVar, exprCon, ShuntingYard::isValidMathOp,
              ShuntingYard::finalCheckMath);
}

std::vector<std::string> ShuntingYard::evalMath(std::vector<Token> exprs) {
  std::shared_ptr<std::unordered_set<std::string>> var =
      std::make_shared<std::unordered_set<std::string>>();
  std::shared_ptr<std::unordered_set<std::string>> con =
      std::make_shared<std::unordered_set<std::string>>();
  return evalMath(exprs, var, con);
}

void ShuntingYard::evalCond(
    std::vector<Token> exprs,
    const std::shared_ptr<std::unordered_set<std::string>>& exprVar,
    const std::shared_ptr<std::unordered_set<std::string>>& exprCon) {
  eval(exprs, exprVar, exprCon, ShuntingYard::isValidCondOp,
       ShuntingYard::finalCheckCond);
}

}  // namespace Common
