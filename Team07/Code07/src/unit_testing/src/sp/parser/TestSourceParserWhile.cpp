#include "catch.hpp"
#include "common/token/Token.h"
#include "sp/parser/SourceParser.h"

using namespace SP;

using Token = Common::Token;
using Type = Common::TokenType;

TEST_CASE("Valid parse while") {
  SECTION("one procedure one simple while") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("while", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("{", Type::special),
        Token("x", Type::name),         Token("=", Type::special),
        Token("1", Type::integer),      Token(";", Type::special),
        Token("}", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 1);

    std::shared_ptr<WhileNode> whileNode =
        std::dynamic_pointer_cast<WhileNode>(stmtNodes[0]);
    REQUIRE(whileNode != nullptr);
    REQUIRE(whileNode->stmtNo == 1);

    std::unordered_set<std::string> expectedVar{"x"};
    std::unordered_set<std::string> expectedCon{"1"};

    REQUIRE(whileNode->exprVar.size() == 1);
    REQUIRE(whileNode->exprVar == expectedVar);
    REQUIRE(whileNode->exprCon.size() == 1);
    REQUIRE(whileNode->exprCon == expectedCon);

    REQUIRE(whileNode->getChildren().size() == 1);
  }

  SECTION("one procedure two nested while") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("while", Type::name),
        Token("(", Type::special),      Token("y", Type::name),
        Token("!=", Type::special),     Token("p", Type::name),
        Token(")", Type::special),      Token("{", Type::special),
        Token("while", Type::name),     Token("(", Type::special),
        Token("z", Type::name),         Token(">=", Type::special),
        Token("123456", Type::integer), Token(")", Type::special),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special),
        Token("}", Type::special),      Token("print", Type::name),
        Token("x", Type::name),         Token(";", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 2);

    std::shared_ptr<WhileNode> whileNode1 =
        std::dynamic_pointer_cast<WhileNode>(stmtNodes[0]);
    REQUIRE(whileNode1 != nullptr);
    REQUIRE(whileNode1->stmtNo == 1);

    std::unordered_set<std::string> expectedVar1{"y", "p"};

    REQUIRE(whileNode1->exprVar.size() == 2);
    REQUIRE(whileNode1->exprVar == expectedVar1);
    REQUIRE(whileNode1->exprCon.size() == 0);

    std::vector<std::shared_ptr<Node>> whileNode1Children =
        whileNode1->getChildren();

    REQUIRE(whileNode1Children.size() == 1);
    REQUIRE(whileNode1Children[0]->getChildren().size() == 1);

    std::shared_ptr<WhileNode> whileNode2 =
        std::dynamic_pointer_cast<WhileNode>(
            whileNode1Children[0]->getChildren()[0]);
    REQUIRE(whileNode2 != nullptr);
    REQUIRE(whileNode2->stmtNo == 2);

    std::unordered_set<std::string> expectedVar2{"z"};
    std::unordered_set<std::string> expectedCon2{"123456"};

    REQUIRE(whileNode2->exprVar.size() == 1);
    REQUIRE(whileNode2->exprVar == expectedVar2);
    REQUIRE(whileNode2->exprCon.size() == 1);
    REQUIRE(whileNode2->exprCon == expectedCon2);

    REQUIRE(whileNode2->getChildren().size() == 1);
  }

  SECTION("two procedure two simple while") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("while", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("{", Type::special),
        Token("x", Type::name),         Token("=", Type::special),
        Token("1", Type::integer),      Token(";", Type::special),
        Token("}", Type::special),      Token("}", Type::special),

        Token("procedure", Type::name), Token("xyz", Type::name),
        Token("{", Type::special),      Token("while", Type::name),
        Token("(", Type::special),      Token("yy", Type::name),
        Token("!=", Type::special),     Token("zz", Type::name),
        Token(")", Type::special),      Token("{", Type::special),
        Token("read", Type::name),      Token("x", Type::name),
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

    std::shared_ptr<WhileNode> whileNode1 =
        std::dynamic_pointer_cast<WhileNode>(stmtNodes1[0]);
    REQUIRE(whileNode1 != nullptr);
    REQUIRE(whileNode1->stmtNo == 1);

    std::unordered_set<std::string> expectedVar1{"x"};
    std::unordered_set<std::string> expectedCon1{"1"};

    REQUIRE(whileNode1->exprVar.size() == 1);
    REQUIRE(whileNode1->exprVar == expectedVar1);
    REQUIRE(whileNode1->exprCon.size() == 1);
    REQUIRE(whileNode1->exprCon == expectedCon1);

    REQUIRE(whileNode1->getChildren().size() == 1);

    std::vector<std::shared_ptr<Node>> stmtNodes2 =
        procedureNodes[1]->getChildren()[0]->getChildren();
    REQUIRE(stmtNodes2.size() == 1);

    std::shared_ptr<WhileNode> whileNode2 =
        std::dynamic_pointer_cast<WhileNode>(stmtNodes2[0]);
    REQUIRE(whileNode2 != nullptr);
    REQUIRE(whileNode2->stmtNo == 3);

    std::unordered_set<std::string> expectedVar{"yy", "zz"};

    REQUIRE(whileNode2->exprVar.size() == 2);
    REQUIRE(whileNode2->exprVar == expectedVar);
    REQUIRE(whileNode2->exprCon.size() == 0);

    REQUIRE(whileNode2->getChildren().size() == 1);
  }

  SECTION("one procedure one complex while 1") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("while", Type::name),
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

        Token(")", Type::special),      Token("{", Type::special),
        Token("x", Type::name),         Token("=", Type::special),
        Token("1", Type::integer),      Token(";", Type::special),
        Token("print", Type::name),     Token("x", Type::name),
        Token(";", Type::special),      Token("call", Type::name),
        Token("y", Type::name),         Token(";", Type::special),
        Token("read", Type::name),      Token("xyz", Type::name),
        Token(";", Type::special),      Token("}", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 1);

    std::shared_ptr<WhileNode> whileNode =
        std::dynamic_pointer_cast<WhileNode>(stmtNodes[0]);
    REQUIRE(whileNode != nullptr);
    REQUIRE(whileNode->stmtNo == 1);

    std::unordered_set<std::string> expectedVar{"xxx", "yyy", "zzz", "a",
                                                "b",   "c",   "d"};

    std::unordered_set<std::string> expectedCon{"1", "200000", "3",      "2",
                                                "4", "10",     "100000", "0"};

    REQUIRE(whileNode->exprVar.size() == 7);
    REQUIRE(whileNode->exprVar == expectedVar);

    REQUIRE(whileNode->exprCon.size() == 8);
    REQUIRE(whileNode->exprCon == expectedCon);

    REQUIRE(whileNode->getChildren().size() == 1);
  }

  SECTION("one procedure one complex while 2") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("while", Type::name),
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

        Token(")", Type::special),      Token("{", Type::special),
        Token("x", Type::name),         Token("=", Type::special),
        Token("1", Type::integer),      Token(";", Type::special),
        Token("print", Type::name),     Token("x", Type::name),
        Token(";", Type::special),      Token("call", Type::name),
        Token("y", Type::name),         Token(";", Type::special),
        Token("read", Type::name),      Token("xyz", Type::name),
        Token(";", Type::special),      Token("}", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 1);

    std::shared_ptr<WhileNode> whileNode =
        std::dynamic_pointer_cast<WhileNode>(stmtNodes[0]);
    REQUIRE(whileNode != nullptr);
    REQUIRE(whileNode->stmtNo == 1);

    std::unordered_set<std::string> expectedVar{"then", "else", "while",
                                                "read", "call", "if"};

    REQUIRE(whileNode->exprVar.size() == 6);
    REQUIRE(whileNode->exprVar == expectedVar);

    REQUIRE(whileNode->exprCon.size() == 0);
    REQUIRE(whileNode->getChildren().size() == 1);
  }

  SECTION("one procedure one complex while 3") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("while", Type::name),
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

        Token(")", Type::special),      Token("{", Type::special),
        Token("x", Type::name),         Token("=", Type::special),
        Token("1", Type::integer),      Token(";", Type::special),
        Token("print", Type::name),     Token("x", Type::name),
        Token(";", Type::special),      Token("call", Type::name),
        Token("y", Type::name),         Token(";", Type::special),
        Token("read", Type::name),      Token("xyz", Type::name),
        Token(";", Type::special),      Token("}", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_NOTHROW(sourceParser.parse());

    std::vector<std::shared_ptr<Node>> stmtNodes = sourceParser.getRoot()
                                                       ->getChildren()[0]
                                                       ->getChildren()[0]
                                                       ->getChildren();
    REQUIRE(stmtNodes.size() == 1);

    std::shared_ptr<WhileNode> whileNode =
        std::dynamic_pointer_cast<WhileNode>(stmtNodes[0]);
    REQUIRE(whileNode != nullptr);
    REQUIRE(whileNode->stmtNo == 1);

    std::unordered_set<std::string> expectedVar{"read", "print", "call",
                                                "while", "then"};

    REQUIRE(whileNode->exprVar.size() == 5);
    REQUIRE(whileNode->exprVar == expectedVar);

    REQUIRE(whileNode->exprCon.size() == 0);
    REQUIRE(whileNode->getChildren().size() == 1);
  }
}

