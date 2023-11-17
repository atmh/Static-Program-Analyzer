#include "catch.hpp"
#include "sp/extractor_adapter/adapters/UseAdapter.h"
#include "sp/helper.h"
#include "stubs/pkb/PKBStorageWriteAPI.h"

using namespace SP;

void testUsesAdaptation(
    std::vector<std::pair<std::shared_ptr<StmtNode>, std::string>> args) {
  std::shared_ptr<PKB::PKBStorageWriteStub> pkb =
      std::make_shared<PKB::PKBStorageWriteStub>();

  std::shared_ptr<UseAdapter> adapter = std::make_shared<UseAdapter>(pkb);

  std::unordered_map<int, std::unordered_set<std::string>> expected;
  std::unordered_map<std::shared_ptr<StmtNode>, std::unordered_set<std::string>>
      usesS{};
  std::unordered_map<std::string, std::unordered_set<std::string>> usesP{};
  for (const auto& pair : args) {
    expected[pair.first->stmtNo].insert(pair.second);
    usesS[pair.first].insert(pair.second);
    usesP["test"].insert(pair.second);
  }

  adapter->adapt(usesS, usesP);

  std::unordered_map<int, std::unordered_set<std::string>> res =
      pkb->usesStatementStorage;
  REQUIRE(expected == res);
}

TEST_CASE("Test Uses Adapter") {
  SECTION("Uses(1, a)") {
    std::shared_ptr<StmtNode> stmt1 =
        std::static_pointer_cast<StmtNode>(std::make_shared<PrintNode>(1, "a"));
    std::vector<std::pair<std::shared_ptr<StmtNode>, std::string>> args{
        {stmt1, "a"}};
    testUsesAdaptation(args);
  }

  SECTION("Uses(1, a) Uses(2,a)") {
    std::shared_ptr<StmtNode> stmt1 =
        std::static_pointer_cast<StmtNode>(std::make_shared<PrintNode>(1, "a"));
    std::shared_ptr<StmtNode> stmt2 =
        std::static_pointer_cast<StmtNode>(std::make_shared<PrintNode>(2, "a"));
    std::vector<std::pair<std::shared_ptr<StmtNode>, std::string>> args{
        {stmt1, "a"}, {stmt2, "a"}};
    testUsesAdaptation(args);
  }

  SECTION("Empty Uses") {
    std::vector<std::pair<std::shared_ptr<StmtNode>, std::string>> args{};
    testUsesAdaptation(args);
  }

  SECTION("Uses(1, a) Uses(2,a) Uses(3, 123)") {
    std::shared_ptr<StmtNode> stmt1 =
        std::static_pointer_cast<StmtNode>(std::make_shared<PrintNode>(1, "a"));
    std::shared_ptr<StmtNode> stmt2 =
        std::static_pointer_cast<StmtNode>(std::make_shared<PrintNode>(2, "a"));
    std::shared_ptr<StmtNode> stmt3 = std::static_pointer_cast<StmtNode>(
        std::make_shared<PrintNode>(3, "123"));
    std::vector<std::pair<std::shared_ptr<StmtNode>, std::string>> args{
        {stmt1, "a"}, {stmt2, "a"}, {stmt3, "123"}};
    testUsesAdaptation(args);
  }
}
