//
// Created by Volunteer The on 22/9/23.
//
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "TestSPA.h"
#include "catch.hpp"
#include "pkb/PKBStorageAPI.h"
#include "pkb/PKBStorageWriteAPI.h"
#include "sp/SPManager.h"

using namespace PKB;

TEST_CASE("Integration test for such that storage") {
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

  SECTION("Test for SP populating PKB") {
    std::string testInput =
        "procedure a {\n"
        "    e = f + g * h;\n"  // 1
        "    z = q;\n"          // 1
        "}\n";
    std::string testFileName = "./testFile.txt";
    std::ofstream testFile;
    testFile.open(testFileName);
    testFile << testInput;
    testFile.close();

    REQUIRE_FALSE(processedStorage->hasFollowsRelationship());
    REQUIRE_FALSE(processedStorageSpa->hasFollowsRelationship());
    sourceManager.process(testFileName);
    spa.process(testFileName);
    REQUIRE(processedStorage->hasFollowsRelationship());
    REQUIRE(processedStorageSpa->hasFollowsRelationship());

    std::filesystem::remove(testFileName);
  }

  SECTION("test for No nesting") {
    std::string testInput =
        "procedure a {\n"
        "    e = f + g * h;\n"    // 1
        "    read c;\n"           // 2
        "    b = c + x;\n"        // 3
        "    while (c == 1) {\n"  // 4
        "       d = 5;\n"         // 5
        "       c = d;\n"         // 6
        "    }\n"
        "    print c;\n"  // 7
        "}\n";

    std::string testFileName = "./testFile.txt";
    std::ofstream testFile;
    testFile.open(testFileName);
    testFile << testInput;
    testFile.close();

    SECTION("Test for Follows Relationship") {
      std::unordered_set<int> expectedRelationshipWithOne = {2, 3, 4, 7};
      SECTION("test SP manager") {
        sourceManager.process(testFileName);
        REQUIRE(pkbRead->getFollowsRelationshipExists(1, 2));
        REQUIRE(pkbRead->getFollowsRelationshipExists(2, 3));
        REQUIRE(pkbRead->getFollowsRelationshipExists(3, 4));
        REQUIRE(pkbRead->getFollowsRelationshipExists(3, 4));
        REQUIRE_FALSE(pkbRead->getFollowsRelationshipExists(4, 5));
        REQUIRE_FALSE(pkbRead->getFollowsFirstArgRelationships(1) ==
                      expectedRelationshipWithOne);
        REQUIRE(pkbRead->getFollowsStarFirstArgRelationships(1) ==
                expectedRelationshipWithOne);
      }
      SECTION("test spa") {
        spa.process(testFileName);
        REQUIRE(pkbReadSpa->getFollowsRelationshipExists(1, 2));
        REQUIRE(pkbReadSpa->getFollowsRelationshipExists(2, 3));
        REQUIRE(pkbReadSpa->getFollowsRelationshipExists(3, 4));
        REQUIRE(pkbReadSpa->getFollowsRelationshipExists(3, 4));
        REQUIRE_FALSE(pkbReadSpa->getFollowsRelationshipExists(4, 5));
        REQUIRE_FALSE(pkbReadSpa->getFollowsFirstArgRelationships(1) ==
                      expectedRelationshipWithOne);
        REQUIRE(pkbReadSpa->getFollowsStarFirstArgRelationships(1) ==
                expectedRelationshipWithOne);
      }
    }
    SECTION("Test for Parent Relationship") {
      std::unordered_set<int> expectedRelationshipWithOne = {5, 6};
      SECTION("test SP manager") {
        sourceManager.process(testFileName);
        REQUIRE_FALSE(pkbRead->getParentRelationshipExists(1, 2));
        REQUIRE_FALSE(pkbRead->getParentRelationshipExists(2, 3));
        REQUIRE_FALSE(pkbRead->getParentRelationshipExists(3, 4));
        REQUIRE_FALSE(pkbRead->getParentRelationshipExists(3, 4));
        REQUIRE(pkbRead->getParentRelationshipExists(4, 5));
        REQUIRE(pkbRead->getParentFirstArgRelationships(1).empty());
        REQUIRE(pkbRead->getParentStarFirstArgRelationships(4) ==
                expectedRelationshipWithOne);
      }
      SECTION("test spa") {
        spa.process(testFileName);
        REQUIRE_FALSE(pkbReadSpa->getParentRelationshipExists(1, 2));
        REQUIRE_FALSE(pkbReadSpa->getParentRelationshipExists(2, 3));
        REQUIRE_FALSE(pkbReadSpa->getParentRelationshipExists(3, 4));
        REQUIRE_FALSE(pkbReadSpa->getParentRelationshipExists(3, 4));
        REQUIRE(pkbReadSpa->getParentRelationshipExists(4, 5));
        REQUIRE(pkbReadSpa->getParentFirstArgRelationships(1).empty());
        REQUIRE(pkbReadSpa->getParentStarFirstArgRelationships(4) ==
                expectedRelationshipWithOne);
      }
    }
    SECTION("Test for Modifies Relationship") {
      SECTION("test SP manager") {
        sourceManager.process(testFileName);
        REQUIRE(pkbRead->getModifiesStatementRelationshipExists(1, "e"));
        REQUIRE(pkbRead->getModifiesStatementFirstArgRelationships(1) ==
                std::unordered_set<std::string>{"e"});
        REQUIRE(pkbRead->getModifiesStatementFirstArgRelationships(2) ==
                std::unordered_set<std::string>{"c"});
        REQUIRE(pkbRead->getModifiesStatementFirstArgRelationships(3) ==
                std::unordered_set<std::string>{"b"});
        REQUIRE(pkbRead->getModifiesStatementFirstArgRelationships(4) ==
                std::unordered_set<std::string>{"c", "d"});
      }
      SECTION("test spa") {
        spa.process(testFileName);
        REQUIRE(pkbReadSpa->getModifiesStatementRelationshipExists(1, "e"));
        REQUIRE(pkbReadSpa->getModifiesStatementFirstArgRelationships(1) ==
                std::unordered_set<std::string>{"e"});
        REQUIRE(pkbReadSpa->getModifiesStatementFirstArgRelationships(2) ==
                std::unordered_set<std::string>{"c"});
        REQUIRE(pkbReadSpa->getModifiesStatementFirstArgRelationships(3) ==
                std::unordered_set<std::string>{"b"});
        REQUIRE(pkbReadSpa->getModifiesStatementFirstArgRelationships(4) ==
                std::unordered_set<std::string>{"c", "d"});
      }
    }
    SECTION("Test for Uses Relationship") {
      SECTION("test SP manager") {
        sourceManager.process(testFileName);
        REQUIRE(pkbRead->getUsesStatementRelationshipExists(1, "f"));
        REQUIRE(pkbRead->getUsesStatementFirstArgRelationships(1) ==
                std::unordered_set<std::string>{"f", "g", "h"});
        REQUIRE(pkbRead->getUsesStatementFirstArgRelationships(2).empty());
        REQUIRE(pkbRead->getUsesStatementFirstArgRelationships(3) ==
                std::unordered_set<std::string>{"c", "x"});
        REQUIRE(pkbRead->getUsesStatementFirstArgRelationships(4) ==
                std::unordered_set<std::string>{"c", "d"});
      }
      SECTION("test spa") {
        spa.process(testFileName);
        REQUIRE(pkbReadSpa->getUsesStatementRelationshipExists(1, "f"));
        REQUIRE(pkbReadSpa->getUsesStatementFirstArgRelationships(1) ==
                std::unordered_set<std::string>{"f", "g", "h"});
        REQUIRE(pkbReadSpa->getUsesStatementFirstArgRelationships(2).empty());
        REQUIRE(pkbReadSpa->getUsesStatementFirstArgRelationships(3) ==
                std::unordered_set<std::string>{"c", "x"});
        REQUIRE(pkbReadSpa->getUsesStatementFirstArgRelationships(4) ==
                std::unordered_set<std::string>{"c", "d"});
      }
    }

    SECTION("Test for Next Relationship") {
      std::unordered_set<int> expectedRelationshipWithOne = {2};
      SECTION("test SP manager") {
        sourceManager.process(testFileName);
        REQUIRE(pkbRead->getNextRelationshipExists(1, 2));
        REQUIRE(pkbRead->getNextRelationshipExists(2, 3));
        REQUIRE(pkbRead->getNextRelationshipExists(3, 4));
        REQUIRE(pkbRead->getNextRelationshipExists(4, 5));
        REQUIRE(pkbRead->getNextRelationshipExists(4, 7));
        REQUIRE(pkbRead->getNextFirstArgRelationships(1) ==
                expectedRelationshipWithOne);

        REQUIRE_FALSE(pkbRead->getNextRelationshipExists(3, 5));
        REQUIRE_FALSE(pkbRead->getNextRelationshipExists(3, 6));
      }
      SECTION("test spa") {
        spa.process(testFileName);
        REQUIRE(pkbReadSpa->getNextRelationshipExists(1, 2));
        REQUIRE(pkbReadSpa->getNextRelationshipExists(2, 3));
        REQUIRE(pkbReadSpa->getNextRelationshipExists(3, 4));
        REQUIRE(pkbReadSpa->getNextRelationshipExists(4, 5));
        REQUIRE(pkbReadSpa->getNextRelationshipExists(4, 7));
        REQUIRE(pkbReadSpa->getNextFirstArgRelationships(1) ==
                expectedRelationshipWithOne);
        REQUIRE_FALSE(pkbReadSpa->getNextRelationshipExists(3, 5));
        REQUIRE_FALSE(pkbReadSpa->getNextRelationshipExists(3, 6));
      }
    }

    std::filesystem::remove(testFileName);
  }

  SECTION("test for while if nesting") {
    std::string testInput =
        "procedure a {\n"
        "    while (c == 1) {\n"     // 1
        "       d = 5;\n"            // 2
        "       c = d;\n"            // 3
        "       if (k > 1) then{\n"  // 4
        "           j = p;\n"        // 5
        "       } else {\n"
        "           j = d + 1;\n"  // 6
        "       }\n"
        "    }\n"
        "    print c;\n"  // 7
        "}\n";

    std::string testFileName = "./testFile.txt";
    std::ofstream testFile;
    testFile.open(testFileName);
    testFile << testInput;
    testFile.close();

    SECTION("test for sp manager") {
      sourceManager.process(testFileName);
      SECTION("Test for Follows Relationship") {
        REQUIRE(pkbRead->getFollowsRelationshipExists(1, 7));
        REQUIRE_FALSE(pkbRead->getFollowsRelationshipExists(4, 7));
        REQUIRE(pkbRead->getFollowsFirstArgRelationships(1) ==
                std::unordered_set<int>{7});
      }
      SECTION("Test for Parent Relationship") {
        REQUIRE(pkbRead->getParentFirstArgRelationships(1) ==
                std::unordered_set<int>{2, 3, 4});
        REQUIRE(pkbRead->getParentStarFirstArgRelationships(4) ==
                std::unordered_set<int>{5, 6});
      }
      SECTION("Test for Modifies Relationship") {
        REQUIRE_FALSE(pkbRead->getModifiesStatementRelationshipExists(1, "e"));
        REQUIRE(pkbRead->getModifiesStatementFirstArgRelationships(1) ==
                std::unordered_set<std::string>{"c", "d", "j"});
        REQUIRE(pkbRead->getModifiesStatementFirstArgRelationships(2) ==
                std::unordered_set<std::string>{"d"});
        REQUIRE(pkbRead->getModifiesStatementFirstArgRelationships(3) ==
                std::unordered_set<std::string>{"c"});
        REQUIRE(pkbRead->getModifiesStatementFirstArgRelationships(4) ==
                std::unordered_set<std::string>{"j"});
        REQUIRE(pkbRead->getModifiesStatementFirstArgRelationships(5) ==
                std::unordered_set<std::string>{"j"});
      }
      SECTION("Test for Uses Relationship") {
        REQUIRE(pkbRead->getUsesStatementFirstArgRelationships(1) ==
                std::unordered_set<std::string>{"c", "d", "k", "p"});
        REQUIRE(pkbRead->getUsesStatementFirstArgRelationships(4) ==
                std::unordered_set<std::string>{"k", "p", "d"});
        REQUIRE(pkbRead->getUsesStatementFirstArgRelationships(5) ==
                std::unordered_set<std::string>{"p"});
        REQUIRE(pkbRead->getUsesStatementFirstArgRelationships(6) ==
                std::unordered_set<std::string>{"d"});
      }
      SECTION("Test for Next Relationship") {
        REQUIRE(pkbRead->getNextRelationshipExists(1, 7));
        REQUIRE(pkbRead->getNextRelationshipExists(4, 6));
        REQUIRE_FALSE(pkbRead->getNextRelationshipExists(4, 7));
        REQUIRE(pkbRead->getNextFirstArgRelationships(1) ==
                std::unordered_set<int>{2, 7});
      }
    }

    SECTION("test for spa") {
      spa.process(testFileName);
      SECTION("Test for Follows Relationship") {
        REQUIRE(pkbReadSpa->getFollowsRelationshipExists(1, 7));
        REQUIRE_FALSE(pkbReadSpa->getFollowsRelationshipExists(4, 7));
        REQUIRE(pkbReadSpa->getFollowsFirstArgRelationships(1) ==
                std::unordered_set<int>{7});
      }
      SECTION("Test for Parent Relationship") {
        REQUIRE(pkbReadSpa->getParentFirstArgRelationships(1) ==
                std::unordered_set<int>{2, 3, 4});
        REQUIRE(pkbReadSpa->getParentStarFirstArgRelationships(4) ==
                std::unordered_set<int>{5, 6});
      }
      SECTION("Test for Modifies Relationship") {
        REQUIRE_FALSE(pkbRead->getModifiesStatementRelationshipExists(1, "e"));
        REQUIRE(pkbReadSpa->getModifiesStatementFirstArgRelationships(1) ==
                std::unordered_set<std::string>{"c", "d", "j"});
        REQUIRE(pkbReadSpa->getModifiesStatementFirstArgRelationships(2) ==
                std::unordered_set<std::string>{"d"});
        REQUIRE(pkbReadSpa->getModifiesStatementFirstArgRelationships(3) ==
                std::unordered_set<std::string>{"c"});
        REQUIRE(pkbReadSpa->getModifiesStatementFirstArgRelationships(4) ==
                std::unordered_set<std::string>{"j"});
        REQUIRE(pkbReadSpa->getModifiesStatementFirstArgRelationships(5) ==
                std::unordered_set<std::string>{"j"});
      }
      SECTION("Test for Uses Relationship") {
        REQUIRE(pkbReadSpa->getUsesStatementFirstArgRelationships(1) ==
                std::unordered_set<std::string>{"c", "d", "k", "p"});
        REQUIRE(pkbReadSpa->getUsesStatementFirstArgRelationships(4) ==
                std::unordered_set<std::string>{"k", "p", "d"});
        REQUIRE(pkbReadSpa->getUsesStatementFirstArgRelationships(5) ==
                std::unordered_set<std::string>{"p"});
        REQUIRE(pkbReadSpa->getUsesStatementFirstArgRelationships(6) ==
                std::unordered_set<std::string>{"d"});
      }
      SECTION("Test for Next Relationship") {
        REQUIRE(pkbReadSpa->getNextRelationshipExists(1, 7));
        REQUIRE(pkbReadSpa->getNextRelationshipExists(4, 6));
        REQUIRE_FALSE(pkbReadSpa->getNextRelationshipExists(4, 7));
        REQUIRE(pkbReadSpa->getNextFirstArgRelationships(1) ==
                std::unordered_set<int>{2, 7});
      }
    }

    std::filesystem::remove(testFileName);
  }

  SECTION("Test for Calls/Calls* relationship") {
    std::string testInput =
        "procedure a {\n"
        "    call b;\n"
        "}\n"
        "procedure b {\n"
        "    call d;\n"
        "}\n"
        "procedure c {\n"
        "    print x;\n"
        "}\n"
        "procedure d {\n"
        "    read y;\n"
        "}\n";
    std::string testFileName = "./testFile.txt";
    std::ofstream testFile;
    testFile.open(testFileName);
    testFile << testInput;
    testFile.close();

    REQUIRE_FALSE(processedStorage->hasCallsRelationship());
    REQUIRE_FALSE(processedStorageSpa->hasCallsRelationship());

    SECTION("test for SPManager") {
      sourceManager.process(testFileName);
      REQUIRE(processedStorage->hasCallsRelationship());
      REQUIRE(pkbRead->getCallsRelationshipExists("a", "b"));
      REQUIRE(pkbRead->getCallsRelationshipExists("b", "d"));
      REQUIRE_FALSE(pkbRead->getCallsRelationshipExists("a", "d"));
      REQUIRE_FALSE(pkbRead->getCallsRelationshipExists("c", "d"));

      SECTION("test Calls*") {
        REQUIRE(pkbRead->getCallsStarRelationshipExists("a", "d"));
      }
    }
    SECTION("test for spa") {
      spa.process(testFileName);
      REQUIRE(processedStorageSpa->hasCallsRelationship());
      REQUIRE(pkbReadSpa->getCallsRelationshipExists("a", "b"));
      REQUIRE(pkbReadSpa->getCallsRelationshipExists("b", "d"));
      REQUIRE_FALSE(pkbReadSpa->getCallsRelationshipExists("a", "d"));
      REQUIRE_FALSE(pkbReadSpa->getCallsRelationshipExists("c", "d"));

      SECTION("test Calls*") {
        REQUIRE(pkbReadSpa->getCallsStarRelationshipExists("a", "d"));
      }
    }

    std::filesystem::remove(testFileName);
  }
}
