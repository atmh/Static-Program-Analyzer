#include "catch.hpp"
#include "common/token/Token.h"
#include "sp/parser/SourceParser.h"

using namespace SP;

using Token = Common::Token;
using Type = Common::TokenType;

TEST_CASE("Valid parse read") {
  SECTION("one procedure one read") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("read", Type::name),
        Token("x", Type::name),         Token(";", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 1);

    std::shared_ptr<ReadNode> readNode =
        std::dynamic_pointer_cast<ReadNode>(stmtNodes[0]);
    REQUIRE(readNode != nullptr);
    REQUIRE(readNode->name == "x");
    REQUIRE(readNode->stmtNo == 1);
  }

  SECTION("one procedure two read") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("read", Type::name),
        Token("xyx", Type::name),       Token(";", Type::special),
        Token("read", Type::name),      Token("hi5", Type::name),
        Token(";", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 2);

    std::shared_ptr<ReadNode> readNode1 =
        std::dynamic_pointer_cast<ReadNode>(stmtNodes[0]);
    REQUIRE(readNode1 != nullptr);
    REQUIRE(readNode1->name == "xyx");
    REQUIRE(readNode1->stmtNo == 1);

    std::shared_ptr<ReadNode> readNode2 =
        std::dynamic_pointer_cast<ReadNode>(stmtNodes[1]);
    REQUIRE(readNode2 != nullptr);
    REQUIRE(readNode2->name == "hi5");
    REQUIRE(readNode2->stmtNo == 2);
  }

  SECTION("two procedure two read") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("read", Type::name),
        Token("xyx", Type::name),       Token(";", Type::special),
        Token("}", Type::special),      Token("procedure", Type::name),
        Token("second", Type::name),    Token("{", Type::special),
        Token("read", Type::name),      Token("hi5", Type::name),
        Token(";", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> procedureNodes =
        sourceParser.getRoot()->getChildren();

    std::vector<std::shared_ptr<Node>> stmtNodes1 =
        procedureNodes[0]->getChildren()[0]->getChildren();
    REQUIRE(stmtNodes1.size() == 1);

    std::shared_ptr<ReadNode> readNode1 =
        std::dynamic_pointer_cast<ReadNode>(stmtNodes1[0]);
    REQUIRE(readNode1 != nullptr);
    REQUIRE(readNode1->name == "xyx");
    REQUIRE(readNode1->stmtNo == 1);

    std::vector<std::shared_ptr<Node>> stmtNodes2 =
        procedureNodes[1]->getChildren()[0]->getChildren();
    REQUIRE(stmtNodes2.size() == 1);

    std::shared_ptr<ReadNode> readNode2 =
        std::dynamic_pointer_cast<ReadNode>(stmtNodes2[0]);
    REQUIRE(readNode2 != nullptr);
    REQUIRE(readNode2->name == "hi5");
    REQUIRE(readNode2->stmtNo == 2);
  }
}

TEST_CASE("Invalid parse read") {
  SECTION("missing read keyword") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token(";", Type::special),      Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("missing variable") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("read", Type::name),
        Token(";", Type::special),      Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("invalid read integer") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("read", Type::name),
        Token("123", Type::integer),    Token(";", Type::special),
        Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("invalid read special") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("read", Type::name),
        Token("*", Type::special),      Token(";", Type::special),
        Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("missing semicolon") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("read", Type::name),
        Token("x", Type::name),         Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }
}
