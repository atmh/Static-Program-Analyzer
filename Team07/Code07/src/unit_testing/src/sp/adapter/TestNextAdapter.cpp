#include "catch.hpp"
#include "sp/extractor_adapter/adapters/NextAdapter.h"
#include "sp/helper.h"
#include "sp/node/ProgramNode.h"
#include "sp/node/stmt_nodes/ReadNode.h"
#include "stubs/pkb/PKBStorageWriteAPI.h"

using namespace SP;

void testNextAdaptation(
    std::vector<std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>>> args) {
  std::shared_ptr<PKB::PKBStorageWriteStub> pkb =
      std::make_shared<PKB::PKBStorageWriteStub>();

  std::shared_ptr<NextAdapter> adapter = std::make_shared<NextAdapter>(pkb);
  adapter->adapt(args);
  std::unordered_map<int, std::unordered_set<int>> actual;
  for (const auto& [s1, s2] : args) {
    std::shared_ptr<StmtNode> stmt1 = std::dynamic_pointer_cast<StmtNode>(s1);
    std::shared_ptr<StmtNode> stmt2 = std::dynamic_pointer_cast<StmtNode>(s2);
    if (stmt1 != nullptr && stmt2 != nullptr)
      actual[stmt1->stmtNo].insert(stmt2->stmtNo);
  }

  REQUIRE(actual.size() == pkb->nextStorage.size());
  for (const auto& [k, _] : actual) {
    std::unordered_set<int> expected = pkb->nextStorage[k];
    REQUIRE(expected == actual[k]);
  }
}

TEST_CASE("Test Next Adapter") {
  SECTION("Invalid next one of the node is not a stmt node.") {
    std::vector<std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>>> args{};
    std::shared_ptr<Node> a =
        std::make_shared<ProgramNode>(std::vector<std::shared_ptr<Node>>{});
    std::shared_ptr<Node> b = std::make_shared<ReadNode>(1, "a");

    args.push_back(std::make_pair(a, b));
    testNextAdaptation(args);
  }

  SECTION("Invalid both of the node is not a stmt node.") {
    std::vector<std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>>> args{};
    std::shared_ptr<Node> a =
        std::make_shared<ProgramNode>(std::vector<std::shared_ptr<Node>>{});
    std::shared_ptr<Node> b =
        std::make_shared<ProgramNode>(std::vector<std::shared_ptr<Node>>{});

    args.push_back(std::make_pair(a, b));
    testNextAdaptation(args);
  }

  SECTION("Next(1,2)") {
    std::vector<std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>>> args{};
    std::shared_ptr<Node> a = std::make_shared<ReadNode>(1, "a");
    std::shared_ptr<Node> b = std::make_shared<ReadNode>(2, "a");

    args.push_back(std::make_pair(a, b));
    testNextAdaptation(args);
  }

  SECTION("Empty Next") {
    std::vector<std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>>> args{};
    testNextAdaptation(args);
  }

  SECTION("Next(1, 2) Next(2,3) Next(3, 1)") {
    std::vector<std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>>> args{};
    std::shared_ptr<Node> a = std::make_shared<ReadNode>(1, "a");
    std::shared_ptr<Node> b = std::make_shared<ReadNode>(2, "a");
    std::shared_ptr<Node> c = std::make_shared<ReadNode>(2, "a");

    args.push_back(std::make_pair(a, b));
    args.push_back(std::make_pair(b, c));
    args.push_back(std::make_pair(c, a));
    testNextAdaptation(args);
  }
}
