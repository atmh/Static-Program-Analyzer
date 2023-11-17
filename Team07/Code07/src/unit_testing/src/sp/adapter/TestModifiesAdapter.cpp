#include "catch.hpp"
#include "sp/extractor_adapter/adapters/ModifiesAdapter.h"
#include "sp/helper.h"
#include "stubs/pkb/PKBStorageWriteAPI.h"

using namespace SP;

void testModifiesAdaptation(
    std::vector<std::pair<std::shared_ptr<StmtNode>, std::string>> args) {
  std::shared_ptr<PKB::PKBStorageWriteStub> pkb =
      std::make_shared<PKB::PKBStorageWriteStub>();

  std::shared_ptr<ModifiesAdapter> adapter =
      std::make_shared<ModifiesAdapter>(pkb);

  std::unordered_map<int, std::unordered_set<std::string>> expected;
  std::unordered_map<std::shared_ptr<StmtNode>, std::unordered_set<std::string>>
      modifiesS{};
  std::unordered_map<std::string, std::unordered_set<std::string>> modifiesP{};
  for (const auto& pair : args) {
    expected[pair.first->stmtNo].insert(pair.second);
    modifiesS[pair.first].insert(pair.second);
    modifiesP["test"].insert(pair.second);
  }

  adapter->adapt(modifiesS, modifiesP);

  std::unordered_map<int, std::unordered_set<std::string>> res =
      pkb->modifiesStatementStorage;
  REQUIRE(expected == res);
}

TEST_CASE("Test Modifies Adapter") {
  SECTION("Modifies(1, a)") {
    std::shared_ptr<StmtNode> stmt1 =
        std::static_pointer_cast<StmtNode>(std::make_shared<ReadNode>(1, "a"));
    std::vector<std::pair<std::shared_ptr<StmtNode>, std::string>> args{
        {stmt1, "a"}};
    testModifiesAdaptation(args);
  }

  SECTION("Modifies(1, a) Modifies(2,a)") {
    std::shared_ptr<StmtNode> stmt1 =
        std::static_pointer_cast<StmtNode>(std::make_shared<ReadNode>(1, "a"));
    std::shared_ptr<StmtNode> stmt2 =
        std::static_pointer_cast<StmtNode>(std::make_shared<ReadNode>(2, "a"));
    std::vector<std::pair<std::shared_ptr<StmtNode>, std::string>> args{
        {stmt1, "a"}, {stmt2, "a"}};
    testModifiesAdaptation(args);
  }

  SECTION("Empty modifies") {
    std::vector<std::pair<std::shared_ptr<StmtNode>, std::string>> args{};
    testModifiesAdaptation(args);
  }

  SECTION("Modifies(1, a) Modifies(2,a) Modifies(3, 123)") {
    std::shared_ptr<StmtNode> stmt1 =
        std::static_pointer_cast<StmtNode>(std::make_shared<ReadNode>(1, "a"));
    std::shared_ptr<StmtNode> stmt2 =
        std::static_pointer_cast<StmtNode>(std::make_shared<ReadNode>(2, "a"));
    std::shared_ptr<StmtNode> stmt3 = std::static_pointer_cast<StmtNode>(
        std::make_shared<ReadNode>(3, "123"));
    std::vector<std::pair<std::shared_ptr<StmtNode>, std::string>> args{
        {stmt1, "a"}, {stmt2, "a"}, {stmt3, "123"}};
    testModifiesAdaptation(args);
  }
}
