#include "catch.hpp"
#include "sp//node/ProcedureNode.h"
#include "sp/design_extractor/extractors/CallExtractor.h"
#include "sp/exception/Messages.h"
#include "sp/exception/SemanticException.h"
#include "sp/node/Node.h"
#include "sp/node/StmtLstNode.h"
#include "sp/node/StmtNode.h"
#include "sp/node/stmt_nodes/AssignNode.h"
#include "sp/node/stmt_nodes/CallNode.h"
#include "sp/node/stmt_nodes/IfNode.h"
#include "sp/node/stmt_nodes/PrintNode.h"
#include "sp/node/stmt_nodes/ReadNode.h"
#include "sp/node/stmt_nodes/WhileNode.h"
#include "stubs/pkb/PKBStorageWriteAPI.h"

using namespace SP;

class CallAdapterStub : public CallAdapter {
 public:
  CallAdapterStub(const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
      : CallAdapter(pkb) {}
};

TEST_CASE("Simple Call Extraction") {
  std::shared_ptr<PKB::PKBStorageWriteInterface> pkb =
      std::make_shared<PKB::PKBStorageWriteStub>();

  SECTION("No Extraction") {
    CallExtractor extractor{CallAdapterStub{pkb}};
    auto storage = extractor.getStorage();
    REQUIRE(storage.size() == 0);
  }

  SECTION("Extraction of irrelevant nodes") {
    CallExtractor extractor{CallAdapterStub{pkb}};

    auto readNode = std::make_shared<ReadNode>(1, "test");
    auto printNode = std::make_shared<PrintNode>(2, "test");

    std::shared_ptr<StmtLstNode> stmtLst =
        std::make_shared<StmtLstNode>(std::vector<std::shared_ptr<Node>>{});

    auto whileNode = std::make_shared<WhileNode>(
        3, std::unordered_set<std::string>{"a"},
        std::unordered_set<std::string>{"a"}, stmtLst);

    std::shared_ptr<StmtLstNode> thenStmtLst =
        std::make_shared<StmtLstNode>(std::vector<std::shared_ptr<Node>>{});
    std::shared_ptr<StmtLstNode> elseStmtLst =
        std::make_shared<StmtLstNode>(std::vector<std::shared_ptr<Node>>{});

    auto ifNode = std::make_shared<IfNode>(
        4, std::unordered_set<std::string>{"a"},
        std::unordered_set<std::string>{"a"}, thenStmtLst, elseStmtLst);

    auto assignNode = std::make_shared<AssignNode>(
        5, "test", std::unordered_set<std::string>{"a"},
        std::unordered_set<std::string>{"a"}, std::vector<std::string>{});
    auto stmtListNode =
        std::make_shared<StmtLstNode>(std::vector<std::shared_ptr<Node>>{});

    extractor.visitRead(readNode);
    extractor.visitPrint(printNode);
    extractor.visitWhile(whileNode);
    extractor.visitIf(ifNode);
    extractor.visitAssign(assignNode);
    extractor.visitStmtList(stmtListNode);

    auto storage = extractor.getStorage();
    REQUIRE(storage.size() == 0);
  }

  SECTION("Extraction of call nodes") {
    CallExtractor extractor{CallAdapterStub{pkb}};

    auto procedureNode = std::make_shared<ProcedureNode>(
        "test", std::vector<std::shared_ptr<Node>>{});
    auto callNode = std::make_shared<CallNode>(1, "test2");
    auto procedureNode2 = std::make_shared<ProcedureNode>(
        "test2", std::vector<std::shared_ptr<Node>>{});

    extractor.visitProcedure(procedureNode);
    extractor.visitCall(callNode);
    extractor.visitProcedure(procedureNode2);

    auto storage = extractor.getStorage();
    auto expected = std::vector<
        std::pair<std::shared_ptr<ProcedureNode>, std::shared_ptr<CallNode>>>{};
    expected.push_back(std::make_pair(procedureNode, callNode));

    REQUIRE(storage.size() == 1);
    REQUIRE(storage == expected);
  }
}

TEST_CASE("Complex Call Extraction") {
  std::shared_ptr<PKB::PKBStorageWriteInterface> pkb =
      std::make_shared<PKB::PKBStorageWriteStub>();

  SECTION("Extraction of multiple calls") {
    CallExtractor extractor{CallAdapterStub{pkb}};

    auto procedureNode = std::make_shared<ProcedureNode>(
        "test", std::vector<std::shared_ptr<Node>>{});
    auto procedureNode2 = std::make_shared<ProcedureNode>(
        "test2", std::vector<std::shared_ptr<Node>>{});
    auto callNode1 = std::make_shared<CallNode>(1, "test2");
    auto callNode2 = std::make_shared<CallNode>(2, "test2");

    extractor.visitProcedure(procedureNode);
    extractor.visitCall(callNode1);
    extractor.visitCall(callNode2);
    extractor.visitProcedure(procedureNode2);

    auto storage = extractor.getStorage();
    auto expected = std::vector<
        std::pair<std::shared_ptr<ProcedureNode>, std::shared_ptr<CallNode>>>{};
    expected.push_back(std::make_pair(procedureNode, callNode1));
    expected.push_back(std::make_pair(procedureNode, callNode2));

    REQUIRE(storage.size() == 2);
    REQUIRE(storage == expected);
  }

  SECTION("Extraction of nested calls") {
    CallExtractor extractor{CallAdapterStub{pkb}};

    auto procedureNode = std::make_shared<ProcedureNode>(
        "test", std::vector<std::shared_ptr<Node>>{});
    auto procedureNode2 = std::make_shared<ProcedureNode>(
        "test2", std::vector<std::shared_ptr<Node>>{});
    auto procedureNode3 = std::make_shared<ProcedureNode>(
        "test3", std::vector<std::shared_ptr<Node>>{});
    auto callNode1 = std::make_shared<CallNode>(1, "test2");
    auto callNode2 = std::make_shared<CallNode>(2, "test3");

    extractor.visitProcedure(procedureNode);
    extractor.visitCall(callNode1);
    extractor.visitProcedure(procedureNode2);
    extractor.visitCall(callNode2);
    extractor.visitProcedure(procedureNode3);

    auto storage = extractor.getStorage();
    auto expected = std::vector<
        std::pair<std::shared_ptr<ProcedureNode>, std::shared_ptr<CallNode>>>{};
    expected.push_back(std::make_pair(procedureNode, callNode1));
    expected.push_back(std::make_pair(procedureNode2, callNode2));

    REQUIRE(storage.size() == 2);
    REQUIRE(storage == expected);
  }

  SECTION("Extraction of nested calls with multiple calls") {
    CallExtractor extractor{CallAdapterStub{pkb}};

    auto procedureNode = std::make_shared<ProcedureNode>(
        "test", std::vector<std::shared_ptr<Node>>{});
    auto procedureNode2 = std::make_shared<ProcedureNode>(
        "test2", std::vector<std::shared_ptr<Node>>{});
    auto procedureNode3 = std::make_shared<ProcedureNode>(
        "test3", std::vector<std::shared_ptr<Node>>{});
    auto callNode1 = std::make_shared<CallNode>(1, "test2");
    auto callNode2 = std::make_shared<CallNode>(2, "test3");
    auto callNode3 = std::make_shared<CallNode>(3, "test3");

    extractor.visitProcedure(procedureNode);
    extractor.visitCall(callNode1);
    extractor.visitProcedure(procedureNode2);
    extractor.visitCall(callNode2);
    extractor.visitCall(callNode3);
    extractor.visitProcedure(procedureNode3);

    auto storage = extractor.getStorage();
    auto expected = std::vector<
        std::pair<std::shared_ptr<ProcedureNode>, std::shared_ptr<CallNode>>>{};
    expected.push_back(std::make_pair(procedureNode, callNode1));
    expected.push_back(std::make_pair(procedureNode2, callNode2));
    expected.push_back(std::make_pair(procedureNode2, callNode3));

    REQUIRE(storage.size() == 3);
    REQUIRE(storage == expected);
  }

  SECTION("Deeply nested calls") {
    CallExtractor extractor{CallAdapterStub{pkb}};

    auto procedureNode = std::make_shared<ProcedureNode>(
        "test", std::vector<std::shared_ptr<Node>>{});
    auto procedureNode2 = std::make_shared<ProcedureNode>(
        "test2", std::vector<std::shared_ptr<Node>>{});
    auto procedureNode3 = std::make_shared<ProcedureNode>(
        "test3", std::vector<std::shared_ptr<Node>>{});
    auto procedureNode4 = std::make_shared<ProcedureNode>(
        "test4", std::vector<std::shared_ptr<Node>>{});
    auto procedureNode5 = std::make_shared<ProcedureNode>(
        "test5", std::vector<std::shared_ptr<Node>>{});
    auto procedureNode6 = std::make_shared<ProcedureNode>(
        "test6", std::vector<std::shared_ptr<Node>>{});
    auto callNode1 = std::make_shared<CallNode>(1, "test2");
    auto callNode2 = std::make_shared<CallNode>(2, "test3");
    auto callNode3 = std::make_shared<CallNode>(3, "test4");
    auto callNode4 = std::make_shared<CallNode>(4, "test5");
    auto callNode5 = std::make_shared<CallNode>(5, "test6");

    extractor.visitProcedure(procedureNode);
    extractor.visitCall(callNode1);
    extractor.visitProcedure(procedureNode2);
    extractor.visitCall(callNode2);
    extractor.visitProcedure(procedureNode3);
    extractor.visitCall(callNode3);
    extractor.visitProcedure(procedureNode4);
    extractor.visitCall(callNode4);
    extractor.visitProcedure(procedureNode5);
    extractor.visitCall(callNode5);

    auto storage = extractor.getStorage();
    auto expected = std::vector<
        std::pair<std::shared_ptr<ProcedureNode>, std::shared_ptr<CallNode>>>{};
    expected.push_back(std::make_pair(procedureNode, callNode1));
    expected.push_back(std::make_pair(procedureNode2, callNode2));
    expected.push_back(std::make_pair(procedureNode3, callNode3));
    expected.push_back(std::make_pair(procedureNode4, callNode4));
    expected.push_back(std::make_pair(procedureNode5, callNode5));

    REQUIRE(storage.size() == 5);
    REQUIRE(storage == expected);
  }

  SECTION("Deeply nested calls with multiple calls") {
    CallExtractor extractor{CallAdapterStub{pkb}};

    auto procedureNode = std::make_shared<ProcedureNode>(
        "test", std::vector<std::shared_ptr<Node>>{});
    auto procedureNode2 = std::make_shared<ProcedureNode>(
        "test2", std::vector<std::shared_ptr<Node>>{});
    auto procedureNode3 = std::make_shared<ProcedureNode>(
        "test3", std::vector<std::shared_ptr<Node>>{});
    auto procedureNode4 = std::make_shared<ProcedureNode>(
        "test4", std::vector<std::shared_ptr<Node>>{});
    auto procedureNode5 = std::make_shared<ProcedureNode>(
        "test5", std::vector<std::shared_ptr<Node>>{});
    auto procedureNode6 = std::make_shared<ProcedureNode>(
        "test6", std::vector<std::shared_ptr<Node>>{});
    auto callNode1n1 = std::make_shared<CallNode>(1, "test2");
    auto callNode1n2 = std::make_shared<CallNode>(2, "test2");
    auto callNode1n3 = std::make_shared<CallNode>(3, "test2");
    auto callNode2n1 = std::make_shared<CallNode>(4, "test3");
    auto callNode2n2 = std::make_shared<CallNode>(5, "test3");
    auto callNode2n3 = std::make_shared<CallNode>(6, "test3");
    auto callNode3n1 = std::make_shared<CallNode>(7, "test4");
    auto callNode3n2 = std::make_shared<CallNode>(8, "test4");
    auto callNode3n3 = std::make_shared<CallNode>(9, "test4");
    auto callNode4n1 = std::make_shared<CallNode>(10, "test5");
    auto callNode4n2 = std::make_shared<CallNode>(11, "test5");
    auto callNode5n1 = std::make_shared<CallNode>(12, "test6");

    extractor.visitProcedure(procedureNode);
    extractor.visitCall(callNode1n1);
    extractor.visitCall(callNode1n2);
    extractor.visitCall(callNode1n3);
    extractor.visitProcedure(procedureNode2);
    extractor.visitCall(callNode2n1);
    extractor.visitCall(callNode2n2);
    extractor.visitCall(callNode2n3);
    extractor.visitProcedure(procedureNode3);
    extractor.visitCall(callNode3n1);
    extractor.visitCall(callNode3n2);
    extractor.visitCall(callNode3n3);
    extractor.visitProcedure(procedureNode4);
    extractor.visitCall(callNode4n1);
    extractor.visitCall(callNode4n2);
    extractor.visitProcedure(procedureNode5);
    extractor.visitCall(callNode5n1);

    auto storage = extractor.getStorage();
    auto expected = std::vector<
        std::pair<std::shared_ptr<ProcedureNode>, std::shared_ptr<CallNode>>>{};
    expected.push_back(std::make_pair(procedureNode, callNode1n1));
    expected.push_back(std::make_pair(procedureNode, callNode1n2));
    expected.push_back(std::make_pair(procedureNode, callNode1n3));
    expected.push_back(std::make_pair(procedureNode2, callNode2n1));
    expected.push_back(std::make_pair(procedureNode2, callNode2n2));
    expected.push_back(std::make_pair(procedureNode2, callNode2n3));
    expected.push_back(std::make_pair(procedureNode3, callNode3n1));
    expected.push_back(std::make_pair(procedureNode3, callNode3n2));
    expected.push_back(std::make_pair(procedureNode3, callNode3n3));
    expected.push_back(std::make_pair(procedureNode4, callNode4n1));
    expected.push_back(std::make_pair(procedureNode4, callNode4n2));
    expected.push_back(std::make_pair(procedureNode5, callNode5n1));

    REQUIRE(storage.size() == 12);
    REQUIRE(storage == expected);
  }
}

TEST_CASE("Semantic check") {
  std::shared_ptr<PKB::PKBStorageWriteInterface> pkb =
      std::make_shared<PKB::PKBStorageWriteStub>();

  SECTION("Calling non-existent procedures") {
    CallExtractor extractor{CallAdapterStub{pkb}};

    auto programNode =
        std::make_shared<ProgramNode>(std::vector<std::shared_ptr<Node>>{});
    auto procedureNode = std::make_shared<ProcedureNode>(
        "test", std::vector<std::shared_ptr<Node>>{});
    auto procedureNode2 = std::make_shared<ProcedureNode>(
        "test2", std::vector<std::shared_ptr<Node>>{});
    auto callNode1 = std::make_shared<CallNode>(1, "test2");
    auto callNode2 = std::make_shared<CallNode>(2, "test3");

    // simulating dfs
    extractor.visitProgram(programNode);
    extractor.visitProcedure(procedureNode);
    extractor.visitCall(callNode1);
    extractor.visitCall(callNode1);
    extractor.visitProcedure(procedureNode);
    extractor.visitProcedure(procedureNode2);
    extractor.visitCall(callNode2);
    extractor.visitCall(callNode2);
    extractor.visitProcedure(procedureNode2);
    REQUIRE_THROWS_MATCHES(
        extractor.visitProgram(programNode), SemanticException,
        Catch::Matchers::Message(CALL_NON_EXSISTENT_PROCEDURE));
  }

  SECTION("Duplicated Procedure Names") {
    CallExtractor extractor{CallAdapterStub{pkb}};

    auto programNode =
        std::make_shared<ProgramNode>(std::vector<std::shared_ptr<Node>>{});
    auto procedureNode = std::make_shared<ProcedureNode>(
        "test", std::vector<std::shared_ptr<Node>>{});
    auto procedureNode2 = std::make_shared<ProcedureNode>(
        "test", std::vector<std::shared_ptr<Node>>{});
    auto callNode1 = std::make_shared<CallNode>(1, "test");

    // simulating dfs
    extractor.visitProgram(programNode);
    extractor.visitProcedure(procedureNode);
    extractor.visitCall(callNode1);
    extractor.visitCall(callNode1);
    extractor.visitProcedure(procedureNode);
    extractor.visitProcedure(procedureNode2);
    extractor.visitProcedure(procedureNode2);
    REQUIRE_THROWS_MATCHES(extractor.visitProgram(programNode),
                           SemanticException,
                           Catch::Matchers::Message(DUPLICATED_PROCEDURE));
  }

  SECTION("Recursive Calls") {
    CallExtractor extractor{CallAdapterStub{pkb}};

    auto programNode =
        std::make_shared<ProgramNode>(std::vector<std::shared_ptr<Node>>{});
    auto procedureNode = std::make_shared<ProcedureNode>(
        "test", std::vector<std::shared_ptr<Node>>{});
    auto callNode1 = std::make_shared<CallNode>(1, "test");

    // simulating dfs
    extractor.visitProgram(programNode);
    extractor.visitProcedure(procedureNode);
    extractor.visitCall(callNode1);
    extractor.visitCall(callNode1);
    extractor.visitProcedure(procedureNode);
    REQUIRE_THROWS_MATCHES(extractor.visitProgram(programNode),
                           SemanticException,
                           Catch::Matchers::Message(RECURSIVE_OR_CYCLIC_CALL));
  }

  SECTION("Cyclic calls") {
    CallExtractor extractor{CallAdapterStub{pkb}};

    auto programNode =
        std::make_shared<ProgramNode>(std::vector<std::shared_ptr<Node>>{});
    auto procedureNode = std::make_shared<ProcedureNode>(
        "test", std::vector<std::shared_ptr<Node>>{});
    auto procedureNode2 = std::make_shared<ProcedureNode>(
        "test2", std::vector<std::shared_ptr<Node>>{});
    auto procedureNode3 = std::make_shared<ProcedureNode>(
        "test3", std::vector<std::shared_ptr<Node>>{});
    auto callNode1 = std::make_shared<CallNode>(1, "test2");
    auto callNode2 = std::make_shared<CallNode>(2, "test3");
    auto callNode3 = std::make_shared<CallNode>(3, "test3");

    // simulating dfs
    extractor.visitProgram(programNode);
    extractor.visitProcedure(procedureNode);
    extractor.visitCall(callNode1);
    extractor.visitCall(callNode1);
    extractor.visitProcedure(procedureNode);
    extractor.visitProcedure(procedureNode2);
    extractor.visitCall(callNode2);
    extractor.visitCall(callNode2);
    extractor.visitProcedure(procedureNode2);
    extractor.visitProcedure(procedureNode3);
    extractor.visitCall(callNode3);
    extractor.visitCall(callNode3);
    extractor.visitProcedure(procedureNode3);

    REQUIRE_THROWS_MATCHES(extractor.visitProgram(programNode),
                           SemanticException,
                           Catch::Matchers::Message(RECURSIVE_OR_CYCLIC_CALL));
  }
}
