#include "catch.hpp"
#include "sp/extractor_adapter/adapters/ParentAdapter.h"
#include "sp/helper.h"
#include "stubs/pkb/PKBStorageWriteAPI.h"

using namespace SP;

void testParentAdaptation(std::vector<int> args) {
  std::shared_ptr<PKB::PKBStorageWriteStub> pkb =
      std::make_shared<PKB::PKBStorageWriteStub>();

  std::shared_ptr<ParentAdapter> adapter = std::make_shared<ParentAdapter>(pkb);
  std::vector<std::pair<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>>>
      vec;

  std::unordered_map<int, std::unordered_set<int>> expected;

  for (int i = 1; i < args.size(); i++) {
    std::shared_ptr<StmtNodeStub> stmtNode1 =
        std::make_shared<StmtNodeStub>(args[i - 1]);
    std::shared_ptr<StmtNodeStub> stmtNode2 =
        std::make_shared<StmtNodeStub>(args[i]);
    vec.push_back(std::make_pair(stmtNode1, stmtNode2));
    expected[args[i - 1]].insert(args[i]);
  }

  adapter->adapt(vec);

  std::unordered_map<int, std::unordered_set<int>> res = pkb->parentStorage;
  REQUIRE(expected == res);
}

TEST_CASE("Test Parent adapt cases") {
  SECTION("Parent(1,2)") {
    std::vector<int> args = {1, 2};
    testParentAdaptation(args);
  }

  SECTION("Parent(1,2) Parent(2,3)") {
    std::vector<int> args = {1, 2};
    testParentAdaptation(args);
  }

  SECTION("Parent(1,2) Parent(2,3) Parent(3,4)") {
    std::vector<int> args = {1, 2, 3, 4};
    testParentAdaptation(args);
  }

  SECTION("Parent(1, 3) Parent(3, 6)") {
    std::vector<int> args = {1, 3, 6};
    testParentAdaptation(args);
  }

  SECTION("Parent(1, 3) Parent(3, 6) Parent(6, 7)") {
    std::vector<int> args = {1, 3, 6, 7};
    testParentAdaptation(args);
  }

  SECTION("Parent(1, 3) Parent(3, 6) Parent(6, 7) Parent(7, 8)") {
    std::vector<int> args = {1, 3, 6, 7, 8};
    testParentAdaptation(args);
  }

  SECTION("Parent(10, 30) Parent(30, 60) Parent(60, 72) Parent(72, 81)") {
    std::vector<int> args = {10, 30, 60, 72, 81};
    testParentAdaptation(args);
  }

  SECTION("Parent(1, )") {
    std::vector<int> args = {1};
    testParentAdaptation(args);
  }

  SECTION("Empty Parent") {
    std::vector<int> args = {};
    testParentAdaptation(args);
  }
}
