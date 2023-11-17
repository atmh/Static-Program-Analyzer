#include "catch.hpp"
#include "sp/design_extractor/extractors/UseExtractor.h"
#include "sp/helper.h"
#include "sp/node/ProcedureNode.h"
#include "sp/node/ProgramNode.h"
#include "sp/node/StmtNode.h"
#include "stubs/pkb/PKBStorageWriteAPI.h"

using namespace SP;

class UsesAdapterStub : public UseAdapter {
 public:
  UsesAdapterStub(const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
      : UseAdapter(pkb) {}
};

TEST_CASE("UseExtractor Tests") {
  std::shared_ptr<PKB::PKBStorageWriteInterface> pkb =
      std::make_shared<PKB::PKBStorageWriteStub>();
  SECTION("No extraction") {
    UseExtractor extractor{UsesAdapterStub{pkb}};
    auto storage = extractor.getStatementStorage();
    REQUIRE(storage.size() == 0);
  }

  SECTION("Extraction of irrevelant nodes") {
    UseExtractor extractor{UsesAdapterStub{pkb}};

    std::shared_ptr<ReadNode> read = std::make_shared<ReadNode>(1, "test");
    std::shared_ptr<ProcedureNode> procedure = std::make_shared<ProcedureNode>(
        "test", std::vector<std::shared_ptr<Node>>{});
    std::shared_ptr<ProgramNode> program =
        std::make_shared<ProgramNode>(std::vector<std::shared_ptr<Node>>{});

    extractor.visitRead(read);
    extractor.visitProcedure(procedure);
    extractor.visitProgram(program);

    auto storage = extractor.getStatementStorage();
    REQUIRE(storage.size() == 0);
  }

  SECTION("No nesting. Extraction of relevant stmts") {
    UseExtractor extractor{UsesAdapterStub{pkb}};
    std::vector<std::shared_ptr<PrintNode>> prints =
        makeNodes<PrintNode>({1}, {"a"});

    std::vector<std::shared_ptr<AssignNode>> assigns =
        makeAssignNodes({2}, {"a"}, {{"a"}}, {{"1"}});

    for (const auto& print : prints) {
      extractor.visitPrint(print);
    }

    for (const auto& assign : assigns) {
      extractor.visitAssign(assign);
    }

    auto storage = extractor.getStatementStorage();
    REQUIRE(storage.size() == 2);
  }

  SECTION("No nesting. Extraction of multiple relevant stmts") {
    UseExtractor extractor{UsesAdapterStub{pkb}};

    std::vector<std::shared_ptr<PrintNode>> prints =
        makeNodes<PrintNode>({1, 2, 3, 4, 5}, {"a", "b", "c", "d", "e"});

    std::vector<std::shared_ptr<AssignNode>> assigns =
        makeAssignNodes({6, 7, 8, 9, 10}, {"a", "b", "c", "d", "e"},
                        {{"a", "a2"}, {"b"}, {"c"}, {"d"}, {"e"}},
                        {{"1"}, {"2"}, {"3"}, {"4"}, {"5"}});

    for (const auto& print : prints) {
      extractor.visitPrint(print);
    }

    for (const auto& assign : assigns) {
      extractor.visitAssign(assign);
    }

    auto storage = extractor.getStatementStorage();
    REQUIRE(storage.size() == 10);
  }

  SECTION(
      "No nesting. Extraction of multiple relevant stmts. Not equal number of "
      "nodes.") {
    UseExtractor extractor{UsesAdapterStub{pkb}};
    std::vector<std::shared_ptr<PrintNode>> prints =
        makeNodes<PrintNode>({1, 2, 3}, {"a", "b", "c"});

    std::vector<std::shared_ptr<AssignNode>> assigns =
        makeAssignNodes({6, 7, 8, 9, 10}, {"a", "b", "c", "d", "e"},
                        {{"a", "a2"}, {"b"}, {"c"}, {"d"}, {"e"}},
                        {{"1"}, {"2"}, {"3"}, {"4"}, {"5"}});

    for (const auto& print : prints) {
      extractor.visitPrint(print);
    }

    for (const auto& assign : assigns) {
      extractor.visitAssign(assign);
    }

    auto storage = extractor.getStatementStorage();
    REQUIRE(storage.size() == 8);
  }

  SECTION("Single Nesting. Extraction of stmt containers (If)") {
    UseExtractor extractor{UsesAdapterStub{pkb}};
    std::shared_ptr<PrintNode> child1 = std::make_shared<PrintNode>(2, "123");
    std::shared_ptr<PrintNode> child2 = std::make_shared<PrintNode>(4, "1234");
    std::vector<std::shared_ptr<AssignNode>> assigns =
        makeAssignNodes({3, 5}, {"a", "b"}, {{"a"}, {"b"}}, {{"1"}, {"2"}});
    REQUIRE(assigns.size() == 2);

    std::shared_ptr<StmtLstNode> stmtLst1 = std::make_shared<StmtLstNode>(
        std::vector<std::shared_ptr<Node>>{child1, assigns[0]});

    std::shared_ptr<StmtLstNode> stmtLst2 = std::make_shared<StmtLstNode>(
        std::vector<std::shared_ptr<Node>>{child2, assigns[1]});

    std::shared_ptr<IfNode> ifStmt = std::make_shared<IfNode>(
        1, std::unordered_set<std::string>{"a"},
        std::unordered_set<std::string>{"a"}, stmtLst1, stmtLst2);

    // dfs visiting order
    extractor.visitIf(ifStmt);
    extractor.visitPrint(child1);
    extractor.visitPrint(child1);
    extractor.visitAssign(assigns[0]);
    extractor.visitAssign(assigns[0]);
    extractor.visitPrint(child2);
    extractor.visitPrint(child2);
    extractor.visitAssign(assigns[1]);
    extractor.visitAssign(assigns[1]);
    extractor.visitIf(ifStmt);

    auto storage = extractor.getStatementStorage();
    REQUIRE(storage.size() == 5);
  }

  SECTION("Single Nesting. Extraction of stmt containers (While)") {
    UseExtractor extractor{UsesAdapterStub{pkb}};
    std::shared_ptr<PrintNode> child1 = std::make_shared<PrintNode>(2, "123");
    std::shared_ptr<PrintNode> child2 = std::make_shared<PrintNode>(4, "1234");
    std::vector<std::shared_ptr<AssignNode>> assigns =
        makeAssignNodes({3, 5}, {"a", "b"}, {{"a"}, {"b"}}, {{"1"}, {"2"}});
    REQUIRE(assigns.size() == 2);

    std::shared_ptr<StmtLstNode> stmtLst =
        std::make_shared<StmtLstNode>(std::vector<std::shared_ptr<Node>>{
            child1, child2, assigns[0], assigns[1]});

    std::shared_ptr<WhileNode> whileStmt = std::make_shared<WhileNode>(
        1, std::unordered_set<std::string>{"a"},
        std::unordered_set<std::string>{"a"}, stmtLst);

    // dfs visiting order
    extractor.visitWhile(whileStmt);
    extractor.visitPrint(child1);
    extractor.visitPrint(child1);
    extractor.visitAssign(assigns[0]);
    extractor.visitAssign(assigns[0]);
    extractor.visitPrint(child2);
    extractor.visitPrint(child2);
    extractor.visitAssign(assigns[1]);
    extractor.visitAssign(assigns[1]);
    extractor.visitWhile(whileStmt);

    auto storage = extractor.getStatementStorage();
    REQUIRE(storage.size() == 5);
  }

  SECTION("Single Nesting. No stmts") {
    UseExtractor extractor{UsesAdapterStub{pkb}};
    std::vector<std::shared_ptr<IfNode>> ifs =
        makeIfNodes({1}, {{"a"}}, {{"1"}});

    std::vector<std::shared_ptr<WhileNode>> whiles =
        makeWhileNodes({2}, {{"a"}}, {{"2"}});

    for (const auto& ifStmt : ifs) {
      // dfs visiting order
      extractor.visitIf(ifStmt);
      extractor.visitIf(ifStmt);
    }

    for (const auto& whileStmt : whiles) {
      // dfs visiting order
      extractor.visitWhile(whileStmt);
      extractor.visitWhile(whileStmt);
    }

    auto storage = extractor.getStatementStorage();
    REQUIRE(storage.size() == 2);
  }

  SECTION("Nesting.") {
    UseExtractor extractor{UsesAdapterStub{pkb}};
    std::vector<std::shared_ptr<IfNode>> ifs =
        makeIfNodes({1}, {{"a"}}, {{"1"}});

    std::vector<std::shared_ptr<WhileNode>> whiles =
        makeWhileNodes({2}, {{"b"}}, {{"2"}});
    REQUIRE(ifs.size() == 1);
    REQUIRE(whiles.size() == 1);

    // dfs structure.
    extractor.visitIf(ifs[0]);
    extractor.visitWhile(whiles[0]);
    extractor.visitWhile(whiles[0]);
    extractor.visitIf(ifs[0]);

    auto storage = extractor.getStatementStorage();
    REQUIRE(storage.size() == 2);
  }
}

TEST_CASE("UseExtractor Tests (Multiple Procedure)") {
  std::shared_ptr<PKB::PKBStorageWriteInterface> pkb =
      std::make_shared<PKB::PKBStorageWriteStub>();
  std::shared_ptr<ProgramNode> program =
      std::make_shared<ProgramNode>(std::vector<std::shared_ptr<Node>>{});

  SECTION("A -> B") {
    UseExtractor extractor{pkb};

    auto procedures = makeProcedureNodes({"A", "B"});
    REQUIRE(procedures.size() == 2);

    auto printNodes = makeNodes<PrintNode>({1, 3}, {"a", "b"});
    REQUIRE(printNodes.size() == 2);

    auto callNodes = makeNodes<CallNode>({2}, {"B"});
    REQUIRE(callNodes.size() == 1);

    // dfs structure
    extractor.visitProgram(program);
    extractor.visitProcedure(procedures[0]);
    extractor.visitPrint(printNodes[0]);
    extractor.visitPrint(printNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitProcedure(procedures[0]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitPrint(printNodes[1]);
    extractor.visitPrint(printNodes[1]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitProgram(program);

    REQUIRE(extractor.getProcedureStorage() ==
            std::unordered_map<std::string, std::unordered_set<std::string>>{
                {"A", {"a", "b"}}, {"B", {"b"}}});
  }

  SECTION("A -> B -> C") {
    UseExtractor extractor{pkb};

    auto procedures = makeProcedureNodes({"A", "B", "C"});
    REQUIRE(procedures.size() == 3);

    auto printNodes = makeNodes<PrintNode>({1, 4, 5}, {"a", "b", "c"});
    REQUIRE(printNodes.size() == 3);

    auto callNodes = makeNodes<CallNode>({2, 3}, {"B", "C"});
    REQUIRE(callNodes.size() == 2);

    // dfs structure
    extractor.visitProgram(program);
    extractor.visitProcedure(procedures[0]);
    extractor.visitPrint(printNodes[0]);
    extractor.visitPrint(printNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitProcedure(procedures[0]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitCall(callNodes[1]);
    extractor.visitCall(callNodes[1]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitPrint(printNodes[1]);
    extractor.visitPrint(printNodes[1]);
    extractor.visitPrint(printNodes[2]);
    extractor.visitPrint(printNodes[2]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitProgram(program);

    REQUIRE(extractor.getProcedureStorage() ==
            std::unordered_map<std::string, std::unordered_set<std::string>>{
                {"A", {"a", "b", "c"}}, {"B", {"b", "c"}}, {"C", {"b", "c"}}});
  }

  SECTION("A -> B <- C") {
    UseExtractor extractor{pkb};

    auto procedures = makeProcedureNodes({"A", "B", "C"});
    REQUIRE(procedures.size() == 3);

    auto printNodes = makeNodes<PrintNode>({1, 4}, {"a", "b"});
    REQUIRE(printNodes.size() == 2);

    auto callNodes = makeNodes<CallNode>({2, 3}, {"B", "B"});
    REQUIRE(callNodes.size() == 2);

    // dfs structure
    extractor.visitProgram(program);
    extractor.visitProcedure(procedures[0]);
    extractor.visitPrint(printNodes[0]);
    extractor.visitPrint(printNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitProcedure(procedures[0]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitPrint(printNodes[1]);
    extractor.visitPrint(printNodes[1]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitCall(callNodes[1]);
    extractor.visitCall(callNodes[1]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitProgram(program);

    REQUIRE(extractor.getProcedureStorage() ==
            std::unordered_map<std::string, std::unordered_set<std::string>>{
                {"A", {"a", "b"}}, {"B", {"b"}}, {"C", {"b"}}});
  }

  SECTION("A -> B -> A") {
    UseExtractor extractor{pkb};

    auto procedures = makeProcedureNodes({"A", "B"});
    REQUIRE(procedures.size() == 2);

    auto printNodes = makeNodes<PrintNode>({1, 3}, {"a", "b"});
    REQUIRE(printNodes.size() == 2);

    auto callNodes = makeNodes<CallNode>({2, 4}, {"B", "A"});
    REQUIRE(callNodes.size() == 2);

    // dfs structure
    extractor.visitProgram(program);
    extractor.visitProcedure(procedures[0]);
    extractor.visitPrint(printNodes[0]);
    extractor.visitPrint(printNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitProcedure(procedures[0]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitPrint(printNodes[1]);
    extractor.visitPrint(printNodes[1]);
    extractor.visitCall(callNodes[1]);
    extractor.visitCall(callNodes[1]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitProgram(program);

    REQUIRE(extractor.getProcedureStorage() ==
            std::unordered_map<std::string, std::unordered_set<std::string>>{
                {"A", {"a"}}, {"B", {"b"}}});
  }

  // This case shouldn't happen because calls extractor will run before
  // modifies. Cyclic calls will be flagged out and semantic exception will be
  // thrown.
  SECTION("A -> B -> C -> B") {
    UseExtractor extractor{pkb};

    auto procedures = makeProcedureNodes({"A", "B", "C"});
    REQUIRE(procedures.size() == 3);

    auto printNodes = makeNodes<PrintNode>({1, 3}, {"a", "b"});
    REQUIRE(printNodes.size() == 2);

    auto callNodes = makeNodes<CallNode>({2, 4, 5}, {"B", "C", "B"});
    REQUIRE(callNodes.size() == 3);

    // dfs structure
    extractor.visitProgram(program);
    extractor.visitProcedure(procedures[0]);
    extractor.visitPrint(printNodes[0]);
    extractor.visitPrint(printNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitProcedure(procedures[0]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitPrint(printNodes[1]);
    extractor.visitPrint(printNodes[1]);
    extractor.visitCall(callNodes[1]);
    extractor.visitCall(callNodes[1]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitCall(callNodes[2]);
    extractor.visitCall(callNodes[2]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitProgram(program);

    REQUIRE(extractor.getProcedureStorage() ==
            std::unordered_map<std::string, std::unordered_set<std::string>>{
                {"A", {"a", "b"}}, {"B", {"b"}}, {"C", {"b"}}});
  }

  SECTION("A -> B, A -> C") {
    UseExtractor extractor{pkb};

    auto procedures = makeProcedureNodes({"A", "B", "C"});
    REQUIRE(procedures.size() == 3);

    auto printNodes = makeNodes<PrintNode>({3, 4}, {"a", "b"});
    REQUIRE(printNodes.size() == 2);

    auto callNodes = makeNodes<CallNode>({1, 2}, {"B", "C"});
    REQUIRE(callNodes.size() == 2);

    // dfs structure
    extractor.visitProgram(program);
    extractor.visitProcedure(procedures[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitCall(callNodes[1]);
    extractor.visitCall(callNodes[1]);
    extractor.visitProcedure(procedures[0]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitPrint(printNodes[0]);
    extractor.visitPrint(printNodes[0]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitPrint(printNodes[1]);
    extractor.visitPrint(printNodes[1]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitProgram(program);

    REQUIRE(extractor.getProcedureStorage() ==
            std::unordered_map<std::string, std::unordered_set<std::string>>{
                {"A", {"a", "b"}}, {"B", {"a"}}, {"C", {"b"}}});
  }

  SECTION("A -> B -> C -> D") {
    UseExtractor extractor{pkb};

    auto procedures = makeProcedureNodes({"A", "B", "C", "D"});
    REQUIRE(procedures.size() == 4);

    auto printNodes = makeNodes<PrintNode>({2, 4, 6}, {"a", "b", "c"});
    REQUIRE(printNodes.size() == 3);

    auto callNodes = makeNodes<CallNode>({1, 3, 5}, {"B", "C", "D"});
    REQUIRE(callNodes.size() == 3);

    // dfs structure
    extractor.visitProgram(program);
    extractor.visitProcedure(procedures[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitProcedure(procedures[0]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitPrint(printNodes[0]);
    extractor.visitPrint(printNodes[0]);
    extractor.visitCall(callNodes[1]);
    extractor.visitCall(callNodes[1]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitPrint(printNodes[1]);
    extractor.visitPrint(printNodes[1]);
    extractor.visitCall(callNodes[2]);
    extractor.visitCall(callNodes[2]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitProcedure(procedures[3]);
    extractor.visitPrint(printNodes[2]);
    extractor.visitPrint(printNodes[2]);
    extractor.visitProcedure(procedures[3]);
    extractor.visitProgram(program);

    REQUIRE(extractor.getProcedureStorage() ==
            std::unordered_map<std::string, std::unordered_set<std::string>>{
                {"A", {"a", "b", "c"}},
                {"B", {"a", "b", "c"}},
                {"C", {"b", "c"}},
                {"D", {"c"}}});
  }

  SECTION("A -> B -> C -> D and a procedure that is not reached.") {
    UseExtractor extractor{pkb};

    auto procedures = makeProcedureNodes({"A", "B", "C", "D", "E"});
    REQUIRE(procedures.size() == 5);

    auto printNodes = makeNodes<PrintNode>({2, 4, 6}, {"a", "b", "c"});
    REQUIRE(printNodes.size() == 3);

    auto callNodes = makeNodes<CallNode>({1, 3, 5}, {"B", "C", "D"});
    REQUIRE(callNodes.size() == 3);

    // dfs structure
    extractor.visitProgram(program);
    extractor.visitProcedure(procedures[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitProcedure(procedures[0]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitPrint(printNodes[0]);
    extractor.visitPrint(printNodes[0]);
    extractor.visitCall(callNodes[1]);
    extractor.visitCall(callNodes[1]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitPrint(printNodes[1]);
    extractor.visitPrint(printNodes[1]);
    extractor.visitCall(callNodes[2]);
    extractor.visitCall(callNodes[2]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitProcedure(procedures[3]);
    extractor.visitPrint(printNodes[2]);
    extractor.visitPrint(printNodes[2]);
    extractor.visitProcedure(procedures[3]);
    extractor.visitProcedure(procedures[4]);
    extractor.visitProcedure(procedures[4]);
    extractor.visitProgram(program);

    REQUIRE(extractor.getProcedureStorage() ==
            std::unordered_map<std::string, std::unordered_set<std::string>>{
                {"A", {"a", "b", "c"}},
                {"B", {"a", "b", "c"}},
                {"C", {"b", "c"}},
                {"D", {"c"}}});

    REQUIRE(extractor.getProcedureStorage().size() == 4);
  }
}