TEST_CASE("Invalid parse while") {
  SECTION("missing while") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("(", Type::special),
        Token("x", Type::name),         Token("<", Type::special),
        Token("1", Type::integer),      Token(")", Type::special),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("missing condition") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("while", Type::name),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("empty condition") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("while", Type::name),
        Token("(", Type::special),      Token(")", Type::special),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("missing open curly bracket") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("while", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("missing closing curly bracket") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("while", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("{", Type::special),
        Token("x", Type::name),         Token("=", Type::special),
        Token("1", Type::integer),      Token(";", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("missing while body") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("while", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("empty while body") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("while", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("{", Type::special),

        Token("}", Type::special),      Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("extra closing curly bracket") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("while", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token(")", Type::special),      Token("{", Type::special),
        Token("x", Type::name),         Token("=", Type::special),
        Token("1", Type::integer),      Token(";", Type::special),
        Token("}", Type::special),      Token("}", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }

  SECTION("missing closing bracket for conditional") {
    std::vector<Token> tokens{
        Token("procedure", Type::name), Token("a", Type::name),
        Token("{", Type::special),      Token("while", Type::name),
        Token("(", Type::special),      Token("x", Type::name),
        Token("<", Type::special),      Token("1", Type::integer),
        Token("{", Type::special),      Token("x", Type::name),
        Token("=", Type::special),      Token("1", Type::integer),
        Token(";", Type::special),      Token("}", Type::special),
        Token("}", Type::special)};

    SourceParser sourceParser = SourceParser(tokens);
    REQUIRE_THROWS(sourceParser.parse());
  }
}
