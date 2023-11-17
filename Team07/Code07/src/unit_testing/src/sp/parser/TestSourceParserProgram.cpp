#include "catch.hpp"
#include "common/token/Token.h"
#include "sp/parser/SourceParser.h"

using namespace SP;

using Token = Common::Token;
using Type = Common::TokenType;

TEST_CASE("Valid parse program") {
  SECTION("valid program") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special)};
    REQUIRE_NOTHROW(SourceParser(tokens));
  }
}

TEST_CASE("Invalid parse program") {
  SECTION("empty tokens") {
    std::vector<Common::Token> tokens;
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("non procedure") {
    std::vector<Common::Token> tokens{
        Token("x", Type::name),
        Token("=", Type::special),
        Token("1", Type::integer),
        Token(";", Type::special),
    };
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("valid procedure followed by non procedure") {
    std::vector<Common::Token> tokens{
        Token("procedure", Type::name), Token("abc", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special),
        Token("x", Type::name),         Token("=", Type::special),
        Token("1", Type::integer),      Token(";", Type::special),
    };
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }
}
