//
// Created by Volunteer The on 19/9/23.
//
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "TestSPA.h"
#include "catch.hpp"
#include "pkb/PKBStorageAPI.h"
#include "pkb/PKBStorageWriteAPI.h"
#include "sp/SPManager.h"

using namespace PKB;

TEST_CASE("test assign pattern storage") {
  std::shared_ptr<PKBStorageAPI> pkbStorageAPI =
      std::make_shared<PKBStorageAPI>();
  std::shared_ptr<PKBStorageWriteInterface> pkbWrite =
      pkbStorageAPI->getWriteStorage();
  std::shared_ptr<PKBStorageReadInterface> pkbRead =
      pkbStorageAPI->getReadStorage();

  SP::SPManager sourceManager(pkbWrite);
  TestSPA spa;
  std::shared_ptr<PKBStorageAPI> pkbStorageAPISpa = spa.pkbStorageAPI;
  std::shared_ptr<PKBStorageWriteInterface> pkbWriteSpa =
      pkbStorageAPISpa->getWriteStorage();
  std::shared_ptr<PKBStorageReadInterface> pkbReadSpa =
      pkbStorageAPISpa->getReadStorage();

  const auto& processedStorage = pkbRead;
  const auto& processedStorageSpa = pkbReadSpa;

  REQUIRE_FALSE(pkbReadSpa == pkbRead);

  auto actualMap = processedStorage->getAssignPatterns();
  auto actualMapSpa = processedStorageSpa->getAssignPatterns();

  REQUIRE(actualMap == actualMapSpa);

  SECTION("negative tests") {
    SECTION("Test syntax errors") {
      std::string testInput =
          "procedure a {\n"
          "    a = (b ++ c) * d;\n"
          "}";
      std::string testFileName = "./testFileOne.txt";
      std::ofstream testFile;
      testFile.open(testFileName);
      testFile << testInput;
      testFile.close();

      REQUIRE_THROWS_MATCHES(
          sourceManager.process(testFileName), Common::ShuntingYardException,
          Catch::Matchers::Message(SHUNTING_YARD_INVALID_EXPR));
      REQUIRE_THROWS_MATCHES(
          spa.process(testFileName), Common::ShuntingYardException,
          Catch::Matchers::Message(SHUNTING_YARD_INVALID_EXPR));

      std::filesystem::remove(testFileName);
    }

    SECTION("Test Procedure with no statement") {
      std::string testInput =
          "procedure a {\n"
          "}";
      std::string testFileName = "./testFile.txt";
      std::ofstream testFile;
      testFile.open(testFileName);
      testFile << testInput;
      testFile.close();

      REQUIRE_THROWS_MATCHES(sourceManager.process(testFileName),
                             SP::SourceParserException,
                             Catch::Matchers::Message(SP::PARSER_NO_STMT));
      REQUIRE_THROWS_MATCHES(spa.process(testFileName),
                             SP::SourceParserException,
                             Catch::Matchers::Message(SP::PARSER_NO_STMT));

      std::filesystem::remove(testFileName);
    }
  }

  SECTION("Test all operation patterns") {
    std::string testInputOne =
        "procedure one {\n"
        "    a = b + c;\n"
        "    b = b - c;\n"
        "    c = b * c;\n"
        "    d = b / c;\n"
        "    e = b + c - d;\n"
        "    f = b * c / d;\n"
        "    g = b + c * d;\n"
        "    h = b - c / d;\n"
        "    i = b * (c - d);\n"
        "    j = (b + c) / d;\n"
        "    k = (b + c) * ((d - e) + f * g);\n"
        "}";
    std::string testFileName = "./testFileOne.txt";
    std::ofstream testFile;
    testFile.open(testFileName);
    testFile << testInputOne;
    testFile.close();

    REQUIRE(pkbRead->getAssignPatterns().empty());
    REQUIRE(pkbReadSpa->getAssignPatterns().empty());

    sourceManager.process(testFileName);
    spa.process(testFileName);
    actualMap = pkbRead->getAssignPatterns();
    actualMapSpa = pkbReadSpa->getAssignPatterns();

    SECTION("Test single assign pattern store") {
      SECTION("Test plus operation") {
        std::unordered_map<
            std::string, std::vector<std::pair<std::vector<std::string>, int>>>
            expectedMap;
        std::vector<std::pair<std::vector<std::string>, int>> expectedVector;
        std::vector<std::string> expectedPattern =
            std::vector<std::string>{"b", "c", "+"};
        expectedVector.emplace_back(expectedPattern, 1);
        std::string lhs = "a";
        expectedMap[lhs] = expectedVector;
        REQUIRE(actualMap[lhs] == expectedMap[lhs]);
        REQUIRE(actualMapSpa[lhs] == expectedMap[lhs]);
      }
      SECTION("Test minus operation") {
        std::unordered_map<
            std::string, std::vector<std::pair<std::vector<std::string>, int>>>
            expectedMap;
        std::vector<std::pair<std::vector<std::string>, int>> expectedVector;
        std::vector<std::string> expectedPattern =
            std::vector<std::string>{"b", "c", "-"};
        expectedVector.emplace_back(expectedPattern, 2);
        std::string lhs = "b";
        expectedMap[lhs] = expectedVector;
        REQUIRE(actualMap[lhs] == expectedMap[lhs]);
        REQUIRE(actualMapSpa[lhs] == expectedMap[lhs]);
      }
      SECTION("Test multiply operation") {
        std::unordered_map<
            std::string, std::vector<std::pair<std::vector<std::string>, int>>>
            expectedMap;
        std::vector<std::pair<std::vector<std::string>, int>> expectedVector;
        std::vector<std::string> expectedPattern =
            std::vector<std::string>{"b", "c", "*"};
        expectedVector.emplace_back(expectedPattern, 3);
        std::string lhs = "c";
        expectedMap[lhs] = expectedVector;
        REQUIRE(actualMap[lhs] == expectedMap[lhs]);
        REQUIRE(actualMapSpa[lhs] == expectedMap[lhs]);
      }
      SECTION("Test divide operation") {
        std::unordered_map<
            std::string, std::vector<std::pair<std::vector<std::string>, int>>>
            expectedMap;
        std::vector<std::pair<std::vector<std::string>, int>> expectedVector;
        std::vector<std::string> expectedPattern =
            std::vector<std::string>{"b", "c", "/"};
        expectedVector.emplace_back(expectedPattern, 4);
        std::string lhs = "d";
        expectedMap[lhs] = expectedVector;
        REQUIRE(actualMap[lhs] == expectedMap[lhs]);
        REQUIRE(actualMapSpa[lhs] == expectedMap[lhs]);
      }
      std::filesystem::remove(testFileName);
    }
    SECTION("Test order of priority") {
      SECTION("Test plus minus operation") {
        std::unordered_map<
            std::string, std::vector<std::pair<std::vector<std::string>, int>>>
            expectedMap;
        std::vector<std::pair<std::vector<std::string>, int>> expectedVector;
        std::vector<std::string> expectedPattern =
            std::vector<std::string>{"b", "c", "+", "d", "-"};
        expectedVector.emplace_back(expectedPattern, 5);
        std::string lhs = "e";
        expectedMap[lhs] = expectedVector;
        REQUIRE(actualMap[lhs] == expectedMap[lhs]);
        REQUIRE(actualMapSpa[lhs] == expectedMap[lhs]);
      }
      SECTION("Test multiply divide operation") {
        std::unordered_map<
            std::string, std::vector<std::pair<std::vector<std::string>, int>>>
            expectedMap;
        std::vector<std::pair<std::vector<std::string>, int>> expectedVector;
        std::vector<std::string> expectedPattern =
            std::vector<std::string>{"b", "c", "*", "d", "/"};
        expectedVector.emplace_back(expectedPattern, 6);
        std::string lhs = "f";
        expectedMap[lhs] = expectedVector;
        REQUIRE(actualMap[lhs] == expectedMap[lhs]);
        REQUIRE(actualMapSpa[lhs] == expectedMap[lhs]);
      }
      SECTION("Test plus multiply operation") {
        std::unordered_map<
            std::string, std::vector<std::pair<std::vector<std::string>, int>>>
            expectedMap;
        std::vector<std::pair<std::vector<std::string>, int>> expectedVector;
        std::vector<std::string> expectedPattern =
            std::vector<std::string>{"b", "c", "d", "*", "+"};
        expectedVector.emplace_back(expectedPattern, 7);
        std::string lhs = "g";
        expectedMap[lhs] = expectedVector;
        REQUIRE(actualMap[lhs] == expectedMap[lhs]);
        REQUIRE(actualMapSpa[lhs] == expectedMap[lhs]);
      }
      SECTION("Test divide minus operation") {
        std::unordered_map<
            std::string, std::vector<std::pair<std::vector<std::string>, int>>>
            expectedMap;
        std::vector<std::pair<std::vector<std::string>, int>> expectedVector;
        std::vector<std::string> expectedPattern =
            std::vector<std::string>{"b", "c", "d", "/", "-"};
        expectedVector.emplace_back(expectedPattern, 8);
        std::string lhs = "h";
        expectedMap[lhs] = expectedVector;
        REQUIRE(actualMap[lhs] == expectedMap[lhs]);
        REQUIRE(actualMapSpa[lhs] == expectedMap[lhs]);
      }
      SECTION("Test multiply (minus) operation") {
        std::unordered_map<
            std::string, std::vector<std::pair<std::vector<std::string>, int>>>
            expectedMap;
        std::vector<std::pair<std::vector<std::string>, int>> expectedVector;
        std::vector<std::string> expectedPattern =
            std::vector<std::string>{"b", "c", "d", "-", "*"};
        expectedVector.emplace_back(expectedPattern, 9);
        std::string lhs = "i";
        expectedMap[lhs] = expectedVector;
        REQUIRE(actualMap[lhs] == expectedMap[lhs]);
        REQUIRE(actualMapSpa[lhs] == expectedMap[lhs]);
      }
      SECTION("Test divide (plus) operation") {
        std::unordered_map<
            std::string, std::vector<std::pair<std::vector<std::string>, int>>>
            expectedMap;
        std::vector<std::pair<std::vector<std::string>, int>> expectedVector;
        std::vector<std::string> expectedPattern =
            std::vector<std::string>{"b", "c", "+", "d", "/"};
        expectedVector.emplace_back(expectedPattern, 10);
        std::string lhs = "j";
        expectedMap[lhs] = expectedVector;
        REQUIRE(actualMap[lhs] == expectedMap[lhs]);
        REQUIRE(actualMapSpa[lhs] == expectedMap[lhs]);
      }
      SECTION("Test multiple parenthesis operation") {
        std::unordered_map<
            std::string, std::vector<std::pair<std::vector<std::string>, int>>>
            expectedMap;
        std::vector<std::pair<std::vector<std::string>, int>> expectedVector;
        std::vector<std::string> expectedPattern = std::vector<std::string>{
            "b", "c", "+", "d", "e", "-", "f", "g", "*", "+", "*"};
        expectedVector.emplace_back(expectedPattern, 11);
        std::string lhs = "k";
        expectedMap[lhs] = expectedVector;
        REQUIRE(actualMap[lhs] == expectedMap[lhs]);
        REQUIRE(actualMapSpa[lhs] == expectedMap[lhs]);
      }
      std::filesystem::remove(testFileName);
    }
  }

  SECTION("Test multiple assign pattern store") {
    SECTION("Test lhs to single vector entry") {
      std::string testInput =
          "procedure a {\n"
          "    a = (b + c) * d;\n"     // 1
          "    while (a == b) {\n"     // 2
          "       b = (a + b) * c;\n"  // 3
          "       c = c / (a - b);\n"  // 4
          "    }\n"
          "    if (a == b) then{\n"    // 5
          "       d = b * (c - d);\n"  // 6
          "       e = (b + c) / d;\n"  // 7
          "    }  else {\n"
          "       f = (b + c) * ((d - e) + f * g);\n"  // 8
          "    }\n"
          "}\n";
      std::string testFileName = "./testFile.txt";
      std::ofstream testFile;
      testFile.open(testFileName);
      testFile << testInput;
      testFile.close();

      REQUIRE(pkbRead->getAssignPatterns().empty());
      REQUIRE(pkbReadSpa->getAssignPatterns().empty());

      sourceManager.process(testFileName);
      spa.process(testFileName);
      actualMap = pkbRead->getAssignPatterns();
      actualMapSpa = pkbReadSpa->getAssignPatterns();

      std::unordered_map<std::string,
                         std::vector<std::pair<std::vector<std::string>, int>>>
          expectedMap;
      std::vector<std::pair<std::vector<std::string>, int>> expectedVectorOne;
      std::vector<std::pair<std::vector<std::string>, int>> expectedVectorTwo;
      std::vector<std::pair<std::vector<std::string>, int>> expectedVectorThree;
      std::vector<std::pair<std::vector<std::string>, int>> expectedVectorFour;
      std::vector<std::pair<std::vector<std::string>, int>> expectedVectorFive;
      std::vector<std::pair<std::vector<std::string>, int>> expectedVectorSix;
      std::string lhsOne = "a";
      std::string lhsTwo = "b";
      std::string lhsThree = "c";
      std::string lhsFour = "d";
      std::string lhsFive = "e";
      std::string lhsSix = "f";
      std::vector<std::string> expectedPatternOne =
          std::vector<std::string>{"b", "c", "+", "d", "*"};
      expectedVectorOne.emplace_back(expectedPatternOne, 1);
      expectedMap[lhsOne] = expectedVectorOne;
      std::vector<std::string> expectedPatternTwo =
          std::vector<std::string>{"a", "b", "+", "c", "*"};
      expectedVectorTwo.emplace_back(expectedPatternTwo, 3);
      expectedMap[lhsTwo] = expectedVectorTwo;
      std::vector<std::string> expectedPatternThree =
          std::vector<std::string>{"c", "a", "b", "-", "/"};
      expectedVectorThree.emplace_back(expectedPatternThree, 4);
      expectedMap[lhsThree] = expectedVectorThree;
      std::vector<std::string> expectedPatternFour =
          std::vector<std::string>{"b", "c", "d", "-", "*"};
      expectedVectorFour.emplace_back(expectedPatternFour, 6);
      expectedMap[lhsFour] = expectedVectorFour;
      std::vector<std::string> expectedPatternFive =
          std::vector<std::string>{"b", "c", "+", "d", "/"};
      expectedVectorFive.emplace_back(expectedPatternFive, 7);
      expectedMap[lhsFive] = expectedVectorFive;
      std::vector<std::string> expectedPatternSix = std::vector<std::string>{
          "b", "c", "+", "d", "e", "-", "f", "g", "*", "+", "*"};
      expectedVectorSix.emplace_back(expectedPatternSix, 8);
      expectedMap[lhsSix] = expectedVectorSix;

      for (const auto& entry : expectedMap) {
        const std::string& thisLhs = entry.first;
        REQUIRE(actualMap[thisLhs] == expectedMap[thisLhs]);
        REQUIRE(actualMapSpa[thisLhs] == expectedMap[thisLhs]);
      }
      std::filesystem::remove(testFileName);
    }

    SECTION("Test lhs to multiple vector entry") {
      std::string testInput =
          "procedure a {\n"
          "    a = (b + c) * d;\n"     // 1
          "    while (a == b) {\n"     // 2
          "       b = (a + b) * c;\n"  // 3
          "       a = c / (a - b);\n"  // 4
          "    }\n"
          "    if (a == b) then{\n"    // 5
          "       b = b * (c - d);\n"  // 6
          "       a = (b + c) / d;\n"  // 7
          "    }  else {\n"
          "       b = (b + c) * ((d - e) + f * g);\n"  // 8
          "    }\n"
          "}\n";
      std::string testFileName = "./testFile.txt";
      std::ofstream testFile;
      testFile.open(testFileName);
      testFile << testInput;
      testFile.close();

      REQUIRE(pkbRead->getAssignPatterns().empty());
      REQUIRE(pkbReadSpa->getAssignPatterns().empty());

      sourceManager.process(testFileName);
      spa.process(testFileName);
      actualMap = pkbRead->getAssignPatterns();
      actualMapSpa = pkbReadSpa->getAssignPatterns();

      std::unordered_map<std::string,
                         std::vector<std::pair<std::vector<std::string>, int>>>
          expectedMap;
      std::vector<std::pair<std::vector<std::string>, int>> expectedVectorOne;
      std::vector<std::pair<std::vector<std::string>, int>> expectedVectorTwo;
      std::vector<std::pair<std::vector<std::string>, int>> expectedVectorThree;
      std::vector<std::pair<std::vector<std::string>, int>> expectedVectorFour;
      std::vector<std::pair<std::vector<std::string>, int>> expectedVectorFive;
      std::vector<std::pair<std::vector<std::string>, int>> expectedVectorSix;
      std::string lhsOne = "a";
      std::string lhsTwo = "b";
      std::vector<std::string> expectedPatternOne =
          std::vector<std::string>{"b", "c", "+", "d", "*"};
      expectedVectorOne.emplace_back(expectedPatternOne, 1);
      expectedMap[lhsOne] = expectedVectorOne;
      std::vector<std::string> expectedPatternTwo =
          std::vector<std::string>{"a", "b", "+", "c", "*"};
      expectedVectorTwo.emplace_back(expectedPatternTwo, 3);
      expectedMap[lhsTwo] = expectedVectorTwo;
      std::vector<std::string> expectedPatternThree =
          std::vector<std::string>{"c", "a", "b", "-", "/"};
      expectedVectorThree.emplace_back(expectedPatternThree, 4);
      expectedMap[lhsOne].emplace_back(expectedVectorThree[0]);
      std::vector<std::string> expectedPatternFour =
          std::vector<std::string>{"b", "c", "d", "-", "*"};
      expectedVectorFour.emplace_back(expectedPatternFour, 6);
      expectedMap[lhsTwo].emplace_back(expectedVectorFour[0]);
      std::vector<std::string> expectedPatternFive =
          std::vector<std::string>{"b", "c", "+", "d", "/"};
      expectedVectorFive.emplace_back(expectedPatternFive, 7);
      expectedMap[lhsOne].emplace_back(expectedVectorFive[0]);
      std::vector<std::string> expectedPatternSix = std::vector<std::string>{
          "b", "c", "+", "d", "e", "-", "f", "g", "*", "+", "*"};
      expectedVectorSix.emplace_back(expectedPatternSix, 8);
      expectedMap[lhsTwo].emplace_back(expectedVectorSix[0]);

      for (const auto& entry : expectedMap) {
        const std::string& thisLhs = entry.first;
        REQUIRE(actualMap[thisLhs] == expectedMap[thisLhs]);
        REQUIRE(actualMapSpa[thisLhs] == expectedMap[thisLhs]);
      }
      std::filesystem::remove(testFileName);
    }
  }
}

