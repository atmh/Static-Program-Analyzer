#include "catch.hpp"
#include "common/algorithm/ShuntingYard.h"

using namespace Common;
using Type = Common::TokenType;

TEST_CASE("Valid conditional expression") {
  SECTION("simple conditional") {
    std::vector<Token> tokens{Token("a", Type::name), Token("<", Type::special),
                              Token("1", Type::integer)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_NOTHROW(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("simple math rel math") {
    std::vector<Token> tokens{
        Token("3", Type::integer), Token("/", Type::special),
        Token("xyz", Type::name),  Token(">=", Type::special),
        Token("1", Type::integer), Token("+", Type::special),
        Token("2", Type::integer)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_NOTHROW(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("simple math rel math with brackets") {
    std::vector<Token> tokens{
        Token("(", Type::special), Token("3", Type::integer),
        Token("/", Type::special), Token("xyz", Type::name),
        Token(")", Type::special), Token("!=", Type::special),
        Token("(", Type::special), Token("1", Type::integer),
        Token("+", Type::special), Token("2", Type::integer),
        Token(")", Type::special)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_NOTHROW(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("simple math rel math with double brackets") {
    std::vector<Token> tokens{
        Token("(", Type::special), Token("(", Type::special),
        Token("3", Type::integer), Token("/", Type::special),
        Token("xyz", Type::name),  Token(")", Type::special),
        Token(")", Type::special), Token("!=", Type::special),
        Token("(", Type::special), Token("(", Type::special),
        Token("1", Type::integer), Token("+", Type::special),
        Token("2", Type::integer), Token(")", Type::special),
        Token(")", Type::special)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_NOTHROW(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("simple math rel math with brackets on LHS only") {
    std::vector<Token> tokens{
        Token("(", Type::special), Token("3", Type::integer),
        Token("/", Type::special), Token("xyz", Type::name),
        Token(")", Type::special), Token("==", Type::special),
        Token("1", Type::integer), Token("+", Type::special),
        Token("2", Type::integer)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_NOTHROW(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("simple math rel math with brackets on RHS only") {
    std::vector<Token> tokens{
        Token("3", Type::integer), Token("/", Type::special),
        Token("xyz", Type::name),  Token("<", Type::special),
        Token("1", Type::integer), Token("+", Type::special),
        Token("2", Type::integer)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_NOTHROW(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("complex math rel math") {
    std::vector<Token> tokens{
        Token("a", Type::name),        Token("+", Type::special),
        Token("b", Type::name),        Token("*", Type::special),
        Token("10000", Type::integer), Token("*", Type::special),
        Token("40", Type::integer),    Token("/", Type::special),
        Token("(", Type::special),     Token("2", Type::integer),
        Token("+", Type::special),     Token("88", Type::integer),
        Token(")", Type::special),     Token("%", Type::special),
        Token("3", Type::integer),     Token("<", Type::special),
        Token("1", Type::integer),     Token("+", Type::special),
        Token("2", Type::integer)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_NOTHROW(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("exclamation complex math rel math") {
    std::vector<Token> tokens{
        Token("!", Type::special),     Token("(", Type::special),
        Token("a", Type::name),        Token("+", Type::special),
        Token("b", Type::name),        Token("*", Type::special),
        Token("10000", Type::integer), Token("*", Type::special),
        Token("40", Type::integer),    Token("/", Type::special),
        Token("(", Type::special),     Token("2", Type::integer),
        Token("+", Type::special),     Token("88", Type::integer),
        Token(")", Type::special),     Token("%", Type::special),
        Token("3", Type::integer),     Token(")", Type::special),
        Token("<", Type::special),     Token("1", Type::integer),
        Token("+", Type::special),     Token("2", Type::integer)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_NOTHROW(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("simple math rel math logical math rel math") {
    std::vector<Token> tokens{
        Token("(", Type::special),  Token("a", Type::name),
        Token("/", Type::special),  Token("b", Type::name),
        Token(">=", Type::special), Token("1", Type::integer),
        Token("+", Type::special),  Token("2", Type::integer),
        Token(")", Type::special),  Token("&&", Type::special),
        Token("(", Type::special),  Token("c", Type::name),
        Token("==", Type::special), Token("4", Type::integer),
        Token(")", Type::special),
    };
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_NOTHROW(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("complex rel math logical math rel math") {
    std::vector<Token> tokens{
        Token("(", Type::special),  Token("a", Type::name),
        Token("/", Type::special),  Token("b", Type::name),
        Token(">=", Type::special), Token("1", Type::integer),
        Token("+", Type::special),  Token("2", Type::integer),
        Token(")", Type::special),  Token("&&", Type::special),
        Token("(", Type::special),  Token("a", Type::name),
        Token("-", Type::special),  Token("b", Type::name),
        Token("==", Type::special), Token("4", Type::integer),
        Token("+", Type::special),  Token("10", Type::integer),
        Token(")", Type::special),
    };
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_NOTHROW(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("double logical") {
    // (( a > b ) || ( c == 4 )) && ( d < e )
    std::vector<Token> tokens{
        Token("(", Type::special),  Token("(", Type::special),
        Token("a", Type::name),     Token(">", Type::special),
        Token("b", Type::name),     Token(")", Type::special),
        Token("||", Type::special), Token("(", Type::special),
        Token("c", Type::name),     Token("==", Type::special),
        Token("4", Type::integer),  Token(")", Type::special),
        Token(")", Type::special),  Token("&&", Type::special),
        Token("(", Type::special),  Token("d", Type::name),
        Token("<", Type::special),  Token("e", Type::name),
        Token(")", Type::special)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_NOTHROW(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("exclamation ( logical )") {
    // !((a < b) || (c == 4))
    std::vector<Token> tokens{
        Token("!", Type::special),  Token("(", Type::special),
        Token("(", Type::special),  Token("a", Type::name),
        Token("<", Type::special),  Token("b", Type::name),
        Token(")", Type::special),  Token("||", Type::special),
        Token("(", Type::special),  Token("c", Type::name),
        Token("==", Type::special), Token("4", Type::integer),
        Token(")", Type::special),  Token(")", Type::special),
    };
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_NOTHROW(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("exclamation ( (logical) && (cond) )") {
    // !(  ((a < b) || (c == 4)) && (d != e)  )
    std::vector<Token> tokens{
        Token("!", Type::special),  Token("(", Type::special),
        Token("(", Type::special),  Token("(", Type::special),
        Token("a", Type::name),     Token("<", Type::special),
        Token("b", Type::name),     Token(")", Type::special),
        Token("||", Type::special), Token("(", Type::special),
        Token("c", Type::name),     Token("==", Type::special),
        Token("4", Type::integer),  Token(")", Type::special),
        Token(")", Type::special),  Token("&&", Type::special),
        Token("(", Type::special),  Token("d", Type::name),
        Token("!=", Type::special), Token("e", Type::name),
        Token(")", Type::special),  Token(")", Type::special),
    };
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_NOTHROW(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("exclamation ( (cond) || (logical) )") {
    // !(  (a < b) || ((c == 4) && (d != e))  )
    std::vector<Token> tokens{
        Token("!", Type::special),  Token("(", Type::special),
        Token("(", Type::special),  Token("a", Type::name),
        Token("<", Type::special),  Token("b", Type::name),
        Token(")", Type::special),  Token("||", Type::special),
        Token("(", Type::special),  Token("(", Type::special),
        Token("c", Type::name),     Token("==", Type::special),
        Token("4", Type::integer),  Token(")", Type::special),
        Token("&&", Type::special), Token("(", Type::special),
        Token("d", Type::name),     Token("!=", Type::special),
        Token("e", Type::name),     Token(")", Type::special),
        Token(")", Type::special),  Token(")", Type::special),
    };
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_NOTHROW(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("multiple exclamation") {
    std::vector<Token> tokens{
        Token("!", Type::special), Token("(", Type::special),
        Token("!", Type::special), Token("(", Type::special),
        Token("!", Type::special), Token("(", Type::special),
        Token("!", Type::special), Token("(", Type::special),
        Token("!", Type::special), Token("(", Type::special),
        Token("a", Type::name),    Token("<", Type::special),
        Token("1", Type::integer), Token(")", Type::special),
        Token(")", Type::special), Token(")", Type::special),
        Token(")", Type::special), Token(")", Type::special)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_NOTHROW(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("complex condtional") {
    // (!((xxx + 1) * yyy / (200000-3) % zzz < 1 + 2)) && (( a - b != 4 + 10 )
    // || (!(c/d >= 100000 + 0 )))
    std::vector<Token> tokens{
        Token("(", Type::special),      Token("!", Type::special),
        Token("(", Type::special),      Token("(", Type::special),
        Token("xxx", Type::name),       Token("+", Type::special),
        Token("1", Type::integer),      Token(")", Type::special),
        Token("*", Type::special),      Token("yyy", Type::name),
        Token("/", Type::special),      Token("(", Type::special),
        Token("200000", Type::integer), Token("-", Type::special),
        Token("3", Type::integer),      Token(")", Type::special),
        Token("%", Type::special),      Token("zzz", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token("+", Type::special),      Token("2", Type::integer),
        Token(")", Type::special),      Token(")", Type::special),
        Token("&&", Type::special),     Token("(", Type::special),
        Token("(", Type::special),      Token("a", Type::name),
        Token("-", Type::special),      Token("b", Type::name),
        Token("!=", Type::special),     Token("4", Type::integer),
        Token("+", Type::special),      Token("10", Type::integer),
        Token(")", Type::special),      Token("||", Type::special),
        Token("(", Type::special),      Token("!", Type::special),
        Token("(", Type::special),      Token("c", Type::name),
        Token("/", Type::special),      Token("d", Type::name),
        Token(">=", Type::special),     Token("100000", Type::integer),
        Token("+", Type::special),      Token("0", Type::integer),
        Token(")", Type::special),      Token(")", Type::special),
        Token(")", Type::special)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_NOTHROW(ShuntingYard::evalCond(tokens, var, con));
  }
}

TEST_CASE("Invalid conditonal expression") {
  SECTION("empty expression") {
    std::vector<Token> tokens{};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("single integer") {
    std::vector<Token> tokens{Token("1", Type::integer)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("integer + integer") {
    std::vector<Token> tokens{Token("1", Type::name), Token("+", Type::special),
                              Token("2", Type::integer)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("name + name") {
    std::vector<Token> tokens{Token("x", Type::name), Token("+", Type::special),
                              Token("y", Type::name)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("<") {
    std::vector<Token> tokens{Token("<", Type::special)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("< <") {
    std::vector<Token> tokens{Token("<", Type::special),
                              Token("<", Type::special)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("< && <") {
    std::vector<Token> tokens{Token("<", Type::special),
                              Token("&&", Type::special),
                              Token("<", Type::special)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("name ! integer") {
    std::vector<Token> tokens{Token("a", Type::name), Token("!", Type::special),
                              Token("1", Type::integer)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("conditional logical math") {
    std::vector<Token> tokens{
        Token("(", Type::special), Token("a", Type::name),
        Token("<", Type::special), Token("1", Type::integer),
        Token(")", Type::special), Token("&&", Type::special),
        Token("(", Type::special), Token("a", Type::name),
        Token("+", Type::special), Token("1", Type::integer),
        Token(")", Type::special)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("math logical conditional") {
    std::vector<Token> tokens{
        Token("(", Type::special), Token("a", Type::name),
        Token("+", Type::special), Token("1", Type::integer),
        Token(")", Type::special), Token("&&", Type::special),
        Token("(", Type::special), Token("a", Type::name),
        Token("<", Type::special), Token("1", Type::integer),
        Token(")", Type::special)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("math < < math") {
    std::vector<Token> tokens{
        Token("a", Type::name),
        Token("<", Type::special),
        Token("<", Type::special),
        Token("1", Type::integer),
    };
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("math > math >") {
    std::vector<Token> tokens{
        Token("a", Type::name),
        Token(">", Type::special),
        Token("1", Type::integer),
        Token(">", Type::special),
    };
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("> math > math") {
    std::vector<Token> tokens{
        Token(">", Type::special),
        Token("a", Type::name),
        Token(">", Type::special),
        Token("1", Type::integer),
    };
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("! math rel math without bracket") {
    std::vector<Token> tokens{
        Token("!", Type::special), Token("a", Type::name),
        Token("+", Type::special), Token("b", Type::name),
        Token("<", Type::special), Token("1", Type::integer),
        Token("+", Type::special), Token("2", Type::integer)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("math ! math") {
    std::vector<Token> tokens{
        Token("(", Type::special), Token("3", Type::name),
        Token("/", Type::special), Token("xyz", Type::name),
        Token(")", Type::special), Token("!", Type::special),
        Token("(", Type::special), Token("1", Type::integer),
        Token("+", Type::special), Token("2", Type::integer),
        Token(")", Type::special)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("rel within brackets") {
    std::vector<Token> tokens{
        Token("(", Type::special),  Token("3", Type::name),
        Token("/", Type::special),  Token("xyz", Type::name),
        Token("!=", Type::special), Token("1", Type::integer),
        Token("+", Type::special),  Token("2", Type::integer),
        Token(")", Type::special)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("rel mismatched brackets") {
    std::vector<Token> tokens{Token(")", Type::special), Token("a", Type::name),
                              Token("<", Type::special),
                              Token("1", Type::integer),
                              Token("(", Type::special)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("invalid logical token") {
    std::vector<Token> tokens{
        Token("(", Type::special), Token("a", Type::name),
        Token("<", Type::special), Token("b", Type::name),
        Token(")", Type::special), Token("^", Type::special),
        Token("(", Type::special), Token("c", Type::name),
        Token(">", Type::special), Token("d", Type::name),
        Token(")", Type::special),
    };
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("logical within bracket") {
    std::vector<Token> tokens{
        Token("(", Type::special),  Token("(", Type::special),
        Token("a", Type::name),     Token("<", Type::special),
        Token("b", Type::name),     Token(")", Type::special),
        Token("||", Type::special), Token("(", Type::special),
        Token("c", Type::name),     Token(">", Type::special),
        Token("d", Type::name),     Token(")", Type::special),
        Token(")", Type::special)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("math rel math logical math rel math without brackets") {
    std::vector<Token> tokens{
        Token("a", Type::name),     Token("+", Type::special),
        Token("b", Type::name),     Token(">=", Type::special),
        Token("1", Type::integer),  Token("+", Type::special),
        Token("2", Type::integer),  Token("&&", Type::special),
        Token("a", Type::name),     Token("-", Type::special),
        Token("b", Type::name),     Token("==", Type::special),
        Token("4", Type::integer),  Token("+", Type::special),
        Token("10", Type::integer),
    };
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("math rel math logical math rel math with only LHS bracket") {
    std::vector<Token> tokens{
        Token("(", Type::special),  Token("a", Type::name),
        Token("+", Type::special),  Token("b", Type::name),
        Token(">=", Type::special), Token("1", Type::integer),
        Token("+", Type::special),  Token("2", Type::integer),
        Token(")", Type::special),  Token("&&", Type::special),
        Token("a", Type::name),     Token("-", Type::special),
        Token("b", Type::name),     Token("==", Type::special),
        Token("4", Type::integer),  Token("+", Type::special),
        Token("10", Type::integer)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("math rel math logical math rel math with only RHS bracket") {
    std::vector<Token> tokens{
        Token("a", Type::name),     Token("+", Type::special),
        Token("b", Type::name),     Token(">=", Type::special),
        Token("1", Type::integer),  Token("+", Type::special),
        Token("2", Type::integer),  Token("&&", Type::special),
        Token("(", Type::special),  Token("a", Type::name),
        Token("-", Type::special),  Token("b", Type::name),
        Token("==", Type::special), Token("4", Type::integer),
        Token("+", Type::special),  Token("10", Type::integer),
        Token(")", Type::special)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("invalid double logical") {
    std::vector<Token> tokens{
        Token("(", Type::special),  Token("a", Type::name),
        Token("/", Type::special),  Token("b", Type::name),
        Token(">=", Type::special), Token("1", Type::integer),
        Token("+", Type::special),  Token("2", Type::integer),
        Token(")", Type::special),  Token("&&", Type::special),
        Token("(", Type::special),  Token("||", Type::special),
        Token(")", Type::special),
    };
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("double logical exclamation missing bracket") {
    std::vector<Token> tokens{
        Token("(", Type::special),  Token("a", Type::name),
        Token("/", Type::special),  Token("b", Type::name),
        Token("<=", Type::special), Token("1", Type::integer),
        Token("+", Type::special),  Token("2", Type::integer),
        Token(")", Type::special),  Token("||", Type::special),
        Token("(", Type::special),  Token("c", Type::name),
        Token("==", Type::special), Token("4", Type::integer),
        Token(")", Type::special),  Token("&&", Type::special),
        Token("!", Type::special),  Token("(", Type::special),
        Token("a", Type::name),     Token("/", Type::special),
        Token("b", Type::name),     Token("<", Type::special),
        Token("1", Type::integer),  Token("+", Type::special),
        Token("2", Type::integer),  Token(")", Type::special),
    };
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("exclamation logical missing bracket") {
    // !(a < b) || (c == 4)
    std::vector<Token> tokens{
        Token("!", Type::special),  Token("(", Type::special),
        Token("a", Type::name),     Token("<", Type::special),
        Token("b", Type::name),     Token(")", Type::special),
        Token("||", Type::special), Token("(", Type::special),
        Token("c", Type::name),     Token("==", Type::special),
        Token("4", Type::integer),  Token(")", Type::special)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("double logical missing brackets") {
    // ( a > b ) || ( c == 4 ) && ( d < e )
    std::vector<Token> tokens{
        Token("(", Type::special),  Token("a", Type::name),
        Token(">", Type::special),  Token("b", Type::name),
        Token(")", Type::special),  Token("||", Type::special),
        Token("(", Type::special),  Token("c", Type::name),
        Token("==", Type::special), Token("4", Type::integer),
        Token(")", Type::special),  Token("&&", Type::special),
        Token("(", Type::special),  Token("d", Type::name),
        Token("<", Type::special),  Token("e", Type::name),
        Token(")", Type::special)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("exclamation ( double logical ) missing bracket") {
    // !(  (a < b) || (c == 4) && (d != e)  )
    std::vector<Token> tokens{
        Token("!", Type::special),  Token("(", Type::special),
        Token("(", Type::special),  Token("a", Type::name),
        Token("<", Type::special),  Token("b", Type::name),
        Token(")", Type::special),  Token("||", Type::special),
        Token("(", Type::special),  Token("c", Type::name),
        Token("==", Type::special), Token("4", Type::integer),
        Token(")", Type::special),  Token("&&", Type::special),
        Token("(", Type::special),  Token("d", Type::name),
        Token("!=", Type::special), Token("e", Type::name),
        Token(")", Type::special),  Token(")", Type::special),
    };
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("multiple exclamation extra outer bracket") {
    std::vector<Token> tokens{
        Token("(", Type::special), Token("!", Type::special),
        Token("(", Type::special), Token("!", Type::special),
        Token("(", Type::special), Token("!", Type::special),
        Token("(", Type::special), Token("!", Type::special),
        Token("(", Type::special), Token("!", Type::special),
        Token("(", Type::special), Token("a", Type::name),
        Token("<", Type::special), Token("1", Type::integer),
        Token(")", Type::special), Token(")", Type::special),
        Token(")", Type::special), Token(")", Type::special),
        Token(")", Type::special), Token(")", Type::special)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("multiple exclamation missing bracket") {
    std::vector<Token> tokens{
        Token("!", Type::special), Token("!", Type::special),
        Token("(", Type::special), Token("a", Type::name),
        Token("<", Type::special), Token("1", Type::integer),
        Token(")", Type::special)};
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }

  SECTION("complex condtional missing bracket") {
    // ! ((xxx + 1) * yyy / (200000-3) % zzz < 1 + 2) && ( a - b != 4 + 10 ) ||
    // (!(c/d >= 100000 + 0 ))
    std::vector<Token> tokens{
        Token("!", Type::special),      Token("(", Type::special),
        Token("(", Type::special),      Token("xxx", Type::name),
        Token("+", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("*", Type::special),
        Token("yyy", Type::name),       Token("/", Type::special),
        Token("(", Type::special),      Token("200000", Type::integer),
        Token("-", Type::special),      Token("3", Type::integer),
        Token(")", Type::special),      Token("%", Type::special),
        Token("zzz", Type::name),       Token("<", Type::special),
        Token("1", Type::integer),      Token("+", Type::special),
        Token("2", Type::integer),      Token(")", Type::special),
        Token("&&", Type::special),     Token("(", Type::special),
        Token("a", Type::name),         Token("-", Type::special),
        Token("b", Type::name),         Token("!=", Type::special),
        Token("4", Type::integer),      Token("+", Type::special),
        Token("10", Type::integer),     Token(")", Type::special),
        Token("||", Type::special),     Token("(", Type::special),
        Token("!", Type::special),      Token("(", Type::special),
        Token("c", Type::name),         Token("/", Type::special),
        Token("d", Type::name),         Token(">=", Type::special),
        Token("100000", Type::integer), Token("+", Type::special),
        Token("0", Type::integer),      Token(")", Type::special),
        Token(")", Type::special),
    };
    std::shared_ptr<std::unordered_set<std::string>> var =
        std::make_shared<std::unordered_set<std::string>>();
    std::shared_ptr<std::unordered_set<std::string>> con =
        std::make_shared<std::unordered_set<std::string>>();

    REQUIRE_THROWS(ShuntingYard::evalCond(tokens, var, con));
  }
}
