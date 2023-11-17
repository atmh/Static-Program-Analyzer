#include "catch.hpp"
#include "common/token/Token.h"
#include "sp/parser/SourceParser.h"

using namespace SP;

using Token = Common::Token;
using Type = Common::TokenType;

TEST_CASE("Valid parse procedure") {
  SECTION("one valid procedure") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> children =
        sourceParser.getRoot()->getChildren();
    REQUIRE(children.size() == 1);

    std::shared_ptr<ProcedureNode> child =
        std::dynamic_pointer_cast<ProcedureNode>(children[0]);
    REQUIRE(child != nullptr);
    REQUIRE(child->name == "abc");
  }

  SECTION("two valid procedure") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special),
        Token("procedure", Type::name), Token("efghikjlmnop", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> children =
        sourceParser.getRoot()->getChildren();
    REQUIRE(children.size() == 2);

    std::shared_ptr<ProcedureNode> child1 =
        std::dynamic_pointer_cast<ProcedureNode>(children[0]);
    REQUIRE(child1 != nullptr);
    REQUIRE(child1->name == "abc");

    std::shared_ptr<ProcedureNode> child2 =
        std::dynamic_pointer_cast<ProcedureNode>(children[1]);
    REQUIRE(child2 != nullptr);
    REQUIRE(child2->name == "efghikjlmnop");
  }
}

TEST_CASE("Invalid parse procedure") {
  SECTION("no procedure keyword") {
    std::vector<Token> tokens{
        Token("abc", Type::name),  Token("{", Type::special),
        Token("x", Type::name),    Token("=", Type::special),
        Token("1", Type::integer), Token(";", Type::special),
        Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("no procedure name") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("{", Type::special),
        Token("x", Type::name),         Token("=", Type::special),
        Token("1", Type::integer),      Token(";", Type::special),
        Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("invalid integer procedure name") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("123", Type::integer),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("invalid special procedure name") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("%", Type::special),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("no opening curly bracket") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc", Type::name),
        Token("x", Type::name),         Token("=", Type::special),
        Token("1", Type::integer),      Token(";", Type::special),
        Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("no closing curly bracket") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),
    };
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("empty body") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc", Type::name),
        Token("{", Type::special), Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }
}