TEST_CASE("test if pattern") {

  std::shared_ptr<PKBStorageAPI> pkbStorageAPI =
      std::make_shared<PKBStorageAPI>();
  std::shared_ptr<PKBStorageWriteInterface> pkbWrite =
      pkbStorageAPI->getWriteStorage();
  std::shared_ptr<PKBStorageReadInterface> pkbRead =
      pkbStorageAPI->getReadStorage();

  SP::SPManager sourceManager(pkbWrite);
  TestSPA spa;
  std::shared_ptr<PKBStorageAPI> pkbStorageAPISpa = spa.pkbStorageAPI;
  std::shared_ptr<PKBStorageWriteInterface> pkbWriteSpa =
      pkbStorageAPISpa->getWriteStorage();
  std::shared_ptr<PKBStorageReadInterface> pkbReadSpa =
      pkbStorageAPISpa->getReadStorage();

  const auto& processedStorage = pkbRead;
  const auto& processedStorageSpa = pkbReadSpa;

  REQUIRE_FALSE(pkbReadSpa == pkbRead);

  auto actualMap = processedStorage->getIfPatterns();
  auto actualMapSpa = processedStorageSpa->getIfPatterns();

  REQUIRE(actualMap == actualMapSpa);

  SECTION("negative tests ifs") {
    SECTION("Test syntax errors") {
      std::string testInput =
          "procedure a {\n"
          "    if {a == 5) then {} else{}\n"
          "}";
      std::string testFileName = "./testFileOne.txt";
      std::ofstream testFile;
      testFile.open(testFileName);
      testFile << testInput;
      testFile.close();

      REQUIRE_THROWS_MATCHES(sourceManager.process(testFileName),
                             Common::SyntaxException,
                             Catch::Matchers::Message(PARSER_SYNTAX_ERROR));
      REQUIRE_THROWS_MATCHES(spa.process(testFileName), Common::SyntaxException,
                             Catch::Matchers::Message(PARSER_SYNTAX_ERROR));

      std::filesystem::remove(testFileName);
    }

    SECTION("Test no statement lists") {
      SECTION("test no statement in if") {
        std::string testInputOne =
            "procedure one {\n"
            "    if (a == 2) then {\n"
            "    } else {"
            "       print x;\n"
            "    }\n"
            "}";
        std::string testFileName = "./testFileOne.txt";
        std::ofstream testFile;
        testFile.open(testFileName);
        testFile << testInputOne;
        testFile.close();

        REQUIRE_THROWS_MATCHES(sourceManager.process(testFileName),
                               SP::SourceParserException,
                               Catch::Matchers::Message(SP::PARSER_NO_STMT));
        REQUIRE_THROWS_MATCHES(spa.process(testFileName),
                               SP::SourceParserException,
                               Catch::Matchers::Message(SP::PARSER_NO_STMT));

        std::filesystem::remove(testFileName);
      }

      SECTION("test no statement in else") {
        std::string testInputOne =
            "procedure one {\n"
            "    if (a == 2) then { \n"
            "       print x; \n"
            "    } else{}\n"
            "}";
        std::string testFileName = "./testFileOne.txt";
        std::ofstream testFile;
        testFile.open(testFileName);
        testFile << testInputOne;
        testFile.close();

        REQUIRE_THROWS_MATCHES(sourceManager.process(testFileName),
                               SP::SourceParserException,
                               Catch::Matchers::Message(SP::PARSER_NO_STMT));
        REQUIRE_THROWS_MATCHES(spa.process(testFileName),
                               SP::SourceParserException,
                               Catch::Matchers::Message(SP::PARSER_NO_STMT));

        std::filesystem::remove(testFileName);
      }
    }
  }

  SECTION("Test single if patterns") {
    std::string testInputOne =
        "procedure one {\n"
        "    if (x == 2) then { \n"
        "       print x; \n"
        "    } else {\n"
        "       read y;\n"
        "    }"
        "}";
    std::string testFileName = "./testFileOne.txt";
    std::ofstream testFile;
    testFile.open(testFileName);
    testFile << testInputOne;
    testFile.close();

    REQUIRE(pkbRead->getIfPatterns().empty());
    REQUIRE(pkbReadSpa->getIfPatterns().empty());

    sourceManager.process(testFileName);
    spa.process(testFileName);
    actualMap = pkbRead->getIfPatterns();
    actualMapSpa = pkbReadSpa->getIfPatterns();

    std::unordered_map<std::string, std::unordered_set<int>> expectedMap;
    expectedMap["x"].insert(1);

    REQUIRE(expectedMap == actualMap);
    REQUIRE(expectedMap == actualMapSpa);
  }

  SECTION("Test multiple if pattern store") {
    SECTION("test non-nested ifs") {
      std::string testInput =
          "procedure a {\n"
          "    if (a == 1) then {\n"  //1
          "       print a;\n"         //2
          "    } else {\n"
          "       read a;\n"  //3
          "    }"
          "    if (1 == 2) then {\n"  //4
          "       c = 4;\n"           //5
          "    } else {\n"
          "       d = 5;\n"  //6
          "    }"
          "    if (b == 2) then {\n"  //7
          "       a = 3;\n"           //8
          "    } else {\n"
          "       a = 5;\n"  //9
          "    }"
          "}\n";
      std::string testFileName = "./testFile.txt";
      std::ofstream testFile;
      testFile.open(testFileName);
      testFile << testInput;
      testFile.close();

      REQUIRE(pkbRead->getIfPatterns().empty());
      REQUIRE(pkbReadSpa->getIfPatterns().empty());

      sourceManager.process(testFileName);
      spa.process(testFileName);
      actualMap = pkbRead->getIfPatterns();
      actualMapSpa = pkbReadSpa->getIfPatterns();

      std::unordered_map<std::string, std::unordered_set<int>> expectedMap;
      expectedMap["a"].insert(1);
      expectedMap["b"].insert(7);

      REQUIRE(actualMap == expectedMap);
      REQUIRE(actualMapSpa == expectedMap);

      std::filesystem::remove(testFileName);
    }
    SECTION("test nested ifs") {
      std::string testInput =
          "procedure a {\n"
          "    if (a == 1) then {\n"     //1
          "       print a;\n"            //2
          "       if (b == 2) then {\n"  //3
          "           c = 4;\n"          //4
          "       } else {\n"
          "           d = 5;"  //5
          "       }\n"
          "    } else {\n"
          "       read a;\n"  //6
          "    }"
          "    if (1 == 2) then {\n"  //7
          "       c = 4;\n"           //8
          "    } else {\n"
          "       if (c > 5) then {\n"  //9
          "           d = 6; \n"        //10
          "       } else {\n"
          "       d = 5;\n"  //11
          "       }"
          "    }"
          "    if (d < 2) then {\n"  //12
          "       a = 3;\n"          //13
          "    } else {\n"
          "       a = 5;\n"  //14
          "    }"
          "}\n";
      std::string testFileName = "./testFile.txt";
      std::ofstream testFile;
      testFile.open(testFileName);
      testFile << testInput;
      testFile.close();

      REQUIRE(pkbRead->getIfPatterns().empty());
      REQUIRE(pkbReadSpa->getIfPatterns().empty());

      sourceManager.process(testFileName);
      spa.process(testFileName);
      actualMap = pkbRead->getIfPatterns();
      actualMapSpa = pkbReadSpa->getIfPatterns();

      std::unordered_map<std::string, std::unordered_set<int>> expectedMap;
      expectedMap["a"].insert(1);
      expectedMap["b"].insert(3);
      expectedMap["c"].insert(9);
      expectedMap["d"].insert(12);

      REQUIRE(actualMap.size() == 4);
      REQUIRE(actualMapSpa.size() == 4);
      REQUIRE(actualMap == expectedMap);
      REQUIRE(actualMapSpa == expectedMap);

      std::filesystem::remove(testFileName);
    }
    SECTION("test multiple values to key ifs") {
      std::string testInput =
          "procedure a {\n"
          "    if (a == 1) then {\n"     //1
          "       print a;\n"            //2
          "       if (a == 2) then {\n"  //3
          "           c = 4;\n"          //4
          "       } else {\n"
          "           d = 5;"  //5
          "       }\n"
          "    } else {\n"
          "       read a;\n"  //6
          "    }"
          "    if (a == 3) then {\n"  //7
          "       c = 4;\n"           //8
          "    } else {\n"
          "       if (a > 5) then {\n"  //9
          "           d = 6; \n"        //10
          "       } else {\n"
          "       d = 5;\n"  //11
          "       }"
          "    }"
          "    if (a < 2) then {\n"  //12
          "       a = 3;\n"          //13
          "    } else {\n"
          "       a = 5;\n"  //14
          "    }"
          "}\n";
      std::string testFileName = "./testFile.txt";
      std::ofstream testFile;
      testFile.open(testFileName);
      testFile << testInput;
      testFile.close();

      REQUIRE(pkbRead->getIfPatterns().empty());
      REQUIRE(pkbReadSpa->getIfPatterns().empty());

      sourceManager.process(testFileName);
      spa.process(testFileName);
      actualMap = pkbRead->getIfPatterns();
      actualMapSpa = pkbReadSpa->getIfPatterns();

      std::unordered_map<std::string, std::unordered_set<int>> expectedMap;
      expectedMap["a"].insert(1);
      expectedMap["a"].insert(3);
      expectedMap["a"].insert(7);
      expectedMap["a"].insert(9);
      expectedMap["a"].insert(12);

      REQUIRE(actualMap.size() == 1);
      REQUIRE(actualMapSpa.size() == 1);
      REQUIRE(actualMap == expectedMap);
      REQUIRE(actualMapSpa == expectedMap);

      std::filesystem::remove(testFileName);
    }
  }
}

