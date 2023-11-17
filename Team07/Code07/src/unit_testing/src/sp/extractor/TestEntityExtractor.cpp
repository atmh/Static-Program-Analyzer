#include "catch.hpp"
#include "sp/adapter/TestEntityAdapter.h"
#include "sp/design_extractor/extractors/EntityExtractor.h"
#include "sp/extractor_adapter/ExtractorAdapter.h"
#include "sp/helper.h"
#include "stubs/pkb/PKBStorageWriteAPI.h"

using namespace SP;
using namespace PKB;

class EntityAdapterFactoryStub : public EntityAdapterProxy {
 public:
  EntityAdapterFactoryStub(
      const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
      : EntityAdapterProxy(pkb) {}
};

template <typename NodeType, typename MemFuncPtrType>
void visitAndExtract(std::vector<std::shared_ptr<NodeType>> nodes,
                     MemFuncPtrType memFnPtr, EntityExtractor& extractor) {
  for (auto& node : nodes) {
    (extractor.*memFnPtr)(node);
  }
}
void createNodesAndTestExtraction(int numProcedures, int numReads,
                                  int numPrints, int numCalls, int numWhiles,
                                  int numIfs, int numAssigns) {
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

  std::shared_ptr<PKB::PKBStorageWriteInterface> pkb =
      std::make_shared<PKB::PKBStorageWriteStub>();

  EntityExtractor extractor{EntityAdapterFactoryStub{pkb}};

  visitAndExtract(procedures, &EntityExtractor::visitProcedure, extractor);
  visitAndExtract(reads, &EntityExtractor::visitRead, extractor);
  visitAndExtract(prints, &EntityExtractor::visitPrint, extractor);
  visitAndExtract(calls, &EntityExtractor::visitCall, extractor);
  visitAndExtract(whiles, &EntityExtractor::visitWhile, extractor);
  visitAndExtract(ifs, &EntityExtractor::visitIf, extractor);
  visitAndExtract(assigns, &EntityExtractor::visitAssign, extractor);

  REQUIRE(procedures == extractor.procedures);
  REQUIRE(reads == extractor.reads);
  REQUIRE(prints == extractor.prints);
  REQUIRE(calls == extractor.calls);
  REQUIRE(whiles == extractor.whiles);
  REQUIRE(ifs == extractor.ifs);
  REQUIRE(assigns == extractor.assigns);
}

TEST_CASE("Test entity extractor") {
  SECTION("Extract 0 nodes") {
    createNodesAndTestExtraction(0, 0, 0, 0, 0, 0, 0);
  }

  SECTION("Extract 1 procedure") {
    createNodesAndTestExtraction(1, 0, 0, 0, 0, 0, 0);
  }

  SECTION("Extract 1 read") {
    createNodesAndTestExtraction(0, 1, 0, 0, 0, 0, 0);
  }

  SECTION("Extract 1 print") {
    createNodesAndTestExtraction(0, 0, 1, 0, 0, 0, 0);
  }

  SECTION("Extract 1 call") {
    createNodesAndTestExtraction(0, 0, 0, 1, 0, 0, 0);
  }

  SECTION("Extract 1 while") {
    createNodesAndTestExtraction(0, 0, 0, 0, 1, 0, 0);
  }

  SECTION("Extract 1 if") {
    createNodesAndTestExtraction(0, 0, 0, 0, 0, 1, 0);
  }

  SECTION("Extract 1 assign") {
    createNodesAndTestExtraction(0, 0, 0, 0, 0, 0, 1);
  }

  SECTION("Extract 100 procedure") {
    createNodesAndTestExtraction(100, 0, 0, 0, 0, 0, 0);
  }

  SECTION("Extract 100 read") {
    createNodesAndTestExtraction(0, 100, 0, 0, 0, 0, 0);
  }

  SECTION("Extract 100 print") {
    createNodesAndTestExtraction(0, 0, 100, 0, 0, 0, 0);
  }

  SECTION("Extract 100 call") {
    createNodesAndTestExtraction(0, 0, 0, 100, 0, 0, 0);
  }

  SECTION("Extract 100 while") {
    createNodesAndTestExtraction(0, 0, 0, 0, 100, 0, 0);
  }

  SECTION("Extract 100 if") {
    createNodesAndTestExtraction(0, 0, 0, 0, 0, 100, 0);
  }

  SECTION("Extract 100 assign") {
    createNodesAndTestExtraction(0, 0, 0, 0, 0, 0, 100);
  }

  SECTION("Extract 12 nodes for all types") {
    createNodesAndTestExtraction(12, 12, 12, 12, 12, 12, 12);
  }

  SECTION("Extracted 123 nodes for all types") {
    createNodesAndTestExtraction(123, 123, 123, 123, 123, 123, 123);
  }
}
