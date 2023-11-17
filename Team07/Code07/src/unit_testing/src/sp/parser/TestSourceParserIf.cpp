#include "catch.hpp"
#include "common/token/Token.h"
#include "sp/parser/SourceParser.h"

using namespace SP;

using Token = Common::Token;
using Type = Common::TokenType;

TEST_CASE("Valid parse if") {
  SECTION("one procedure one simple if") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("if", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("then", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special),
        Token("else", Type::name),      Token("{", Type::special),
        Token("read", Type::name),      Token("x", Type::name),
        Token(";", Type::special),      Token("}", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 1);

    std::shared_ptr<IfNode> ifNode =
        std::dynamic_pointer_cast<IfNode>(stmtNodes[0]);
    REQUIRE(ifNode != nullptr);
    REQUIRE(ifNode->stmtNo == 1);

    std::unordered_set<std::string> expectedVar{"x"};
    std::unordered_set<std::string> expectedCon{"1"};

    REQUIRE(ifNode->exprVar.size() == 1);
    REQUIRE(ifNode->exprVar == expectedVar);
    REQUIRE(ifNode->exprCon.size() == 1);
    REQUIRE(ifNode->exprCon == expectedCon);

    REQUIRE(ifNode->getChildren().size() == 2);
  }

  SECTION("one procedure two nested if then if") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("if", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("then", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),

        Token("if", Type::name),        Token("(", Type::special),
        Token("y", Type::name),         Token("<", Type::special),
        Token("x", Type::integer),      Token(")", Type::special),
        Token("then", Type::name),      Token("{", Type::special),
        Token("x", Type::name),         Token("=", Type::special),
        Token("1", Type::integer),      Token(";", Type::special),
        Token("}", Type::special),      Token("else", Type::name),
        Token("{", Type::special),      Token("read", Type::name),
        Token("x", Type::name),         Token(";", Type::special),
        Token("}", Type::special),

        Token("}", Type::special),      Token("else", Type::name),
        Token("{", Type::special),      Token("read", Type::name),
        Token("x", Type::name),         Token(";", Type::special),
        Token("}", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 1);

    std::shared_ptr<IfNode> ifNode1 =
        std::dynamic_pointer_cast<IfNode>(stmtNodes[0]);
    REQUIRE(ifNode1 != nullptr);
    REQUIRE(ifNode1->stmtNo == 1);

    std::unordered_set<std::string> expectedVar1{"x"};
    std::unordered_set<std::string> expectedCon1{"1"};

    REQUIRE(ifNode1->exprVar.size() == 1);
    REQUIRE(ifNode1->exprVar == expectedVar1);
    REQUIRE(ifNode1->exprCon.size() == 1);
    REQUIRE(ifNode1->exprCon == expectedCon1);

    std::vector<std::shared_ptr<Node>> ifNode1Children = ifNode1->getChildren();

    REQUIRE(ifNode1Children.size() == 2);
    REQUIRE(ifNode1Children[0]->getChildren().size() == 2);

    std::shared_ptr<IfNode> ifNode2 =
        std::dynamic_pointer_cast<IfNode>(ifNode1Children[0]->getChildren()[1]);
    REQUIRE(ifNode2 != nullptr);
    REQUIRE(ifNode2->stmtNo == 3);

    std::unordered_set<std::string> expectedVar2{"y"};
    std::unordered_set<std::string> expectedCon2{"x"};

    REQUIRE(ifNode2->exprVar.size() == 1);
    REQUIRE(ifNode2->exprVar == expectedVar2);
    REQUIRE(ifNode2->exprCon.size() == 1);
    REQUIRE(ifNode2->exprCon == expectedCon2);

    REQUIRE(ifNode2->getChildren().size() == 2);
  }

  SECTION("one procedure two nested if else if") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("if", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("then", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("read", Type::name),
        Token("y", Type::name),         Token(";", Type::special),
        Token("}", Type::special),      Token("else", Type::name),
        Token("{", Type::special),

        Token("if", Type::name),        Token("(", Type::special),
        Token("y", Type::name),         Token("<", Type::special),
        Token("x", Type::integer),      Token(")", Type::special),
        Token("then", Type::name),      Token("{", Type::special),
        Token("x", Type::name),         Token("=", Type::special),
        Token("1", Type::integer),      Token(";", Type::special),
        Token("}", Type::special),      Token("else", Type::name),
        Token("{", Type::special),      Token("read", Type::name),
        Token("x", Type::name),         Token(";", Type::special),
        Token("}", Type::special),

        Token("}", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 1);

    std::shared_ptr<IfNode> ifNode1 =
        std::dynamic_pointer_cast<IfNode>(stmtNodes[0]);
    REQUIRE(ifNode1 != nullptr);
    REQUIRE(ifNode1->stmtNo == 1);

    std::unordered_set<std::string> expectedVar1{"x"};
    std::unordered_set<std::string> expectedCon1{"1"};

    REQUIRE(ifNode1->exprVar.size() == 1);
    REQUIRE(ifNode1->exprVar == expectedVar1);
    REQUIRE(ifNode1->exprCon.size() == 1);
    REQUIRE(ifNode1->exprCon == expectedCon1);

    std::vector<std::shared_ptr<Node>> ifNode1Children = ifNode1->getChildren();

    REQUIRE(ifNode1Children.size() == 2);
    REQUIRE(ifNode1Children[1]->getChildren().size() == 1);

    std::shared_ptr<IfNode> ifNode2 =
        std::dynamic_pointer_cast<IfNode>(ifNode1Children[1]->getChildren()[0]);
    REQUIRE(ifNode2 != nullptr);
    REQUIRE(ifNode2->stmtNo == 4);

    std::unordered_set<std::string> expectedVar2{"y"};
    std::unordered_set<std::string> expectedCon2{"x"};

    REQUIRE(ifNode2->exprVar.size() == 1);
    REQUIRE(ifNode2->exprVar == expectedVar2);
    REQUIRE(ifNode2->exprCon.size() == 1);
    REQUIRE(ifNode2->exprCon == expectedCon2);

    REQUIRE(ifNode2->getChildren().size() == 2);
  }

  SECTION("two procedure two simple while") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("if", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("then", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special),
        Token("else", Type::name),      Token("{", Type::special),
        Token("read", Type::name),      Token("x", Type::name),
        Token(";", Type::special),      Token("}", Type::special),
        Token("}", Type::special),

        Token("procedure", Type::name), Token("xyz", Type::name),
        Token("{", Type::special),      Token("if", Type::name),
        Token("(", Type::special),      Token("yy", Type::name),
        Token("==", Type::special),     Token("zz", Type::name),
        Token(")", Type::special),      Token("then", Type::name),
        Token("{", Type::special),      Token("xx", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special),
        Token("else", Type::name),      Token("{", Type::special),
        Token("print", Type::name),     Token("x", Type::name),
        Token(";", Type::special),      Token("}", Type::special),
        Token("}", Type::special),
    };

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> procedureNodes =
        sourceParser.getRoot()->getChildren();

    std::vector<std::shared_ptr<Node>> stmtNodes1 =
        procedureNodes[0]->getChildren()[0]->getChildren();
    REQUIRE(stmtNodes1.size() == 1);

    std::shared_ptr<IfNode> ifNode1 =
        std::dynamic_pointer_cast<IfNode>(stmtNodes1[0]);
    REQUIRE(ifNode1 != nullptr);
    REQUIRE(ifNode1->stmtNo == 1);

    std::unordered_set<std::string> expectedVar1{"x"};
    std::unordered_set<std::string> expectedCon1{"1"};

    REQUIRE(ifNode1->exprVar.size() == 1);
    REQUIRE(ifNode1->exprVar == expectedVar1);
    REQUIRE(ifNode1->exprCon.size() == 1);
    REQUIRE(ifNode1->exprCon == expectedCon1);

    REQUIRE(ifNode1->getChildren().size() == 2);

    std::vector<std::shared_ptr<Node>> stmtNodes2 =
        procedureNodes[1]->getChildren()[0]->getChildren();
    REQUIRE(stmtNodes2.size() == 1);

    std::shared_ptr<IfNode> IfNode2 =
        std::dynamic_pointer_cast<IfNode>(stmtNodes2[0]);
    REQUIRE(IfNode2 != nullptr);
    REQUIRE(IfNode2->stmtNo == 4);

    std::unordered_set<std::string> expectedVar{"yy", "zz"};

    REQUIRE(IfNode2->exprVar.size() == 2);
    REQUIRE(IfNode2->exprVar == expectedVar);
    REQUIRE(IfNode2->exprCon.size() == 0);

    REQUIRE(IfNode2->getChildren().size() == 2);
  }

  SECTION("one procedure one complex if 1") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("if", Type::name),
        Token("(", Type::special),

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
        Token(")", Type::special),

        Token(")", Type::special),      Token("then", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special),
        Token("else", Type::name),      Token("{", Type::special),
        Token("read", Type::name),      Token("x", Type::name),
        Token(";", Type::special),      Token("}", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 1);

    std::shared_ptr<IfNode> ifNode =
        std::dynamic_pointer_cast<IfNode>(stmtNodes[0]);
    REQUIRE(ifNode != nullptr);
    REQUIRE(ifNode->stmtNo == 1);

    std::unordered_set<std::string> expectedVar{"xxx", "yyy", "zzz", "a",
                                                "b",   "c",   "d"};

    std::unordered_set<std::string> expectedCon{"1", "200000", "3",      "2",
                                                "4", "10",     "100000", "0"};

    REQUIRE(ifNode->exprVar.size() == 7);
    REQUIRE(ifNode->exprVar == expectedVar);

    REQUIRE(ifNode->exprCon.size() == 8);
    REQUIRE(ifNode->exprCon == expectedCon);

    REQUIRE(ifNode->getChildren().size() == 2);
  }

  SECTION("one procedure one complex if 2") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("if", Type::name),
        Token("(", Type::special),

        Token("!", Type::special),      Token("(", Type::special),
        Token("(", Type::special),      Token("then", Type::name),
        Token("<", Type::special),      Token("else", Type::name),
        Token(")", Type::special),      Token("||", Type::special),
        Token("(", Type::special),      Token("(", Type::special),
        Token("while", Type::name),     Token("==", Type::special),
        Token("read", Type::name),      Token(")", Type::special),
        Token("&&", Type::special),     Token("(", Type::special),
        Token("call", Type::name),      Token("!=", Type::special),
        Token("if", Type::name),        Token(")", Type::special),
        Token(")", Type::special),      Token(")", Type::special),

        Token(")", Type::special),      Token("then", Type::name),
        Token("{", Type::special),      Token("print", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special),
        Token("else", Type::name),      Token("{", Type::special),
        Token("read", Type::name),      Token("call", Type::name),
        Token(";", Type::special),      Token("}", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 1);

    std::shared_ptr<IfNode> ifNode =
        std::dynamic_pointer_cast<IfNode>(stmtNodes[0]);
    REQUIRE(ifNode != nullptr);
    REQUIRE(ifNode->stmtNo == 1);

    std::unordered_set<std::string> expectedVar{"then", "else", "while",
                                                "read", "call", "if"};

    REQUIRE(ifNode->exprVar.size() == 6);
    REQUIRE(ifNode->exprVar == expectedVar);

    REQUIRE(ifNode->exprCon.size() == 0);
    REQUIRE(ifNode->getChildren().size() == 2);
  }

  SECTION("one procedure one complex if 3") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("if", Type::name),
        Token("(", Type::special),

        Token("!", Type::special),      Token("(", Type::special),
        Token("(", Type::special),      Token("(", Type::special),
        Token("read", Type::name),      Token("<", Type::special),
        Token("print", Type::name),     Token(")", Type::special),
        Token("||", Type::special),     Token("(", Type::special),
        Token("call", Type::name),      Token("==", Type::special),
        Token("while", Type::name),     Token(")", Type::special),
        Token(")", Type::special),      Token("&&", Type::special),
        Token("(", Type::special),      Token("then", Type::name),
        Token("!=", Type::special),     Token("then", Type::name),
        Token(")", Type::special),      Token(")", Type::special),

        Token(")", Type::special),      Token("then", Type::name),
        Token("{", Type::special),      Token("print", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special),
        Token("else", Type::name),      Token("{", Type::special),
        Token("read", Type::name),      Token("call", Type::name),
        Token(";", Type::special),      Token("}", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 1);

    std::shared_ptr<IfNode> ifNode =
        std::dynamic_pointer_cast<IfNode>(stmtNodes[0]);
    REQUIRE(ifNode != nullptr);
    REQUIRE(ifNode->stmtNo == 1);

    std::unordered_set<std::string> expectedVar{"read", "print", "call",
                                                "while", "then"};

    REQUIRE(ifNode->exprVar.size() == 5);
    REQUIRE(ifNode->exprVar == expectedVar);

    REQUIRE(ifNode->exprCon.size() == 0);
    REQUIRE(ifNode->getChildren().size() == 2);
  }
}

