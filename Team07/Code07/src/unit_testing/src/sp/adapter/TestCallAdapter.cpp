#include "catch.hpp"
#include "sp//node/ProcedureNode.h"
#include "sp/extractor_adapter/adapters/CallAdapter.h"
#include "stubs/pkb/PKBStorageWriteAPI.h"

using namespace SP;

void testCallAdaptation(
    std::vector<
        std::pair<std::shared_ptr<ProcedureNode>, std::shared_ptr<CallNode>>>
        args) {
  std::shared_ptr<PKB::PKBStorageWriteStub> pkb =
      std::make_shared<PKB::PKBStorageWriteStub>();

  std::shared_ptr<CallAdapter> adapter = std::make_shared<CallAdapter>(pkb);

  std::unordered_map<std::string, std::unordered_set<std::string>> expected;

  for (const auto& pair : args) {
    expected[pair.first->name].insert(pair.second->name);
  }

  adapter->adapt(args);

  auto res = pkb->callsStorage;
  REQUIRE(expected == res);
}

TEST_CASE("Test Call Adapter") {
  SECTION("Empty Calls") {
    std::vector<
        std::pair<std::shared_ptr<ProcedureNode>, std::shared_ptr<CallNode>>>
        args;

    testCallAdaptation(args);
  }

  SECTION("Calls(proc1, proc2)") {
    std::vector<
        std::pair<std::shared_ptr<ProcedureNode>, std::shared_ptr<CallNode>>>
        args;

    auto proc1 = std::make_shared<ProcedureNode>(
        "proc1", std::vector<std::shared_ptr<Node>>{});
    auto call1 = std::make_shared<CallNode>(1, "proc2");

    args.push_back(std::make_pair(proc1, call1));

    testCallAdaptation(args);
  }

  SECTION("Calls(proc1, proc2), Calls(proc2, proc3), Calls(proc3, proc4)") {
    std::vector<
        std::pair<std::shared_ptr<ProcedureNode>, std::shared_ptr<CallNode>>>
        args;
    auto proc1 = std::make_shared<ProcedureNode>(
        "proc1", std::vector<std::shared_ptr<Node>>{});
    auto call1 = std::make_shared<CallNode>(1, "proc2");
    auto proc2 = std::make_shared<ProcedureNode>(
        "proc2", std::vector<std::shared_ptr<Node>>{});
    auto call2 = std::make_shared<CallNode>(1, "proc3");
    auto proc3 = std::make_shared<ProcedureNode>(
        "proc3", std::vector<std::shared_ptr<Node>>{});
    auto call3 = std::make_shared<CallNode>(1, "proc4");
    args.push_back(std::make_pair(proc1, call1));
    args.push_back(std::make_pair(proc2, call2));
    args.push_back(std::make_pair(proc3, call3));

    testCallAdaptation(args);
  }

  SECTION("Calls(proc1, proc2), Calls(proc1, proc3), Calls(proc1, proc4)") {
    std::vector<
        std::pair<std::shared_ptr<ProcedureNode>, std::shared_ptr<CallNode>>>
        args;
    auto proc1 = std::make_shared<ProcedureNode>(
        "proc1", std::vector<std::shared_ptr<Node>>{});
    auto call1 = std::make_shared<CallNode>(1, "proc2");
    auto call2 = std::make_shared<CallNode>(1, "proc3");
    auto call3 = std::make_shared<CallNode>(1, "proc4");
    args.push_back(std::make_pair(proc1, call1));
    args.push_back(std::make_pair(proc1, call2));
    args.push_back(std::make_pair(proc1, call3));

    testCallAdaptation(args);
  }

  SECTION(
      "Calls(proc1, proc2), Calls(proc1, proc3), Calls(proc1, proc4), "
      "Calls(proc2, proc3), Calls(proc2, proc4), Calls(proc3, proc4)") {
    std::vector<
        std::pair<std::shared_ptr<ProcedureNode>, std::shared_ptr<CallNode>>>
        args;
    auto proc1 = std::make_shared<ProcedureNode>(
        "proc1", std::vector<std::shared_ptr<Node>>{});
    auto call1 = std::make_shared<CallNode>(1, "proc2");
    auto call2 = std::make_shared<CallNode>(1, "proc3");
    auto call3 = std::make_shared<CallNode>(1, "proc4");
    auto proc2 = std::make_shared<ProcedureNode>(
        "proc2", std::vector<std::shared_ptr<Node>>{});
    auto call4 = std::make_shared<CallNode>(1, "proc3");
    auto call5 = std::make_shared<CallNode>(1, "proc4");
    auto proc3 = std::make_shared<ProcedureNode>(
        "proc3", std::vector<std::shared_ptr<Node>>{});
    auto call6 = std::make_shared<CallNode>(1, "proc4");
    args.push_back(std::make_pair(proc1, call1));
    args.push_back(std::make_pair(proc1, call2));
    args.push_back(std::make_pair(proc1, call3));
    args.push_back(std::make_pair(proc2, call4));
    args.push_back(std::make_pair(proc2, call5));
    args.push_back(std::make_pair(proc3, call6));

    testCallAdaptation(args);
  }

  SECTION(
      "Calls(proc1, proc2), Calls(proc1, proc3), Calls(proc1, proc4), "
      "Calls(proc2, proc3), Calls(proc2, proc4), Calls(proc3, proc4), "
      "Calls(proc4, proc1)") {
    std::vector<
        std::pair<std::shared_ptr<ProcedureNode>, std::shared_ptr<CallNode>>>
        args;
    auto proc1 = std::make_shared<ProcedureNode>(
        "proc1", std::vector<std::shared_ptr<Node>>{});
    auto call1 = std::make_shared<CallNode>(1, "proc2");
    auto call2 = std::make_shared<CallNode>(1, "proc3");
    auto call3 = std::make_shared<CallNode>(1, "proc4");
    auto proc2 = std::make_shared<ProcedureNode>(
        "proc2", std::vector<std::shared_ptr<Node>>{});
    auto call4 = std::make_shared<CallNode>(1, "proc3");
    auto call5 = std::make_shared<CallNode>(1, "proc4");
    auto proc3 = std::make_shared<ProcedureNode>(
        "proc3", std::vector<std::shared_ptr<Node>>{});
    auto call6 = std::make_shared<CallNode>(1, "proc4");
    auto proc4 = std::make_shared<ProcedureNode>(
        "proc4", std::vector<std::shared_ptr<Node>>{});
    auto call7 = std::make_shared<CallNode>(1, "proc1");
    args.push_back(std::make_pair(proc1, call1));
    args.push_back(std::make_pair(proc1, call2));
    args.push_back(std::make_pair(proc1, call3));
    args.push_back(std::make_pair(proc2, call4));
    args.push_back(std::make_pair(proc2, call5));
    args.push_back(std::make_pair(proc3, call6));
    args.push_back(std::make_pair(proc4, call7));

    testCallAdaptation(args);
  }

  SECTION(
      "Calls(proc1, proc2), Calls(proc1, proc3), Calls(proc1, proc4), "
      "Calls(proc2, proc3), Calls(proc2, proc4), Calls(proc3, proc4), "
      "Calls(proc4, proc1), Calls(proc4, proc2), Calls(proc4, proc3)") {
    std::vector<
        std::pair<std::shared_ptr<ProcedureNode>, std::shared_ptr<CallNode>>>
        args;
    auto proc1 = std::make_shared<ProcedureNode>(
        "proc1", std::vector<std::shared_ptr<Node>>{});
    auto call1 = std::make_shared<CallNode>(1, "proc2");
    auto call2 = std::make_shared<CallNode>(1, "proc3");
    auto call3 = std::make_shared<CallNode>(1, "proc4");
    auto proc2 = std::make_shared<ProcedureNode>(
        "proc2", std::vector<std::shared_ptr<Node>>{});
    auto call4 = std::make_shared<CallNode>(1, "proc3");
    auto call5 = std::make_shared<CallNode>(1, "proc4");
    auto proc3 = std::make_shared<ProcedureNode>(
        "proc3", std::vector<std::shared_ptr<Node>>{});
    auto call6 = std::make_shared<CallNode>(1, "proc4");
    auto proc4 = std::make_shared<ProcedureNode>(
        "proc4", std::vector<std::shared_ptr<Node>>{});
    auto call7 = std::make_shared<CallNode>(1, "proc1");
    auto call8 = std::make_shared<CallNode>(1, "proc2");
    auto call9 = std::make_shared<CallNode>(1, "proc3");
    args.push_back(std::make_pair(proc1, call1));
    args.push_back(std::make_pair(proc1, call2));
    args.push_back(std::make_pair(proc1, call3));
    args.push_back(std::make_pair(proc2, call4));
    args.push_back(std::make_pair(proc2, call5));
    args.push_back(std::make_pair(proc3, call6));
    args.push_back(std::make_pair(proc4, call7));
    args.push_back(std::make_pair(proc4, call8));
    args.push_back(std::make_pair(proc4, call9));

    testCallAdaptation(args);
  }
}