TEST_CASE("test while pattern") {

  std::shared_ptr<PKBStorageAPI> pkbStorageAPI =
      std::make_shared<PKBStorageAPI>();
  std::shared_ptr<PKBStorageWriteInterface> pkbWrite =
      pkbStorageAPI->getWriteStorage();
  std::shared_ptr<PKBStorageReadInterface> pkbRead =
      pkbStorageAPI->getReadStorage();

  SP::SPManager sourceManager(pkbWrite);
  TestSPA spa;
  std::shared_ptr<PKBStorageAPI> pkbStorageAPISpa = spa.pkbStorageAPI;
  std::shared_ptr<PKBStorageWriteInterface> pkbWriteSpa =
      pkbStorageAPISpa->getWriteStorage();
  std::shared_ptr<PKBStorageReadInterface> pkbReadSpa =
      pkbStorageAPISpa->getReadStorage();

  const auto& processedStorage = pkbRead;
  const auto& processedStorageSpa = pkbReadSpa;

  REQUIRE_FALSE(pkbReadSpa == pkbRead);

  auto actualMap = processedStorage->getWhilePatterns();
  auto actualMapSpa = processedStorageSpa->getWhilePatterns();

  REQUIRE(actualMap == actualMapSpa);

  SECTION("negative test whiles") {
    SECTION("Test invalid expression") {
      std::string testInput =
          "procedure a {\n"
          "    while ( == 5) {\n"
          "       print x;\n"
          "    }\n"
          "}";
      std::string testFileName = "./testFileOne.txt";
      std::ofstream testFile;
      testFile.open(testFileName);
      testFile << testInput;
      testFile.close();

      REQUIRE_THROWS_MATCHES(
          sourceManager.process(testFileName), Common::ShuntingYardException,
          Catch::Matchers::Message(SHUNTING_YARD_INVALID_EXPR));
      REQUIRE_THROWS_MATCHES(
          spa.process(testFileName), Common::ShuntingYardException,
          Catch::Matchers::Message(SHUNTING_YARD_INVALID_EXPR));

      std::filesystem::remove(testFileName);
    }

    SECTION("Test no statement lists") {

      std::string testInputOne =
          "procedure one {\n"
          "    while (a == 2)  {}\n"
          "}";
      std::string testFileName = "./testFileOne.txt";
      std::ofstream testFile;
      testFile.open(testFileName);
      testFile << testInputOne;
      testFile.close();

      REQUIRE_THROWS_MATCHES(sourceManager.process(testFileName),
                             SP::SourceParserException,
                             Catch::Matchers::Message(SP::PARSER_NO_STMT));
      REQUIRE_THROWS_MATCHES(spa.process(testFileName),
                             SP::SourceParserException,
                             Catch::Matchers::Message(SP::PARSER_NO_STMT));

      std::filesystem::remove(testFileName);
    }
  }

  SECTION("Test single while patterns") {
    std::string testInputOne =
        "procedure one {\n"
        "    while (x == 2) { \n"
        "       print x; \n"
        "    } "
        "}";
    std::string testFileName = "./testFileOne.txt";
    std::ofstream testFile;
    testFile.open(testFileName);
    testFile << testInputOne;
    testFile.close();

    REQUIRE(pkbRead->getIfPatterns().empty());
    REQUIRE(pkbReadSpa->getIfPatterns().empty());

    sourceManager.process(testFileName);
    spa.process(testFileName);
    actualMap = pkbRead->getWhilePatterns();
    actualMapSpa = pkbReadSpa->getWhilePatterns();

    std::unordered_map<std::string, std::unordered_set<int>> expectedMap;
    expectedMap["x"].insert(1);

    REQUIRE(expectedMap == actualMap);
    REQUIRE(expectedMap == actualMapSpa);
  }

  SECTION("Test multiple while pattern store") {
    SECTION("test non-nested ifs") {
      std::string testInput =
          "procedure a {\n"
          "    while (a == 1) {\n"  //1
          "       print a;\n"       //2
          "    }\n"
          "    while (1 == 2) {\n"  //3
          "       c = 4;\n"         //4
          "    } \n"
          "    while (b == 2) {\n"  //5
          "       a = 3;\n"         //6
          "    }\n"
          "}\n";
      std::string testFileName = "./testFile.txt";
      std::ofstream testFile;
      testFile.open(testFileName);
      testFile << testInput;
      testFile.close();

      REQUIRE(pkbRead->getWhilePatterns().empty());
      REQUIRE(pkbReadSpa->getWhilePatterns().empty());

      sourceManager.process(testFileName);
      spa.process(testFileName);
      actualMap = pkbRead->getWhilePatterns();
      actualMapSpa = pkbReadSpa->getWhilePatterns();

      std::unordered_map<std::string, std::unordered_set<int>> expectedMap;
      expectedMap["a"].insert(1);
      expectedMap["b"].insert(5);

      REQUIRE(actualMap == expectedMap);
      REQUIRE(actualMapSpa == expectedMap);

      std::filesystem::remove(testFileName);
    }

    SECTION("test nested whiles") {
      std::string testInput =
          "procedure a {\n"
          "    while (a == 1) {\n"     //1
          "       print a;\n"          //2
          "       while (b == 2) {\n"  //3
          "           c = 4;\n"        //4
          "       }\n"
          "    }\n"
          "    while (1 == 2) {\n"    //5
          "       c = 4;\n"           //6
          "       while (c > 5) {\n"  //7
          "           d = 6;\n"       //8
          "       }\n"
          "    }"
          "    while (d < 2) {\n"  //9
          "       a = 3;\n"        //10
          "    }\n"
          "}\n";
      std::string testFileName = "./testFile.txt";
      std::ofstream testFile;
      testFile.open(testFileName);
      testFile << testInput;
      testFile.close();

      REQUIRE(pkbRead->getWhilePatterns().empty());
      REQUIRE(pkbReadSpa->getWhilePatterns().empty());

      sourceManager.process(testFileName);
      spa.process(testFileName);
      actualMap = pkbRead->getWhilePatterns();
      actualMapSpa = pkbReadSpa->getWhilePatterns();

      std::unordered_map<std::string, std::unordered_set<int>> expectedMap;
      expectedMap["a"].insert(1);
      expectedMap["b"].insert(3);
      expectedMap["c"].insert(7);
      expectedMap["d"].insert(9);

      REQUIRE(actualMap.size() == 4);
      REQUIRE(actualMapSpa.size() == 4);
      REQUIRE(actualMap == expectedMap);
      REQUIRE(actualMapSpa == expectedMap);

      std::filesystem::remove(testFileName);
    }
    SECTION("test multiple values to key whiles") {
      std::string testInput =
          "procedure a {\n"
          "    while (a == 1) {\n"     //1
          "       print a;\n"          //2
          "       while (a == 2) {\n"  //3
          "           c = 4;\n"        //4
          "       }\n"
          "    }\n"
          "    while (a == 2) {\n"    //5
          "       c = 4;\n"           //6
          "       while (a > 5) {\n"  //7
          "           d = 6; \n"      //8
          "       }\n"
          "    }"
          "    while (a < 2) {\n"  //9
          "       a = 3;\n"        //10
          "    }\n"
          "}\n";
      std::string testFileName = "./testFile.txt";
      std::ofstream testFile;
      testFile.open(testFileName);
      testFile << testInput;
      testFile.close();

      REQUIRE(pkbRead->getWhilePatterns().empty());
      REQUIRE(pkbReadSpa->getWhilePatterns().empty());

      sourceManager.process(testFileName);
      spa.process(testFileName);
      actualMap = pkbRead->getWhilePatterns();
      actualMapSpa = pkbReadSpa->getWhilePatterns();

      std::unordered_map<std::string, std::unordered_set<int>> expectedMap;
      expectedMap["a"].insert(1);
      expectedMap["a"].insert(3);
      expectedMap["a"].insert(5);
      expectedMap["a"].insert(7);
      expectedMap["a"].insert(9);

      REQUIRE(actualMap.size() == 1);
      REQUIRE(actualMapSpa.size() == 1);
      REQUIRE(actualMap == expectedMap);
      REQUIRE(actualMapSpa == expectedMap);

      std::filesystem::remove(testFileName);
    }
  }
}