TEST_CASE("Invalid parse if") {
  SECTION("missing if") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("(", Type::special),
        Token("x", Type::name),         Token("<", Type::special),
        Token("1", Type::integer),      Token(")", Type::special),
        Token("then", Type::name),      Token("{", Type::special),
        Token("x", Type::name),         Token("=", Type::special),
        Token("1", Type::integer),      Token(";", Type::special),
        Token("}", Type::special),      Token("else", Type::name),
        Token("{", Type::special),      Token("read", Type::name),
        Token("x", Type::name),         Token(";", Type::special),
        Token("}", Type::special),

        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("missing then") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("if", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("{", Type::special),
        Token("x", Type::name),         Token("=", Type::special),
        Token("1", Type::integer),      Token(";", Type::special),
        Token("}", Type::special),      Token("else", Type::name),
        Token("{", Type::special),      Token("read", Type::name),
        Token("x", Type::name),         Token(";", Type::special),
        Token("}", Type::special),

        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("missing else") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("if", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("then", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special),
        Token("{", Type::special),      Token("read", Type::name),
        Token("x", Type::name),         Token(";", Type::special),
        Token("}", Type::special),

        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("missing condition") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("if", Type::name),
        Token("then", Type::name),      Token("{", Type::special),
        Token("x", Type::name),         Token("=", Type::special),
        Token("1", Type::integer),      Token(";", Type::special),
        Token("}", Type::special),      Token("else", Type::name),
        Token("{", Type::special),      Token("read", Type::name),
        Token("x", Type::name),         Token(";", Type::special),
        Token("}", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("empty condition") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("if", Type::name),
        Token("(", Type::special),      Token(")", Type::special),
        Token("then", Type::name),      Token("{", Type::special),
        Token("x", Type::name),         Token("=", Type::special),
        Token("1", Type::integer),      Token(";", Type::special),
        Token("}", Type::special),      Token("else", Type::name),
        Token("{", Type::special),      Token("read", Type::name),
        Token("x", Type::name),         Token(";", Type::special),
        Token("}", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("missing then open curly bracket") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("if", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("then", Type::name),
        Token("x", Type::name),         Token("=", Type::special),
        Token("1", Type::integer),      Token(";", Type::special),
        Token("}", Type::special),      Token("else", Type::name),
        Token("{", Type::special),      Token("read", Type::name),
        Token("x", Type::name),         Token(";", Type::special),
        Token("}", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("missing then closing curly bracket") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("if", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("then", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("else", Type::name),
        Token("{", Type::special),      Token("read", Type::name),
        Token("x", Type::name),         Token(";", Type::special),
        Token("}", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("missing else open curly bracket") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("if", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("then", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special),
        Token("else", Type::name),      Token("read", Type::name),
        Token("x", Type::name),         Token(";", Type::special),
        Token("}", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("missing else closing curly bracket") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("if", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("then", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special),
        Token("else", Type::name),      Token("{", Type::special),
        Token("read", Type::name),      Token("x", Type::name),
        Token(";", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("missing then body") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("if", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("then", Type::name),
        Token("else", Type::name),      Token("{", Type::special),
        Token("read", Type::name),      Token("x", Type::name),
        Token(";", Type::special),      Token("}", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("empty then body") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("if", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("then", Type::name),
        Token("{", Type::special),      Token("}", Type::special),
        Token("else", Type::name),      Token("{", Type::special),
        Token("read", Type::name),      Token("x", Type::name),
        Token(";", Type::special),      Token("}", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("extra closing curly bracket") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("if", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("then", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special),
        Token("else", Type::name),      Token("{", Type::special),
        Token("read", Type::name),      Token("x", Type::name),
        Token(";", Type::special),      Token("}", Type::special),
        Token("}", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("missing closing bracket for conditional") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("if", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token("then", Type::name),      Token("{", Type::special),
        Token("x", Type::name),         Token("=", Type::special),
        Token("1", Type::integer),      Token(";", Type::special),
        Token("}", Type::special),      Token("else", Type::name),
        Token("{", Type::special),      Token("read", Type::name),
        Token("x", Type::name),         Token(";", Type::special),
        Token("}", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }
}
