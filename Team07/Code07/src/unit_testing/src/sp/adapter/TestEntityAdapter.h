#pragma once
#include "catch.hpp"
#include "sp/extractor_adapter/adapters/EntityAdapterProxy.h"
#include "sp/helper.h"
#include "sp/node/stmt_nodes/ReadNode.h"
#include "stubs/pkb/PKBStorageWriteAPI.h"

using namespace SP;
using namespace PKB;

inline void testEntityAdapter(
    std::vector<std::shared_ptr<ProcedureNode>> procedures,
    std::vector<std::shared_ptr<ReadNode>> reads,
    std::vector<std::shared_ptr<PrintNode>> prints,
    std::vector<std::shared_ptr<CallNode>> calls,
    std::vector<std::shared_ptr<WhileNode>> whiles,
    std::vector<std::shared_ptr<IfNode>> ifs,
    std::vector<std::shared_ptr<AssignNode>> assigns,
    std::unordered_set<std::string> expectedProcs,
    std::unordered_set<std::string> expectedVars,
    std::unordered_set<std::string> expectedConsts,
    std::unordered_set<int> expectedReads,
    std::unordered_set<int> expectedPrints,
    std::unordered_set<int> expectedCalls,
    std::unordered_set<int> expectedWhiles,
    std::unordered_set<int> expectedAssigns,
    std::unordered_set<int> expectedIfs,
    std::unordered_map<std::string,
                       std::vector<std::pair<std::vector<std::string>, int>>>
        expectedPattern) {
  std::shared_ptr<PKBStorageWriteStub> pkb =
      std::make_shared<PKBStorageWriteStub>();
  EntityAdapterProxy adapterProxy(pkb);
  adapterProxy.adapt(assigns);
  adapterProxy.adapt(calls);
  adapterProxy.adapt(ifs);
  adapterProxy.adapt(prints);
  adapterProxy.adapt(procedures);
  adapterProxy.adapt(reads);
  adapterProxy.adapt(whiles);

  REQUIRE(expectedProcs == pkb->procedureStorage);
  REQUIRE(expectedVars == pkb->variableStorage);
  REQUIRE(expectedConsts == pkb->constantStorage);
  REQUIRE(expectedReads == pkb->readStorage);
  REQUIRE(expectedPrints == pkb->printStorage);
  REQUIRE(expectedCalls == pkb->callStorage);
  REQUIRE(expectedWhiles == pkb->whileStorage);
  REQUIRE(expectedAssigns == pkb->assignStorage);
  REQUIRE(expectedIfs == pkb->ifStorage);
  REQUIRE(expectedPattern == pkb->assignPatternStorage);
}

inline  // Function to generate a random string of a given length
    std::string
    generateRandomString(int length) {
  const std::string charset =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  std::string randomString;

  for (int i = 0; i < length; ++i) {
    int randomIndex = std::rand() % charset.size();
    randomString += charset[randomIndex];
  }

  return randomString;
}

// Function to generate a vector of random strings
inline std::vector<std::string> generateRandomStringVector(int n,
                                                           int stringLength) {
  std::vector<std::string> randomStrings;
  std::srand(static_cast<unsigned int>(
      std::time(nullptr)));  // Seed the random number generator

  for (int i = 0; i < n; ++i) {
    std::string randomString = generateRandomString(stringLength);
    randomStrings.push_back(randomString);
  }

  return randomStrings;
}

// Function to generate a vector of random integers
inline std::vector<int> generateRandomIntVector(int n, int min, int max) {
  std::vector<int> randomInts;
  std::srand(static_cast<unsigned int>(
      std::time(nullptr)));  // Seed the random number generator

  for (int i = 0; i < n; ++i) {
    int randomInt = min + (std::rand() % (max - min + 1));
    randomInts.push_back(randomInt);
  }

  return randomInts;
}

// function to generate a vector of sets with numElements elements
inline std::vector<std::unordered_set<std::string>> generateXSets(
    int numSets, int numElements) {
  std::vector<std::unordered_set<std::string>> sets;
  for (int i = 0; i < numSets; i++) {
    std::vector<std::string> vec = generateRandomStringVector(numElements, 5);
    sets.push_back(std::unordered_set<std::string>{vec.begin(), vec.end()});
  }
  return sets;
};

inline void unionSets(std::vector<std::unordered_set<std::string>> vecOfSets,
                      std::unordered_set<std::string>& target) {
  for (auto& set : vecOfSets) {
    target.merge(set);
  }
};
