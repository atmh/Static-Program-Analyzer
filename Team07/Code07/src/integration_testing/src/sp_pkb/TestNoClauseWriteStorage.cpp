//
// Created by Volunteer The on 22/9/23.
//
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "catch.hpp"
#include "pkb/PKBStorageAPI.h"
#include "pkb/PKBStorageWriteAPI.h"
#include "sp/SPManager.h"

using namespace PKB;

TEST_CASE("Integration test for populating no clause storage") {
  std::string testInput =
      "procedure one {\n"
      "   a = 15;\n"
      "   call two;\n"
      "   print d;\n"
      "   read e;\n"
      "   if(a == b) then {\n"
      "       f = 20;\n"
      "       call three;\n"
      "       print i;\n"
      "       read j;\n"
      "   } else {\n"
      "       k = 30;\n"
      "       call four;\n"
      "       print n;\n"
      "       read o;\n"
      "   }"
      "   while (a == b) {\n"
      "       p = 45;\n"
      "       call five;\n"
      "       print s;\n"
      "       read t;\n"
      "   }\n"
      "}\n"
      "procedure two {\n"
      "   u = 10;"
      "}\n"
      "procedure three {\n"
      "   v = 15;"
      "}\n"
      "procedure four {\n"
      "   w = 20;\n"
      "}\n"
      "procedure five {\n"
      "   x = 25;\n"
      "}\n";
  ;

  std::string testFileName = "./testFile.txt";
  std::ofstream testFile;
  testFile.open(testFileName);
  testFile << testInput;
  testFile.close();

  std::shared_ptr<PKBStorageAPI> pkbStorageAPI =
      std::make_shared<PKBStorageAPI>();
  std::shared_ptr<PKBStorageWriteInterface> pkbWrite =
      pkbStorageAPI->getWriteStorage();
  std::shared_ptr<PKBStorageReadInterface> pkbRead =
      pkbStorageAPI->getReadStorage();
  SP::SPManager sourceManager(pkbWrite);

  const auto& processedStorage = pkbRead;
  sourceManager.process(testFileName);

  SECTION("test all entities") {
    SECTION("test int entities") {
      auto expectedAssigns =
          std::unordered_set<int>{1, 6, 10, 15, 19, 20, 21, 22};
      auto expectedPrint = std::unordered_set<int>{3, 8, 12, 17};
      auto expectedCalls = std::unordered_set<int>{2, 7, 11, 16};
      auto expectedReads = std::unordered_set<int>{4, 9, 13, 18};
      auto expectedWhiles = std::unordered_set<int>{14};
      auto expectedIfs = std::unordered_set<int>{5};
      auto expectedStmts =
          std::unordered_set<int>{1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
                                  12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22};
      REQUIRE(processedStorage->getAssigns() == expectedAssigns);
      REQUIRE(processedStorage->getReads() == expectedReads);
      REQUIRE(processedStorage->getCalls() == expectedCalls);
      REQUIRE(processedStorage->getPrints() == expectedPrint);
      REQUIRE(processedStorage->getWhiles() == expectedWhiles);
      REQUIRE(processedStorage->getIfs() == expectedIfs);
      REQUIRE(processedStorage->getStmts() == expectedStmts);
    }

    SECTION("test string entities") {
      auto expectedProcedures = std::unordered_set<std::string>{
          "one", "two", "three", "four", "five"};
      auto expectedVariables = std::unordered_set<std::string>{
          "a", "b", "d", "e", "f", "i", "j", "k", "n",
          "o", "p", "s", "t", "u", "v", "w", "x"};
      auto expectedReadVariables = std::unordered_set<std::string>{
          "a", "b", "d", "e", "f", "i", "j", "k", "n",
          "o", "p", "s", "t", "u", "v", "w", "x"};
      REQUIRE(processedStorage->getProcedures() == expectedProcedures);
      REQUIRE(processedStorage->getVariables() == expectedVariables);
      REQUIRE(processedStorage->getVariables() == expectedReadVariables);
    }
  }

  SECTION("test call secondary fields data calls") {
    std::unordered_map<int, std::string> secondaryFieldMapping = {
        {2, "two"}, {7, "three"}, {11, "four"}, {16, "five"}};
    REQUIRE(processedStorage->getCallProcName(2) ==
            secondaryFieldMapping.at(2));
    REQUIRE(processedStorage->getCallProcName(7) ==
            secondaryFieldMapping.at(7));
    REQUIRE(processedStorage->getCallProcName(11) ==
            secondaryFieldMapping.at(11));
    REQUIRE(processedStorage->getCallProcName(16) ==
            secondaryFieldMapping.at(16));
  }

  SECTION("test print secondary fields data calls") {
    std::unordered_map<int, std::string> secondaryFieldMapping = {
        {3, "d"}, {8, "i"}, {12, "n"}, {17, "s"}};
    REQUIRE(processedStorage->getPrintVarName(3) ==
            secondaryFieldMapping.at(3));
    REQUIRE(processedStorage->getPrintVarName(8) ==
            secondaryFieldMapping.at(8));
    REQUIRE(processedStorage->getPrintVarName(12) ==
            secondaryFieldMapping.at(12));
    REQUIRE(processedStorage->getPrintVarName(17) ==
            secondaryFieldMapping.at(17));
  }

  SECTION("test read secondary fields data calls") {
    std::unordered_map<int, std::string> secondaryFieldMapping = {
        {4, "e"}, {9, "j"}, {13, "o"}, {18, "t"}};
    REQUIRE(processedStorage->getReadVarName(4) == secondaryFieldMapping.at(4));
    REQUIRE(processedStorage->getReadVarName(9) == secondaryFieldMapping.at(9));
    REQUIRE(processedStorage->getReadVarName(13) ==
            secondaryFieldMapping.at(13));
    REQUIRE(processedStorage->getReadVarName(18) ==
            secondaryFieldMapping.at(18));
  }
  std::filesystem::remove(testFileName);
}
