#include "TestEntityAdapter.h"

#include "catch.hpp"

auto makeExpectedPattern =
    [](std ::vector<std ::shared_ptr<AssignNode>> assigns) {
      std::unordered_map<std::string,
                         std::vector<std::pair<std::vector<std::string>, int>>>
          expectedPattern{};

      for (const auto& assign : assigns) {
        std::pair<std::vector<std::string>, int> pairToStore =
            std::make_pair(assign->postfix, assign->stmtNo);
        expectedPattern[assign->name].push_back(pairToStore);
      }
      return expectedPattern;
    };

void createNodesAndTest(int numProcedures, int numReads, int numPrints,
                        int numCalls, int numWhiles, int numIfs,
                        int numAssigns) {
  std::vector<std::string> procedureNames =
      generateRandomStringVector(numProcedures, 5);
  auto procedures = makeProcedureNodes(procedureNames);
  REQUIRE(procedures.size() == numProcedures);

  std::vector<std::string> readVars = generateRandomStringVector(numReads, 5);
  std::vector<int> readStmtNos = generateRandomIntVector(numReads, 1, 200);
  auto reads = makeNodes<ReadNode>(readStmtNos, readVars);
  REQUIRE(reads.size() == numReads);

  std::vector<std::string> printVars = generateRandomStringVector(numPrints, 5);
  std::vector<int> printStmtNos = generateRandomIntVector(numPrints, 1, 200);
  auto prints = makeNodes<PrintNode>(printStmtNos, printVars);
  REQUIRE(prints.size() == numPrints);

  std::vector<std::string> callVars = generateRandomStringVector(numCalls, 5);
  std::vector<int> callStmtNos = generateRandomIntVector(numCalls, 1, 200);
  auto calls = makeNodes<CallNode>(callStmtNos, callVars);
  REQUIRE(calls.size() == numCalls);

  std::vector<int> whilesStmtNos = generateRandomIntVector(numWhiles, 1, 200);
  std::vector<std::unordered_set<std::string>> whileVars =
      generateXSets(numWhiles, 3);
  std::vector<std::unordered_set<std::string>> whileCons =
      generateXSets(numWhiles, 3);
  auto whiles = makeWhileNodes(whilesStmtNos, whileVars, whileCons);
  REQUIRE(whiles.size() == numWhiles);

  std::vector<int> ifStmtNos = generateRandomIntVector(numIfs, 1, 200);
  std::vector<std::unordered_set<std::string>> ifVars =
      generateXSets(numIfs, 3);
  std::vector<std::unordered_set<std::string>> ifCons =
      generateXSets(numIfs, 3);
  auto ifs = makeIfNodes(ifStmtNos, ifVars, ifCons);
  REQUIRE(ifs.size() == numIfs);

  std::vector<int> assignsStmtNos = generateRandomIntVector(numAssigns, 1, 200);
  std::vector<std::string> assignNames =
      generateRandomStringVector(numAssigns, 5);
  std::vector<std::unordered_set<std::string>> assignVars =
      generateXSets(numAssigns, 3);
  std::vector<std::unordered_set<std::string>> assignCons =
      generateXSets(numAssigns, 3);
  auto assigns =
      makeAssignNodes(assignsStmtNos, assignNames, assignVars, assignCons);
  REQUIRE(assigns.size() == numAssigns);

  std::unordered_set<std::string> expectedVars{};
  unionSets(whileVars, expectedVars);
  unionSets(ifVars, expectedVars);
  unionSets(assignVars, expectedVars);
  expectedVars.insert(assignNames.begin(), assignNames.end());
  expectedVars.insert(readVars.begin(), readVars.end());
  expectedVars.insert(printVars.begin(), printVars.end());

  std::unordered_set<std::string> expectedConsts{};
  unionSets(whileCons, expectedConsts);
  unionSets(ifCons, expectedConsts);
  unionSets(assignCons, expectedConsts);

  std::unordered_set<std::string> expectedProcs{procedureNames.begin(),
                                                procedureNames.end()};
  std::unordered_set<int> expectedReads{readStmtNos.begin(), readStmtNos.end()};
  std::unordered_set<int> expectedPrints{printStmtNos.begin(),
                                         printStmtNos.end()};
  std::unordered_set<int> expectedCalls{callStmtNos.begin(), callStmtNos.end()};
  std::unordered_set<int> expectedWhiles{whilesStmtNos.begin(),
                                         whilesStmtNos.end()};
  std::unordered_set<int> expectedAssigns{assignsStmtNos.begin(),
                                          assignsStmtNos.end()};
  std::unordered_set<int> expectedIfs{ifStmtNos.begin(), ifStmtNos.end()};
  auto expectedPattern = makeExpectedPattern(assigns);

  testEntityAdapter(procedures, reads, prints, calls, whiles, ifs, assigns,
                    expectedProcs, expectedVars, expectedConsts, expectedReads,
                    expectedPrints, expectedCalls, expectedWhiles,
                    expectedAssigns, expectedIfs, expectedPattern);
}

TEST_CASE("Basic Entity Adapter Test") {
  SECTION("Extracted no nodes") {
    createNodesAndTest(0, 0, 0, 0, 0, 0, 0);
  }

  SECTION("Extracted 1 procedure") {
    createNodesAndTest(1, 0, 0, 0, 0, 0, 0);
  }

  SECTION("Extracted 1 read") {
    createNodesAndTest(0, 1, 0, 0, 0, 0, 0);
  }

  SECTION("Extracted 1 print") {
    createNodesAndTest(0, 0, 1, 0, 0, 0, 0);
  }

  SECTION("Extracted 1 call") {
    createNodesAndTest(0, 0, 0, 1, 0, 0, 0);
  }

  SECTION("Extracted 1 while") {
    createNodesAndTest(0, 0, 0, 0, 1, 0, 0);
  }

  SECTION("Extracted 1 if") {
    createNodesAndTest(0, 0, 0, 0, 0, 1, 0);
  }

  SECTION("Extracted 1 assign") {
    createNodesAndTest(0, 0, 0, 0, 0, 0, 1);
  }

  SECTION("Extracted 100 procedure") {
    createNodesAndTest(100, 0, 0, 0, 0, 0, 0);
  }

  SECTION("Extracted 100 read") {
    createNodesAndTest(0, 100, 0, 0, 0, 0, 0);
  }

  SECTION("Extracted 100 print") {
    createNodesAndTest(0, 0, 100, 0, 0, 0, 0);
  }

  SECTION("Extracted 100 call") {
    createNodesAndTest(0, 0, 0, 100, 0, 0, 0);
  }

  SECTION("Extracted 100 while") {
    createNodesAndTest(0, 0, 0, 0, 100, 0, 0);
  }

  SECTION("Extracted 100 if") {
    createNodesAndTest(0, 0, 0, 0, 0, 100, 0);
  }

  SECTION("Extracted 100 assign") {
    createNodesAndTest(0, 0, 0, 0, 0, 0, 100);
  }

  SECTION("Extracted 5 nodes for all types") {
    createNodesAndTest(5, 5, 5, 5, 5, 5, 5);
  }

  SECTION("Extracted 100 nodes for all types") {
    createNodesAndTest(100, 100, 100, 100, 100, 100, 100);
  }
}
