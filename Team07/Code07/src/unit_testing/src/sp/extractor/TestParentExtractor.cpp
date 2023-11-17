#include "catch.hpp"
#include "sp/design_extractor/extractors/ParentExtractor.h"
#include "sp/node/ProcedureNode.h"
#include "sp/node/ProgramNode.h"
#include "sp/node/StmtLstNode.h"
#include "sp/node/stmt_nodes/AssignNode.h"
#include "sp/node/stmt_nodes/CallNode.h"
#include "sp/node/stmt_nodes/IfNode.h"
#include "sp/node/stmt_nodes/PrintNode.h"
#include "sp/node/stmt_nodes/ReadNode.h"
#include "sp/node/stmt_nodes/WhileNode.h"
#include "stubs/pkb/PKBStorageWriteAPI.h"

using namespace SP;

class ParentAdapterStub : public ParentAdapter {
 public:
  ParentAdapterStub(const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
      : ParentAdapter(pkb) {}
};

TEST_CASE("ParentExtractor Tests (Single level nesting)") {
  std::shared_ptr<PKB::PKBStorageWriteInterface> pkb =
      std::make_shared<PKB::PKBStorageWriteStub>();

  SECTION("Visit IfNodes") {
    std::shared_ptr<CallNode> child1 = std::make_shared<CallNode>(5, "123");
    std::shared_ptr<CallNode> child2 = std::make_shared<CallNode>(6, "1234");

    std::shared_ptr<StmtLstNode> stmtLst1 = std::make_shared<StmtLstNode>(
        std::vector<std::shared_ptr<Node>>{child1});

    std::shared_ptr<StmtLstNode> stmtLst2 = std::make_shared<StmtLstNode>(
        std::vector<std::shared_ptr<Node>>{child2});

    std::shared_ptr<IfNode> ifNode = std::make_shared<IfNode>(
        1, std::unordered_set<std::string>{"123"},
        std::unordered_set<std::string>{"321"}, stmtLst1, stmtLst2);

    std::vector<std::pair<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>>>
        expected = {{ifNode, child1}, {ifNode, child2}};

    ParentExtractor extractor{ParentAdapterStub{pkb}};
    extractor.visitIf(ifNode);

    REQUIRE(expected == extractor.getStorage());
  }

  SECTION("Visit whileNode") {
    std::shared_ptr<CallNode> child1 = std::make_shared<CallNode>(5, "123");

    std::shared_ptr<StmtLstNode> stmtLst = std::make_shared<StmtLstNode>(
        std::vector<std::shared_ptr<Node>>{child1});

    std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(
        1, std::unordered_set<std::string>{"123"},
        std::unordered_set<std::string>{"321"}, stmtLst);

    std::vector<std::pair<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>>>
        expected = {{whileNode, child1}};

    ParentExtractor extractor{ParentAdapterStub{pkb}};
    extractor.visitWhile(whileNode);

    REQUIRE(expected == extractor.getStorage());
  }

  SECTION("Visit non-container node") {
    std::shared_ptr<CallNode> node1 = std::make_shared<CallNode>(5, "123");
    std::shared_ptr<ReadNode> node2 = std::make_shared<ReadNode>(6, "1234");
    std::shared_ptr<AssignNode> node3 = std::make_shared<AssignNode>(
        1, "123", std::unordered_set<std::string>{},
        std::unordered_set<std::string>{}, std::vector<std::string>{"123"});

    std::shared_ptr<ProcedureNode> node4 = std::make_shared<ProcedureNode>(
        "test", std::vector<std::shared_ptr<Node>>{});
    std::shared_ptr<PrintNode> node5 = std::make_shared<PrintNode>(7, "123");
    std::shared_ptr<ProgramNode> node6 =
        std::make_shared<ProgramNode>(std::vector<std::shared_ptr<Node>>{});
    std::shared_ptr<StmtLstNode> node7 =
        std::make_shared<StmtLstNode>(std::vector<std::shared_ptr<Node>>{});

    std::vector<std::pair<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>>>
        expected{};

    ParentExtractor extractor{ParentAdapterStub{pkb}};
    extractor.visitCall(node1);
    extractor.visitRead(node2);
    extractor.visitAssign(node3);
    extractor.visitProcedure(node4);
    extractor.visitPrint(node5);
    extractor.visitProgram(node6);
    extractor.visitStmtList(node7);

    REQUIRE(expected == extractor.getStorage());
  }

  SECTION("Multiple statements inside container statement") {
    std::shared_ptr<CallNode> child1 = std::make_shared<CallNode>(5, "123");
    std::shared_ptr<CallNode> child2 = std::make_shared<CallNode>(6, "123");
    std::shared_ptr<CallNode> child3 = std::make_shared<CallNode>(7, "123");

    std::shared_ptr<StmtLstNode> stmtLst = std::make_shared<StmtLstNode>(
        std::vector<std::shared_ptr<Node>>{child1, child2, child3});
    std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(
        1, std::unordered_set<std::string>{"123"},
        std::unordered_set<std::string>{"321"}, stmtLst);
    std::vector<std::pair<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>>>
        expected = {
            {whileNode, child1}, {whileNode, child2}, {whileNode, child3}};

    ParentExtractor extractor{ParentAdapterStub{pkb}};
    extractor.visitWhile(whileNode);

    REQUIRE(expected == extractor.getStorage());
  }

  SECTION("Container statements with no children") {
    std::shared_ptr<StmtLstNode> stmtLst =
        std::make_shared<StmtLstNode>(std::vector<std::shared_ptr<Node>>{});
    std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(
        1, std::unordered_set<std::string>{"123"},
        std::unordered_set<std::string>{"321"}, stmtLst);
    std::vector<std::pair<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>>>
        expected = {};

    ParentExtractor extractor{ParentAdapterStub{pkb}};
    extractor.visitWhile(whileNode);

    REQUIRE(expected == extractor.getStorage());
  }

  SECTION("Visit nested container statements") {
    std::shared_ptr<CallNode> child1 = std::make_shared<CallNode>(5, "123");
    std::shared_ptr<CallNode> child2 = std::make_shared<CallNode>(6, "123");
    std::shared_ptr<CallNode> child3 = std::make_shared<CallNode>(7, "123");
    std::shared_ptr<CallNode> child4 = std::make_shared<CallNode>(8, "123");
    std::shared_ptr<CallNode> child5 = std::make_shared<CallNode>(9, "123");
    std::shared_ptr<CallNode> child6 = std::make_shared<CallNode>(10, "123");
    std::shared_ptr<CallNode> child7 = std::make_shared<CallNode>(3, "123");

    std::shared_ptr<StmtLstNode> stmtLst1 = std::make_shared<StmtLstNode>(
        std::vector<std::shared_ptr<Node>>{child1, child2, child3});

    std::shared_ptr<StmtLstNode> stmtLst2 = std::make_shared<StmtLstNode>(
        std::vector<std::shared_ptr<Node>>{child4, child5, child6});

    std::shared_ptr<IfNode> ifNode = std::make_shared<IfNode>(
        2, std::unordered_set<std::string>{"123"},
        std::unordered_set<std::string>{"321"}, stmtLst1, stmtLst2);

    std::shared_ptr<StmtLstNode> stmtLst = std::make_shared<StmtLstNode>(
        std::vector<std::shared_ptr<Node>>{ifNode, child7});

    std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(
        1, std::unordered_set<std::string>{"123"},
        std::unordered_set<std::string>{"321"}, stmtLst);
    std::vector<std::pair<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>>>
        expected = {{whileNode, ifNode}, {whileNode, child7}, {ifNode, child1},
                    {ifNode, child2},    {ifNode, child3},    {ifNode, child4},
                    {ifNode, child5},    {ifNode, child6}};

    ParentExtractor extractor{ParentAdapterStub{pkb}};
    extractor.visitWhile(whileNode);
    extractor.visitIf(ifNode);

    REQUIRE(expected == extractor.getStorage());
  }

  SECTION("Visit If Then and Else is nullptr") {
    std::shared_ptr<IfNode> ifNode = std::make_shared<IfNode>(
        2, std::unordered_set<std::string>{"123"},
        std::unordered_set<std::string>{"321"}, nullptr, nullptr);

    ParentExtractor extractor{ParentAdapterStub{pkb}};

    REQUIRE_NOTHROW(extractor.visitIf(ifNode));
  }

  SECTION("Visit while and stmtLst is nullptr") {
    std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(
        1, std::unordered_set<std::string>{"123"},
        std::unordered_set<std::string>{"321"}, nullptr);

    ParentExtractor extractor{ParentAdapterStub{pkb}};

    REQUIRE_NOTHROW(extractor.visitWhile(whileNode));
  }
}
