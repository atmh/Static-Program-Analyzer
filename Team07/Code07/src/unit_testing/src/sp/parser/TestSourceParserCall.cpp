#include "catch.hpp"
#include "common/token/Token.h"
#include "sp/parser/SourceParser.h"

using namespace SP;

using Token = Common::Token;
using Type = Common::TokenType;

TEST_CASE("Valid parse call") {
  /* Semantic check will be done in design extractor */
  SECTION("one procedure one call") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("call", Type::name),
        Token("x", Type::name),         Token(";", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 1);

    std::shared_ptr<CallNode> callNode =
        std::dynamic_pointer_cast<CallNode>(stmtNodes[0]);
    REQUIRE(callNode != nullptr);
    REQUIRE(callNode->name == "x");
    REQUIRE(callNode->stmtNo == 1);
  }

  SECTION("one procedure two call") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("call", Type::name),
        Token("xyx", Type::name),       Token(";", Type::special),
        Token("call", Type::name),      Token("hi5", Type::name),
        Token(";", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 2);

    std::shared_ptr<CallNode> callNode1 =
        std::dynamic_pointer_cast<CallNode>(stmtNodes[0]);
    REQUIRE(callNode1 != nullptr);
    REQUIRE(callNode1->name == "xyx");
    REQUIRE(callNode1->stmtNo == 1);

    std::shared_ptr<CallNode> callNode2 =
        std::dynamic_pointer_cast<CallNode>(stmtNodes[1]);
    REQUIRE(callNode2 != nullptr);
    REQUIRE(callNode2->name == "hi5");
    REQUIRE(callNode2->stmtNo == 2);
  }

  SECTION("two procedure two call") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("call", Type::name),
        Token("xyx", Type::name),       Token(";", Type::special),
        Token("}", Type::special),      Token("procedure", Type::name),
        Token("second", Type::name),    Token("{", Type::special),
        Token("call", Type::name),      Token("hi5", Type::name),
        Token(";", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> procedureNodes =
        sourceParser.getRoot()->getChildren();

    std::vector<std::shared_ptr<Node>> stmtNodes1 =
        procedureNodes[0]->getChildren()[0]->getChildren();
    REQUIRE(stmtNodes1.size() == 1);

    std::shared_ptr<CallNode> callNode1 =
        std::dynamic_pointer_cast<CallNode>(stmtNodes1[0]);
    REQUIRE(callNode1 != nullptr);
    REQUIRE(callNode1->name == "xyx");
    REQUIRE(callNode1->stmtNo == 1);

    std::vector<std::shared_ptr<Node>> stmtNodes2 =
        procedureNodes[1]->getChildren()[0]->getChildren();
    REQUIRE(stmtNodes2.size() == 1);

    std::shared_ptr<CallNode> callNode2 =
        std::dynamic_pointer_cast<CallNode>(stmtNodes2[0]);
    REQUIRE(callNode2 != nullptr);
    REQUIRE(callNode2->name == "hi5");
    REQUIRE(callNode2->stmtNo == 2);
  }
}

TEST_CASE("Invalid parse call") {
  SECTION("missing call keyword") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token(";", Type::special),      Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("missing variable") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("call", Type::name),
        Token(";", Type::special),      Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("invalid call integer") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("call", Type::name),
        Token("123", Type::integer),    Token(";", Type::special),
        Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("invalid call special") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("call", Type::name),
        Token("*", Type::special),      Token(";", Type::special),
        Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }

  SECTION("missing semicolon") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("abc123", Type::name),
        Token("{", Type::special),      Token("call", Type::name),
        Token("x", Type::name),         Token("}", Type::special)};
    REQUIRE_THROWS(SourceParser(tokens).parse());
  }
}
