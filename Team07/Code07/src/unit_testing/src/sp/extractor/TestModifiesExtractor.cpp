#include "catch.hpp"
#include "sp/design_extractor/extractors/ModifiesExtractor.h"
#include "sp/helper.h"
#include "sp/node/ProcedureNode.h"
#include "sp/node/ProgramNode.h"
#include "sp/node/StmtNode.h"
#include "stubs/pkb/PKBStorageWriteAPI.h"

using namespace SP;

class ModifiesAdapterStub : public ModifiesAdapter {
 public:
  ModifiesAdapterStub(const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
      : ModifiesAdapter(pkb) {}
};

TEST_CASE("ModifiesExtractor Tests") {
  std::shared_ptr<PKB::PKBStorageWriteInterface> pkb =
      std::make_shared<PKB::PKBStorageWriteStub>();

  SECTION("No extraction") {
    ModifiesExtractor extractor{ModifiesAdapterStub{pkb}};
    auto storage = extractor.getStatementStorage();
    REQUIRE(storage.size() == 0);
  }

  SECTION("Extraction of irrelevant nodes") {
    ModifiesExtractor extractor{ModifiesAdapterStub{pkb}};

    std::shared_ptr<PrintNode> print = std::make_shared<PrintNode>(1, "test");
    std::shared_ptr<ProcedureNode> procedure = std::make_shared<ProcedureNode>(
        "test", std::vector<std::shared_ptr<Node>>{});
    std::shared_ptr<ProgramNode> program =
        std::make_shared<ProgramNode>(std::vector<std::shared_ptr<Node>>{});

    extractor.visitPrint(print);
    extractor.visitProcedure(procedure);
    extractor.visitProgram(program);

    auto storage = extractor.getStatementStorage();
    REQUIRE(storage.size() == 0);
  }

  SECTION("No nesting. Extraction of relevant stmts") {
    ModifiesExtractor extractor{ModifiesAdapterStub{pkb}};
    std::vector<std::shared_ptr<ReadNode>> reads =
        makeNodes<ReadNode>({1}, {"a"});

    std::vector<std::shared_ptr<AssignNode>> assigns =
        makeAssignNodes({2}, {"a"}, {{"a"}}, {{"1"}});

    for (const auto& read : reads) {
      extractor.visitRead(read);
    }

    for (const auto& assign : assigns) {
      extractor.visitAssign(assign);
    }

    auto storage = extractor.getStatementStorage();
    REQUIRE(storage.size() == 2);
  }

  SECTION("No nesting. Extraction of multiple relevant stmts") {
    ModifiesExtractor extractor{ModifiesAdapterStub{pkb}};
    std::vector<std::shared_ptr<ReadNode>> reads =
        makeNodes<ReadNode>({1, 2, 3, 4, 5}, {"a", "b", "c", "d", "e"});

    std::vector<std::shared_ptr<AssignNode>> assigns =
        makeAssignNodes({6, 7, 8, 9, 10}, {"a", "b", "c", "d", "e"},
                        {{"a"}, {"b"}, {"c"}, {"d"}, {"e"}},
                        {{"1"}, {"2"}, {"3"}, {"4"}, {"5"}});

    for (const auto& read : reads) {
      extractor.visitRead(read);
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
    ModifiesExtractor extractor{ModifiesAdapterStub{pkb}};
    std::vector<std::shared_ptr<ReadNode>> reads =
        makeNodes<ReadNode>({1, 2, 3}, {"a", "b", "c"});

    std::vector<std::shared_ptr<AssignNode>> assigns =
        makeAssignNodes({6, 7, 8, 9, 10}, {"a", "b", "c", "d", "e"},
                        {{"a"}, {"b"}, {"c"}, {"d"}, {"e"}},
                        {{"1"}, {"2"}, {"3"}, {"4"}, {"5"}});

    for (const auto& read : reads) {
      extractor.visitRead(read);
    }

    for (const auto& assign : assigns) {
      extractor.visitAssign(assign);
    }

    auto storage = extractor.getStatementStorage();
    REQUIRE(storage.size() == 8);
  }

  SECTION("Single Nesting. Extraction of stmt containers (If)") {
    ModifiesExtractor extractor{ModifiesAdapterStub{pkb}};
    std::shared_ptr<ReadNode> child1 = std::make_shared<ReadNode>(2, "123");
    std::shared_ptr<ReadNode> child2 = std::make_shared<ReadNode>(3, "1234");
    std::vector<std::shared_ptr<AssignNode>> assigns =
        makeAssignNodes({4, 5}, {"a", "b"}, {{"a"}, {"b"}}, {{"1"}, {"2"}});
    REQUIRE(assigns.size() == 2);

    std::shared_ptr<StmtLstNode> stmtLst1 = std::make_shared<StmtLstNode>(
        std::vector<std::shared_ptr<Node>>{child1, child2});

    std::shared_ptr<StmtLstNode> stmtLst2 = std::make_shared<StmtLstNode>(
        std::vector<std::shared_ptr<Node>>{assigns[0], assigns[1]});

    std::shared_ptr<IfNode> ifStmt = std::make_shared<IfNode>(
        1, std::unordered_set<std::string>{"a"},
        std::unordered_set<std::string>{"a"}, stmtLst1, stmtLst2);

    // dfs structure
    extractor.visitIf(ifStmt);
    extractor.visitRead(child1);
    extractor.visitRead(child1);
    extractor.visitRead(child2);
    extractor.visitRead(child2);
    extractor.visitAssign(assigns[0]);
    extractor.visitAssign(assigns[0]);
    extractor.visitAssign(assigns[1]);
    extractor.visitAssign(assigns[1]);
    extractor.visitIf(ifStmt);

    auto storage = extractor.getStatementStorage();
    REQUIRE(storage.size() == 5);
  }

  SECTION("Single Nesting. Extraction of stmt containers (While)") {
    ModifiesExtractor extractor{ModifiesAdapterStub{pkb}};
    std::shared_ptr<ReadNode> child1 = std::make_shared<ReadNode>(2, "123");
    std::shared_ptr<ReadNode> child2 = std::make_shared<ReadNode>(3, "1234");

    std::shared_ptr<StmtLstNode> stmtLst = std::make_shared<StmtLstNode>(
        std::vector<std::shared_ptr<Node>>{child1, child2});

    std::shared_ptr<WhileNode> whileStmt = std::make_shared<WhileNode>(
        1, std::unordered_set<std::string>{"a"},
        std::unordered_set<std::string>{"a"}, stmtLst);

    // dfs structure
    extractor.visitWhile(whileStmt);
    extractor.visitRead(child1);
    extractor.visitRead(child1);
    extractor.visitRead(child2);
    extractor.visitRead(child2);
    extractor.visitWhile(whileStmt);

    auto storage = extractor.getStatementStorage();
    REQUIRE(storage.size() == 3);
  }

  SECTION("Single Nesting. No stmts") {
    ModifiesExtractor extractor{ModifiesAdapterStub{pkb}};
    std::vector<std::shared_ptr<IfNode>> ifs =
        makeIfNodes({1}, {{"a"}}, {{"a"}});

    std::vector<std::shared_ptr<WhileNode>> whiles =
        makeWhileNodes({2}, {{"a"}}, {{"a"}});

    for (const auto& ifStmt : ifs) {
      extractor.visitIf(ifStmt);
      extractor.visitIf(ifStmt);
    }

    for (const auto& whileStmt : whiles) {
      extractor.visitWhile(whileStmt);
      extractor.visitWhile(whileStmt);
    }

    auto storage = extractor.getStatementStorage();
    REQUIRE(storage.size() == 0);
  }
}

void check(
    std::unordered_map<std::string, std::unordered_set<std::string>>
        procedureStorage,
    std::unordered_map<std::string, std::unordered_set<std::string>> expected) {
  REQUIRE(procedureStorage == expected);
}

TEST_CASE("ModifiesExtractor Tests (Multiple Procedure)") {
  std::shared_ptr<PKB::PKBStorageWriteInterface> pkb =
      std::make_shared<PKB::PKBStorageWriteStub>();
  std::shared_ptr<ProgramNode> program =
      std::make_shared<ProgramNode>(std::vector<std::shared_ptr<Node>>{});

  SECTION("A -> B") {
    ModifiesExtractor extractor{pkb};

    auto procedures = makeProcedureNodes({"A", "B"});
    REQUIRE(procedures.size() == 2);

    auto readNodes = makeNodes<ReadNode>({1, 3}, {"a", "b"});
    REQUIRE(readNodes.size() == 2);

    auto callNodes = makeNodes<CallNode>({2}, {"B"});
    REQUIRE(callNodes.size() == 1);

    // dfs structure
    extractor.visitProgram(program);
    extractor.visitProcedure(procedures[0]);
    extractor.visitRead(readNodes[0]);
    extractor.visitRead(readNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitProcedure(procedures[0]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitRead(readNodes[1]);
    extractor.visitRead(readNodes[1]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitProgram(program);

    check(extractor.getProcedureStorage(),
          std::unordered_map<std::string, std::unordered_set<std::string>>{
              {"A", {"a", "b"}}, {"B", {"b"}}});
  }

  SECTION("A -> B -> C") {
    ModifiesExtractor extractor{pkb};

    auto procedures = makeProcedureNodes({"A", "B", "C"});
    REQUIRE(procedures.size() == 3);

    auto readNodes = makeNodes<ReadNode>({1, 4, 5}, {"a", "b", "c"});
    REQUIRE(readNodes.size() == 3);

    auto callNodes = makeNodes<CallNode>({2, 3}, {"B", "C"});
    REQUIRE(callNodes.size() == 2);

    // dfs structure
    extractor.visitProgram(program);
    extractor.visitProcedure(procedures[0]);
    extractor.visitRead(readNodes[0]);
    extractor.visitRead(readNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitProcedure(procedures[0]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitCall(callNodes[1]);
    extractor.visitCall(callNodes[1]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitRead(readNodes[1]);
    extractor.visitRead(readNodes[1]);
    extractor.visitRead(readNodes[2]);
    extractor.visitRead(readNodes[2]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitProgram(program);

    check(extractor.getProcedureStorage(),
          std::unordered_map<std::string, std::unordered_set<std::string>>{
              {"A", {"a", "b", "c"}}, {"B", {"b", "c"}}, {"C", {"b", "c"}}});
  }

  SECTION("A -> B <- C") {
    ModifiesExtractor extractor{pkb};

    auto procedures = makeProcedureNodes({"A", "B", "C"});
    REQUIRE(procedures.size() == 3);

    auto readNodes = makeNodes<ReadNode>({1, 4}, {"a", "b"});
    REQUIRE(readNodes.size() == 2);

    auto callNodes = makeNodes<CallNode>({2, 3}, {"B", "B"});
    REQUIRE(callNodes.size() == 2);

    // dfs structure
    extractor.visitProgram(program);
    extractor.visitProcedure(procedures[0]);
    extractor.visitRead(readNodes[0]);
    extractor.visitRead(readNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitProcedure(procedures[0]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitRead(readNodes[1]);
    extractor.visitRead(readNodes[1]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitCall(callNodes[1]);
    extractor.visitCall(callNodes[1]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitProgram(program);

    check(extractor.getProcedureStorage(),
          std::unordered_map<std::string, std::unordered_set<std::string>>{
              {"A", {"a", "b"}}, {"B", {"b"}}, {"C", {"b"}}});
  }

  SECTION("A -> B -> A") {
    ModifiesExtractor extractor{pkb};

    auto procedures = makeProcedureNodes({"A", "B"});
    REQUIRE(procedures.size() == 2);

    auto readNodes = makeNodes<ReadNode>({1, 3}, {"a", "b"});
    REQUIRE(readNodes.size() == 2);

    auto callNodes = makeNodes<CallNode>({2, 4}, {"B", "A"});
    REQUIRE(callNodes.size() == 2);

    // dfs structure
    extractor.visitProgram(program);
    extractor.visitProcedure(procedures[0]);
    extractor.visitRead(readNodes[0]);
    extractor.visitRead(readNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitProcedure(procedures[0]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitRead(readNodes[1]);
    extractor.visitRead(readNodes[1]);
    extractor.visitCall(callNodes[1]);
    extractor.visitCall(callNodes[1]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitProgram(program);

    check(extractor.getProcedureStorage(),
          std::unordered_map<std::string, std::unordered_set<std::string>>{
              {"A", {"a"}}, {"B", {"b"}}});
  }

  // This case shouldn't happen because calls extractor will run before
  // modifies. Cyclic calls will be flagged out and semantic exception will be
  // thrown.
  SECTION("A -> B -> C -> B") {
    ModifiesExtractor extractor{pkb};

    auto procedures = makeProcedureNodes({"A", "B", "C"});
    REQUIRE(procedures.size() == 3);

    auto readNodes = makeNodes<ReadNode>({1, 3}, {"a", "b"});
    REQUIRE(readNodes.size() == 2);

    auto callNodes = makeNodes<CallNode>({2, 4, 5}, {"B", "C", "B"});
    REQUIRE(callNodes.size() == 3);

    // dfs structure
    extractor.visitProgram(program);
    extractor.visitProcedure(procedures[0]);
    extractor.visitRead(readNodes[0]);
    extractor.visitRead(readNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitProcedure(procedures[0]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitRead(readNodes[1]);
    extractor.visitRead(readNodes[1]);
    extractor.visitCall(callNodes[1]);
    extractor.visitCall(callNodes[1]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitCall(callNodes[2]);
    extractor.visitCall(callNodes[2]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitProgram(program);

    check(extractor.getProcedureStorage(),
          std::unordered_map<std::string, std::unordered_set<std::string>>{
              {"A", {"a", "b"}}, {"B", {"b"}}, {"C", {"b"}}});
  }

  SECTION("A -> B, A -> C") {
    ModifiesExtractor extractor{pkb};

    auto procedures = makeProcedureNodes({"A", "B", "C"});
    REQUIRE(procedures.size() == 3);

    auto readNodes = makeNodes<ReadNode>({3, 4}, {"a", "b"});
    REQUIRE(readNodes.size() == 2);

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
    extractor.visitRead(readNodes[0]);
    extractor.visitRead(readNodes[0]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitRead(readNodes[1]);
    extractor.visitRead(readNodes[1]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitProgram(program);

    check(extractor.getProcedureStorage(),
          std::unordered_map<std::string, std::unordered_set<std::string>>{
              {"A", {"a", "b"}}, {"B", {"a"}}, {"C", {"b"}}});
  }

  SECTION("A -> B -> C -> D") {
    ModifiesExtractor extractor{pkb};

    auto procedures = makeProcedureNodes({"A", "B", "C", "D"});
    REQUIRE(procedures.size() == 4);

    auto readNodes = makeNodes<ReadNode>({2, 4, 6}, {"a", "b", "c"});
    REQUIRE(readNodes.size() == 3);

    auto callNodes = makeNodes<CallNode>({1, 3, 5}, {"B", "C", "D"});
    REQUIRE(callNodes.size() == 3);

    // dfs structure
    extractor.visitProgram(program);
    extractor.visitProcedure(procedures[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitProcedure(procedures[0]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitRead(readNodes[0]);
    extractor.visitRead(readNodes[0]);
    extractor.visitCall(callNodes[1]);
    extractor.visitCall(callNodes[1]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitRead(readNodes[1]);
    extractor.visitRead(readNodes[1]);
    extractor.visitCall(callNodes[2]);
    extractor.visitCall(callNodes[2]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitProcedure(procedures[3]);
    extractor.visitRead(readNodes[2]);
    extractor.visitRead(readNodes[2]);
    extractor.visitProcedure(procedures[3]);
    extractor.visitProgram(program);

    check(extractor.getProcedureStorage(),
          std::unordered_map<std::string, std::unordered_set<std::string>>{
              {"A", {"a", "b", "c"}},
              {"B", {"a", "b", "c"}},
              {"C", {"b", "c"}},
              {"D", {"c"}}});
  }

  SECTION("A -> B -> C -> D and a procedure that is not reached.") {
    ModifiesExtractor extractor{pkb};

    auto procedures = makeProcedureNodes({"A", "B", "C", "D", "E"});
    REQUIRE(procedures.size() == 5);

    auto readNodes = makeNodes<ReadNode>({2, 4, 6}, {"a", "b", "c"});
    REQUIRE(readNodes.size() == 3);

    auto callNodes = makeNodes<CallNode>({1, 3, 5}, {"B", "C", "D"});
    REQUIRE(callNodes.size() == 3);

    // dfs structure
    extractor.visitProgram(program);
    extractor.visitProcedure(procedures[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitCall(callNodes[0]);
    extractor.visitProcedure(procedures[0]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitRead(readNodes[0]);
    extractor.visitRead(readNodes[0]);
    extractor.visitCall(callNodes[1]);
    extractor.visitCall(callNodes[1]);
    extractor.visitProcedure(procedures[1]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitRead(readNodes[1]);
    extractor.visitRead(readNodes[1]);
    extractor.visitCall(callNodes[2]);
    extractor.visitCall(callNodes[2]);
    extractor.visitProcedure(procedures[2]);
    extractor.visitProcedure(procedures[3]);
    extractor.visitRead(readNodes[2]);
    extractor.visitRead(readNodes[2]);
    extractor.visitProcedure(procedures[3]);
    extractor.visitProcedure(procedures[4]);
    extractor.visitProcedure(procedures[4]);
    extractor.visitProgram(program);

    check(extractor.getProcedureStorage(),
          std::unordered_map<std::string, std::unordered_set<std::string>>{
              {"A", {"a", "b", "c"}},
              {"B", {"a", "b", "c"}},
              {"C", {"b", "c"}},
              {"D", {"c"}}});

    REQUIRE(extractor.getProcedureStorage().size() == 4);
  }
}
