#include "catch.hpp"
#include "common/algorithm/ShuntingYard.h"

using namespace Common;
using Type = Common::TokenType;

TEST_CASE("Valid expression") {
  SECTION("single integer") {
    std::vector<Token> tokens{Token("1", Type::integer)};

    std::vector<std::string> postfix;
    REQUIRE_NOTHROW([&]() {
      postfix = ShuntingYard::evalMath(tokens);
    }());

    std::vector<std::string> expected{"1"};
    REQUIRE(postfix == expected);
  }

  SECTION("single name") {
    std::vector<Token> tokens{Token("hi", Type::name)};

    std::vector<std::string> postfix;
    REQUIRE_NOTHROW([&]() {
      postfix = ShuntingYard::evalMath(tokens);
    }());

    std::vector<std::string> expected{"hi"};
    REQUIRE(postfix == expected);
  }

  SECTION("name + integer") {
    std::vector<Token> tokens{Token("x", Type::name), Token("+", Type::special),
                              Token("1", Type::integer)};

    std::vector<std::string> postfix;
    REQUIRE_NOTHROW([&]() {
      postfix = ShuntingYard::evalMath(tokens);
    }());

    std::vector<std::string> expected{"x", "1", "+"};
    REQUIRE(postfix == expected);
  }

  SECTION("name + name") {
    std::vector<Token> tokens{Token("x", Type::name), Token("+", Type::special),
                              Token("y", Type::name)};

    std::vector<std::string> postfix;
    REQUIRE_NOTHROW([&]() {
      postfix = ShuntingYard::evalMath(tokens);
    }());

    std::vector<std::string> expected{"x", "y", "+"};
    REQUIRE(postfix == expected);
  }

  SECTION("integer + integer") {
    std::vector<Token> tokens{Token("1", Type::integer),
                              Token("+", Type::special),
                              Token("2", Type::integer)};

    std::vector<std::string> postfix;
    REQUIRE_NOTHROW([&]() {
      postfix = ShuntingYard::evalMath(tokens);
    }());

    std::vector<std::string> expected{"1", "2", "+"};
    REQUIRE(postfix == expected);
  }

  SECTION("simple bracket") {
    std::vector<Token> tokens{
        Token("(", Type::special), Token("xyz", Type::name),
        Token("+", Type::special), Token("123", Type::integer),
        Token(")", Type::special),
    };

    std::vector<std::string> postfix;
    REQUIRE_NOTHROW([&]() {
      postfix = ShuntingYard::evalMath(tokens);
    }());

    std::vector<std::string> expected{"xyz", "123", "+"};
    REQUIRE(postfix == expected);
  }

  SECTION("complex expression 1") {
    std::vector<Token> tokens{
        Token("(", Type::special), Token("xxx", Type::name),
        Token("+", Type::special), Token("1", Type::integer),
        Token(")", Type::special), Token("*", Type::special),
        Token("yyy", Type::name),  Token("/", Type::special),
        Token("(", Type::special), Token("200000", Type::integer),
        Token("-", Type::special), Token("3", Type::integer),
        Token(")", Type::special), Token("%", Type::special),
        Token("zzz", Type::name),
    };

    std::vector<std::string> postfix;
    REQUIRE_NOTHROW([&]() {
      postfix = ShuntingYard::evalMath(tokens);
    }());

    std::vector<std::string> expected{"xxx", "1", "+", "yyy", "*", "200000",
                                      "3",   "-", "/", "zzz", "%"};
    REQUIRE(postfix == expected);
  }

  SECTION("complex expression 2") {
    std::vector<Token> tokens{
        Token("a", Type::name),    Token("+", Type::special),
        Token("b", Type::name),    Token("*", Type::special),
        Token("c", Type::name),    Token("*", Type::special),
        Token("d", Type::name),    Token("+", Type::special),
        Token("(", Type::special), Token("e", Type::name),
        Token("-", Type::special), Token("8", Type::integer),
        Token(")", Type::special), Token("*", Type::special),
        Token("(", Type::special), Token("g", Type::name),
        Token("*", Type::special), Token("h", Type::name),
        Token("+", Type::special), Token("i", Type::name),
        Token(")", Type::special)};

    std::vector<std::string> postfix;
    REQUIRE_NOTHROW([&]() {
      postfix = ShuntingYard::evalMath(tokens);
    }());

    std::vector<std::string> expected{"a", "b", "c", "*", "d", "*",
                                      "+", "e", "8", "-", "g", "h",
                                      "*", "i", "+", "*", "+"};
    REQUIRE(postfix == expected);
  }

  SECTION("complex expression 3") {
    std::vector<Token> tokens{
        Token("(", Type::special), Token("(", Type::special),
        Token("(", Type::special), Token("a", Type::name),
        Token("+", Type::special), Token("b", Type::name),
        Token(")", Type::special), Token("*", Type::special),
        Token("c", Type::name),    Token(")", Type::special),
        Token("-", Type::special), Token("(", Type::special),
        Token("(", Type::special), Token("d", Type::name),
        Token("-", Type::special), Token("e", Type::name),
        Token(")", Type::special), Token("*", Type::special),
        Token("(", Type::special), Token("f", Type::name),
        Token("+", Type::special), Token("123456", Type::integer),
        Token(")", Type::special), Token(")", Type::special),
        Token(")", Type::special)};

    std::vector<std::string> postfix;
    REQUIRE_NOTHROW([&]() {
      postfix = ShuntingYard::evalMath(tokens);
    }());

    std::vector<std::string> expected{"a", "b", "+",      "c", "*", "d", "e",
                                      "-", "f", "123456", "+", "*", "-"};
    REQUIRE(postfix == expected);
  }
}

