#include "catch.hpp"
#include "common/token/Token.h"
#include "sp/parser/SourceParser.h"

using namespace SP;

using Token = Common::Token;
using Type = Common::TokenType;

TEST_CASE("Valid parse print") {
  SECTION("one procedure one print") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("print", Type::name),
        Token("x", Type::name),         Token(";", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 1);

    std::shared_ptr<PrintNode> printNode =
        std::dynamic_pointer_cast<PrintNode>(stmtNodes[0]);
    REQUIRE(printNode != nullptr);
    REQUIRE(printNode->name == "x");
    REQUIRE(printNode->stmtNo == 1);
  }

  SECTION("one procedure two print") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("print", Type::name),
        Token("xyx", Type::name),       Token(";", Type::special),
        Token("print", Type::name),     Token("hi5", Type::name),
        Token(";", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 2);

    std::shared_ptr<PrintNode> printNode1 =
        std::dynamic_pointer_cast<PrintNode>(stmtNodes[0]);
    REQUIRE(printNode1 != nullptr);
    REQUIRE(printNode1->name == "xyx");
    REQUIRE(printNode1->stmtNo == 1);

    std::shared_ptr<PrintNode> printNode2 =
        std::dynamic_pointer_cast<PrintNode>(stmtNodes[1]);
    REQUIRE(printNode2 != nullptr);
    REQUIRE(printNode2->name == "hi5");
    REQUIRE(printNode2->stmtNo == 2);
  }

  SECTION("two procedure two print") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("print", Type::name),
        Token("xyx", Type::name),       Token(";", Type::special),
        Token("}", Type::special),      Token("procedure", Type::name),
        Token("second", Type::name),    Token("{", Type::special),
        Token("print", Type::name),     Token("hi5", Type::name),
        Token(";", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> procedureNodes =
        sourceParser.getRoot()->getChildren();

    std::vector<std::shared_ptr<Node>> stmtNodes1 =
        procedureNodes[0]->getChildren()[0]->getChildren();
    REQUIRE(stmtNodes1.size() == 1);

    std::shared_ptr<PrintNode> printNode1 =
        std::dynamic_pointer_cast<PrintNode>(stmtNodes1[0]);
    REQUIRE(printNode1 != nullptr);
    REQUIRE(printNode1->name == "xyx");
    REQUIRE(printNode1->stmtNo == 1);

    std::vector<std::shared_ptr<Node>> stmtNodes2 =
        procedureNodes[1]->getChildren()[0]->getChildren();
    REQUIRE(stmtNodes2.size() == 1);

    std::shared_ptr<PrintNode> printNode2 =
        std::dynamic_pointer_cast<PrintNode>(stmtNodes2[0]);
    REQUIRE(printNode2 != nullptr);
    REQUIRE(printNode2->name == "hi5");
    REQUIRE(printNode2->stmtNo == 2);
  }
}

TEST_CASE("Invalid parse print") {
  SECTION("missing print keyword") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token(";", Type::special),      Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("missing variable") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("print", Type::name),
        Token(";", Type::special),      Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("invalid print integer") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("print", Type::name),
        Token("123", Type::integer),    Token(";", Type::special),
        Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("invalid print special") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("print", Type::name),
        Token("*", Type::special),      Token(";", Type::special),
        Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("missing semicolon") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("print", Type::name),
        Token("x", Type::name),         Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }
}
