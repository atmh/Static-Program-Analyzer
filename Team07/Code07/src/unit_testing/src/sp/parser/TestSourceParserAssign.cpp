#include "catch.hpp"
#include "common/token/Token.h"
#include "sp/parser/SourceParser.h"

using namespace SP;

using Token = Common::Token;
using Type = Common::TokenType;

TEST_CASE("Valid parse assign") {
  SECTION("one procedure one simple assign") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 1);

    std::shared_ptr<AssignNode> assignNode =
        std::dynamic_pointer_cast<AssignNode>(stmtNodes[0]);
    REQUIRE(assignNode != nullptr);
    REQUIRE(assignNode->name == "x");
    REQUIRE(assignNode->stmtNo == 1);
    REQUIRE(assignNode->exprVar.size() == 0);
    REQUIRE(assignNode->exprCon.size() == 1);
    REQUIRE(assignNode->exprCon.find("1") != assignNode->exprCon.end());
  }

  SECTION("one procedure one simple keyword assign") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("read", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 1);

    std::shared_ptr<AssignNode> assignNode =
        std::dynamic_pointer_cast<AssignNode>(stmtNodes[0]);
    REQUIRE(assignNode != nullptr);
    REQUIRE(assignNode->name == "read");
    REQUIRE(assignNode->stmtNo == 1);
    REQUIRE(assignNode->exprVar.size() == 0);
    REQUIRE(assignNode->exprCon.size() == 1);
    REQUIRE(assignNode->exprCon.find("1") != assignNode->exprCon.end());
  }

  SECTION("one procedure two simple assign") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("y", Type::name),
        Token("=", Type::special),      Token("z", Type::name),
        Token(";", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 2);

    std::shared_ptr<AssignNode> assignNode1 =
        std::dynamic_pointer_cast<AssignNode>(stmtNodes[0]);
    REQUIRE(assignNode1 != nullptr);
    REQUIRE(assignNode1->name == "x");
    REQUIRE(assignNode1->stmtNo == 1);
    REQUIRE(assignNode1->exprVar.size() == 0);
    REQUIRE(assignNode1->exprCon.size() == 1);
    REQUIRE(assignNode1->exprCon.find("1") != assignNode1->exprCon.end());

    std::shared_ptr<AssignNode> assignNode2 =
        std::dynamic_pointer_cast<AssignNode>(stmtNodes[1]);
    REQUIRE(assignNode2 != nullptr);
    REQUIRE(assignNode2->name == "y");
    REQUIRE(assignNode2->stmtNo == 2);
    REQUIRE(assignNode2->exprVar.size() == 1);
    REQUIRE(assignNode2->exprVar.find("z") != assignNode2->exprVar.end());
    REQUIRE(assignNode2->exprCon.size() == 0);
  }

  SECTION("two procedure two simple assign") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special),
        Token("procedure", Type::name), Token("b", Type::name),
        Token("{", Type::special),      Token("y", Type::name),
        Token("=", Type::special),      Token("z", Type::name),
        Token(";", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> procedureNodes =
        sourceParser.getRoot()->getChildren();

    std::vector<std::shared_ptr<Node>> stmtNodes1 =
        procedureNodes[0]->getChildren()[0]->getChildren();
    REQUIRE(stmtNodes1.size() == 1);

    std::shared_ptr<AssignNode> assignNode1 =
        std::dynamic_pointer_cast<AssignNode>(stmtNodes1[0]);
    REQUIRE(assignNode1 != nullptr);
    REQUIRE(assignNode1->name == "x");
    REQUIRE(assignNode1->stmtNo == 1);
    REQUIRE(assignNode1->exprVar.size() == 0);
    REQUIRE(assignNode1->exprCon.size() == 1);
    REQUIRE(assignNode1->exprCon.find("1") != assignNode1->exprCon.end());

    std::vector<std::shared_ptr<Node>> stmtNodes2 =
        procedureNodes[1]->getChildren()[0]->getChildren();
    REQUIRE(stmtNodes2.size() == 1);

    std::shared_ptr<AssignNode> assignNode2 =
        std::dynamic_pointer_cast<AssignNode>(stmtNodes2[0]);
    REQUIRE(assignNode2 != nullptr);
    REQUIRE(assignNode2->name == "y");
    REQUIRE(assignNode2->stmtNo == 2);
    REQUIRE(assignNode2->exprVar.size() == 1);
    REQUIRE(assignNode2->exprVar.find("z") != assignNode2->exprVar.end());
    REQUIRE(assignNode2->exprCon.size() == 0);
  }

  SECTION("one procedure one complex assign") {
    // hi = (xxx + 1) * yyy / (200000 - 3) % zzz
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("hi", Type::name),
        Token("=", Type::special),      Token("(", Type::special),
        Token("xxx", Type::name),       Token("+", Type::special),
        Token("1", Type::integer),      Token(")", Type::special),
        Token("*", Type::special),      Token("yyy", Type::name),
        Token("/", Type::special),      Token("(", Type::special),
        Token("200000", Type::integer), Token("-", Type::special),
        Token("3", Type::integer),      Token(")", Type::special),
        Token("%", Type::special),      Token("zzz", Type::name),
        Token(";", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 1);

    std::shared_ptr<AssignNode> assignNode =
        std::dynamic_pointer_cast<AssignNode>(stmtNodes[0]);
    REQUIRE(assignNode != nullptr);
    REQUIRE(assignNode->name == "hi");
    REQUIRE(assignNode->stmtNo == 1);
    REQUIRE(assignNode->exprVar.size() == 3);
    REQUIRE(assignNode->exprVar.find("xxx") != assignNode->exprVar.end());
    REQUIRE(assignNode->exprVar.find("yyy") != assignNode->exprVar.end());
    REQUIRE(assignNode->exprVar.find("zzz") != assignNode->exprVar.end());
    REQUIRE(assignNode->exprCon.size() == 3);
    REQUIRE(assignNode->exprCon.find("1") != assignNode->exprCon.end());
    REQUIRE(assignNode->exprCon.find("200000") != assignNode->exprCon.end());
    REQUIRE(assignNode->exprCon.find("3") != assignNode->exprCon.end());
  }
}

TEST_CASE("Invalid parse assign") {
  SECTION("empty RHS") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token(";", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("missing variable name on LHS") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("=", Type::special),
        Token("1", Type::integer),      Token(";", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("missing op") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("1", Type::integer),      Token(";", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("missing semicolon") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("invalid expr") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("*", Type::special),
        Token(";", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }
}
