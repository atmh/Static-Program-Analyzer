#include "catch.hpp"
#include "sp/extractor_adapter/adapters/FollowsAdapter.h"
#include "sp/helper.h"
#include "stubs/pkb/PKBStorageWriteAPI.h"

using namespace SP;

void testFollowsAdaptation(std::vector<int> args) {
  std::shared_ptr<PKB::PKBStorageWriteStub> pkb =
      std::make_shared<PKB::PKBStorageWriteStub>();

  std::shared_ptr<FollowsAdapter> adapter =
      std::make_shared<FollowsAdapter>(pkb);
  std::unordered_map<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>> map;

  std::unordered_map<int, int> expected;

  for (int i = 1; i < args.size(); i++) {
    std::shared_ptr<StmtNodeStub> stmtNode1 =
        std::make_shared<StmtNodeStub>(args[i - 1]);
    std::shared_ptr<StmtNodeStub> stmtNode2 =
        std::make_shared<StmtNodeStub>(args[i]);
    map.insert(std::make_pair(stmtNode1, stmtNode2));
    expected.insert(std::make_pair(args[i - 1], args[i]));
  }

  adapter->adapt(map);

  std::unordered_map<int, int> res = pkb->followsStorage;
  REQUIRE(expected == res);
}

TEST_CASE("Test parent adapt cases") {
  SECTION("Follows(1,2)") {
    std::vector<int> args = {1, 2};
    testFollowsAdaptation(args);
  }

  SECTION("Follows(1,2) Follows(2,3)") {
    std::vector<int> args = {1, 2};
    testFollowsAdaptation(args);
  }

  SECTION("Follows(1,2) Follows(2,3) Follows(3,4)") {
    std::vector<int> args = {1, 2, 3, 4};
    testFollowsAdaptation(args);
  }

  SECTION("Follows(1, 3) Follows(3, 6)") {
    std::vector<int> args = {1, 3, 6};
    testFollowsAdaptation(args);
  }

  SECTION("Follows(1, 3) Follows(3, 6) Follows(6, 7)") {
    std::vector<int> args = {1, 3, 6, 7};
    testFollowsAdaptation(args);
  }

  SECTION("Follows(1, 3) Follows(3, 6) Follows(6, 7) Follows(7, 8)") {
    std::vector<int> args = {1, 3, 6, 7, 8};
    testFollowsAdaptation(args);
  }

  SECTION("Follows(20, 33) Follows(33, 46) Follows(46, 61) Follows(61, 66)") {
    std::vector<int> args = {20, 33, 46, 61, 66};
    testFollowsAdaptation(args);
  }

  SECTION("Follows(1, )") {
    std::vector<int> args = {1};
    testFollowsAdaptation(args);
  }

  SECTION("Empty Follows") {
    std::vector<int> args = {};
    testFollowsAdaptation(args);
  }
}