TEST_CASE("Invalid expression") {
  SECTION("empty expression") {
    std::vector<Token> tokens{};
    REQUIRE_THROWS(ShuntingYard::evalMath(tokens));
  }

  SECTION("only single op") {
    std::vector<Token> tokens{Token("+", Type::special)};
    REQUIRE_THROWS(ShuntingYard::evalMath(tokens));
  }

  SECTION("only multiple op") {
    std::vector<Token> tokens{Token("+", Type::special),
                              Token("*", Type::special),
                              Token("/", Type::special)};
    REQUIRE_THROWS(ShuntingYard::evalMath(tokens));
  }

  SECTION("only value") {
    std::vector<Token> tokens{Token("1", Type::integer), Token("a", Type::name),
                              Token("2", Type::integer)};
    REQUIRE_THROWS(ShuntingYard::evalMath(tokens));
  }

  SECTION("invalid op") {
    std::vector<Token> tokens{Token("x", Type::name), Token("<", Type::special),
                              Token("1", Type::integer)};
    REQUIRE_THROWS(ShuntingYard::evalMath(tokens));
  }

  SECTION("missing third value") {
    std::vector<Token> tokens{Token("x", Type::name), Token("+", Type::special),
                              Token("1", Type::integer),
                              Token("+", Type::special)};
    REQUIRE_THROWS(ShuntingYard::evalMath(tokens));
  }

  SECTION("missing RHS") {
    std::vector<Token> tokens{
        Token("x", Type::name),
        Token("+", Type::special),
    };
    REQUIRE_THROWS(ShuntingYard::evalMath(tokens));
  }

  SECTION("missing LHS") {
    std::vector<Token> tokens{Token("<", Type::special),
                              Token("1", Type::integer)};
    REQUIRE_THROWS(ShuntingYard::evalMath(tokens));
  }

  SECTION("missing open bracket") {
    std::vector<Token> tokens{
        Token("x", Type::name),
        Token("+", Type::special),
        Token("1", Type::integer),
        Token(")", Type::special),
    };
    REQUIRE_THROWS(ShuntingYard::evalMath(tokens));
  }

  SECTION("missing closing bracket") {
    std::vector<Token> tokens{
        Token("(", Type::special),
        Token("x", Type::name),
        Token("+", Type::special),
        Token("1", Type::integer),
    };
    REQUIRE_THROWS(ShuntingYard::evalMath(tokens));
  }

  SECTION("mismatched bracket") {
    std::vector<Token> tokens{
        Token("(", Type::special), Token("x", Type::name),
        Token("+", Type::special), Token(")", Type::special),
        Token("1", Type::integer),
    };
    REQUIRE_THROWS(ShuntingYard::evalMath(tokens));
  }
}
