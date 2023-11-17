#include "catch.hpp"
#include "common/token/Token.h"
#include "sp/parser/SourceParser.h"

using namespace SP;

using Token = Common::Token;
using Type = Common::TokenType;

TEST_CASE("Valid parse stmt list") {
  SECTION("one valid stmt list") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> procedureNodes =
        sourceParser.getRoot()->getChildren();
    REQUIRE(procedureNodes.size() == 1);

    std::vector<std::shared_ptr<Node>> stmtLstNode =
        procedureNodes[0]->getChildren();
    REQUIRE(stmtLstNode.size() == 1);

    std::shared_ptr<StmtLstNode> stmtLst =
        std::dynamic_pointer_cast<StmtLstNode>(stmtLstNode[0]);
    REQUIRE(stmtLst != nullptr);

    std::vector<std::shared_ptr<Node>> stmtNodes =
        stmtLstNode[0]->getChildren();
    REQUIRE(stmtNodes.size() == 1);
  }

  SECTION("two valid stmt list") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("read", Type::name),
        Token("x", Type::name),         Token(";", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> procedureNodes =
        sourceParser.getRoot()->getChildren();
    REQUIRE(procedureNodes.size() == 1);

    std::vector<std::shared_ptr<Node>> stmtLstNode =
        procedureNodes[0]->getChildren();
    REQUIRE(stmtLstNode.size() == 1);

    std::shared_ptr<StmtLstNode> stmtLst =
        std::dynamic_pointer_cast<StmtLstNode>(stmtLstNode[0]);
    REQUIRE(stmtLst != nullptr);

    std::vector<std::shared_ptr<Node>> stmtNodes =
        stmtLstNode[0]->getChildren();
    REQUIRE(stmtNodes.size() == 2);
  }
}

TEST_CASE("Invalid parse stmt list") {
  SECTION("no stmt list start") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc", Type::name),
        Token("x", Type::name),         Token("=", Type::special),
        Token("1", Type::integer),      Token(";", Type::special),
        Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("no stmt list end") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("invalid integer starting token") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc", Type::name),
        Token("{", Type::special),      Token("123", Type::integer),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("invalid special procedure name") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc", Type::name),
        Token("{", Type::special),      Token("special", Type::special),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("invalid entity") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc", Type::name),
        Token("{", Type::special),      Token("hello", Type::name),
        Token("x", Type::name),         Token(";", Type::special),
        Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("missing semicolon") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("empty stmt list") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc", Type::name),
        Token("{", Type::special), Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }
}
