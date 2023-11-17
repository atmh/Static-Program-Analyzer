#include "Parser.h"

using namespace Common;

Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {}

Token Parser::peek() {
  return tokens[index];
}

Token Parser::get() {
  return tokens[index++];
}

bool Parser::hasNext() {
  return index < tokens.size();
}

bool Parser::isCurrentType(TokenType type) {
  if (!hasNext()) {
    throw ParserException(PARSER_SYNTAX_ERROR);
  }

  return peek().getType() == type;
}

bool Parser::isCurrentValue(const std::string& value) {
  if (!hasNext()) {
    throw ParserException(PARSER_SYNTAX_ERROR);
  }

  return peek().getValue() == value;
}

Token Parser::parseToken(TokenType type) {
  if (!isCurrentType(type)) {
    throw ParserException(PARSER_SYNTAX_ERROR);
  }
  return get();
}

Token Parser::parseToken(const std::string& value) {
  if (!isCurrentValue(value)) {
    throw ParserException(PARSER_SYNTAX_ERROR);
  }
  return get();
}
