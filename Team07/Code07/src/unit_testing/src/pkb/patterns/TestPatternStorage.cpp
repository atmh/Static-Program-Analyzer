//
// Created by Volunteer The on 9/9/23.
//

#include "catch.hpp"
#include "pkb/pattern_clause/patterns/AssignPatternStorage.h"
#include "pkb/pattern_clause/patterns/IfPatternStorage.h"
#include "pkb/pattern_clause/patterns/WhilePatternStorage.h"
namespace PKB {

TEST_CASE("test AssignPatternStorage") {
  PKB::AssignPatternStorage patternStorage;

  SECTION("test get vector") {
    std::string lhs1 = "x";
    std::vector<std::string> rhs1 = {"a", "+", "b"};
    int stmtIndex1 = 1;
    patternStorage.storeAssignPattern(stmtIndex1, lhs1, rhs1);

    SECTION("test non-existent vector") {
      std::string nonExistentLhs = "z";
      const std::vector<std::pair<std::vector<std::string>, int>>&
          actualVector = patternStorage.getVector(nonExistentLhs);
      REQUIRE(patternStorage.getAllPatterns().size() == 1);
      REQUIRE(actualVector.empty());
    }
    SECTION("test getVector") {
      const std::vector<std::pair<std::vector<std::string>, int>>&
          actualVector = patternStorage.getVector(lhs1);
      std::vector<std::pair<std::vector<std::string>, int>> expectedVector;
      expectedVector.emplace_back(rhs1, stmtIndex1);
      REQUIRE(patternStorage.getVector(lhs1).size() == 1);
      REQUIRE(patternStorage.getVector(lhs1) == expectedVector);
    }
  }

  SECTION("test StorePattern") {
    std::string lhs1 = "x";
    std::vector<std::string> rhs1 = {"a", "+", "b"};
    int stmtIndex1 = 1;
    std::string lhs2 = "y";
    std::vector<std::string> rhs2 = {"c", "-", "d"};
    int stmtIndex2 = 2;
    std::string lhs3 = "z";
    std::vector<std::string> rhs3 = {"e", "*", "f"};
    int stmtIndex3 = 3;
    std::string lhs4 = "w";
    std::vector<std::string> rhs4 = {"g", "/", "h"};
    int stmtIndex4 = 4;

    patternStorage.storeAssignPattern(stmtIndex1, lhs1, rhs1);

    const std::vector<std::pair<std::vector<std::string>, int>>& storedVector1 =
        patternStorage.getVector(lhs1);

    SECTION("test Store Single pattern") {
      REQUIRE(storedVector1.size() == 1);
      REQUIRE(storedVector1[0].first == rhs1);
      REQUIRE(storedVector1[0].second == stmtIndex1);
    }
    patternStorage.storeAssignPattern(stmtIndex2, lhs2, rhs2);
    const std::vector<std::pair<std::vector<std::string>, int>>& storedVector2 =
        patternStorage.getVector(lhs2);
    patternStorage.storeAssignPattern(stmtIndex3, lhs3, rhs3);
    const std::vector<std::pair<std::vector<std::string>, int>>& storedVector3 =
        patternStorage.getVector(lhs3);
    patternStorage.storeAssignPattern(stmtIndex4, lhs4, rhs4);
    const std::vector<std::pair<std::vector<std::string>, int>>& storedVector4 =
        patternStorage.getVector(lhs4);

    SECTION("test Store multiple patterns") {
      SECTION("negative test ") {
        REQUIRE_FALSE(storedVector2.size() == 2);
        REQUIRE_FALSE(storedVector2[0].first == rhs3);
        REQUIRE_FALSE(storedVector2[0].second == stmtIndex3);
      }

      SECTION("positive tests") {
        REQUIRE(storedVector2.size() == 1);
        REQUIRE(storedVector2[0].first == rhs2);
        REQUIRE(storedVector2[0].second == stmtIndex2);
        REQUIRE(storedVector3.size() == 1);
        REQUIRE(storedVector3[0].first == rhs3);
        REQUIRE(storedVector3[0].second == stmtIndex3);
        REQUIRE(storedVector4.size() == 1);
        REQUIRE(storedVector4[0].first == rhs4);
        REQUIRE(storedVector4[0].second == stmtIndex4);
      }
      SECTION("storing and retrieving multiple patterns into single lhs") {
        patternStorage.storeAssignPattern(stmtIndex3, lhs2, rhs3);
        const std::vector<std::pair<std::vector<std::string>, int>>&
            storedVector5 = patternStorage.getVector(lhs2);
        REQUIRE(storedVector2.size() == 2);
        auto actualVector = patternStorage.getVector(lhs2);
        std::vector<std::pair<std::vector<std::string>, int>> expectedVector;
        expectedVector.emplace_back(rhs2, stmtIndex2);
        expectedVector.emplace_back(rhs3, stmtIndex3);
        REQUIRE(expectedVector == actualVector);
      }
    }
  }
}
TEST_CASE("test IfPatternStorage") {
  PKB::IfPatternStorage patternStorage;

  SECTION("test getSet") {
    int stmtOne = 1;
    std::string varOne = "x";
    std::unordered_map<std::string, std::unordered_set<int>> expectedMap;

    SECTION("test non existing set") {
      REQUIRE(patternStorage.getAllPatterns().empty());
      std::string nonExistingVar = "y";
      patternStorage.storeIfWhilePattern(stmtOne, varOne);
      REQUIRE(patternStorage.getAllPatterns().size() == 1);
      REQUIRE(patternStorage.getSet(nonExistingVar).empty());
    }
    SECTION("test single entry StorePattern") {
      REQUIRE(patternStorage.getSet(varOne) == expectedMap[varOne]);
      expectedMap[varOne].insert(stmtOne);
      patternStorage.storeIfWhilePattern(stmtOne, varOne);
      REQUIRE(patternStorage.getSet(varOne) == expectedMap[varOne]);
    }
  }

  SECTION("test Multiple entry StorePattern") {
    int stmtOne = 1;
    std::string varOne = "x";
    int stmtTwo = 5;
    int stmtThree = 7;
    std::unordered_map<std::string, std::unordered_set<int>> expectedMap;
    expectedMap[varOne].insert(stmtOne);
    expectedMap[varOne].insert(stmtTwo);
    expectedMap[varOne].insert(stmtThree);
    REQUIRE(patternStorage.getSet(varOne).empty());
    patternStorage.storeIfWhilePattern(stmtOne, varOne);
    patternStorage.storeIfWhilePattern(stmtTwo, varOne);
    patternStorage.storeIfWhilePattern(stmtThree, varOne);

    SECTION("test one variable") {
      REQUIRE(patternStorage.getSet(varOne) == expectedMap[varOne]);
    }
    int stmtFour = 2;
    std::string varTwo = "y";
    int stmtFive = 6;
    int stmtSix = 9;
    expectedMap[varTwo].insert(stmtFour);
    expectedMap[varTwo].insert(stmtFive);
    expectedMap[varTwo].insert(stmtSix);
    REQUIRE(patternStorage.getAllPatterns().size() == 1);
    patternStorage.storeIfWhilePattern(stmtFour, varTwo);
    patternStorage.storeIfWhilePattern(stmtFive, varTwo);
    patternStorage.storeIfWhilePattern(stmtSix, varTwo);

    SECTION("test multiple variables") {
      REQUIRE(patternStorage.getAllPatterns().size() == 2);
      REQUIRE(patternStorage.getSet(varOne) == expectedMap[varOne]);
      REQUIRE(patternStorage.getSet(varTwo) == expectedMap[varTwo]);
      REQUIRE_FALSE(patternStorage.getSet(varOne) == expectedMap[varTwo]);
    }
  }
}

TEST_CASE("test WhilePatternStorage") {
  PKB::WhilePatternStorage patternStorage;

  SECTION("test getSet") {
    int stmtOne = 1;
    std::string varOne = "x";
    std::unordered_map<std::string, std::unordered_set<int>> expectedMap;

    SECTION("test non existing set") {
      REQUIRE(patternStorage.getAllPatterns().empty());
      std::string nonExistingVar = "y";
      patternStorage.storeIfWhilePattern(stmtOne, varOne);
      REQUIRE(patternStorage.getAllPatterns().size() == 1);
      REQUIRE(patternStorage.getSet(nonExistingVar).empty());
    }
    SECTION("test single entry StorePattern") {
      REQUIRE(patternStorage.getSet(varOne) == expectedMap[varOne]);
      expectedMap[varOne].insert(stmtOne);
      patternStorage.storeIfWhilePattern(stmtOne, varOne);
      REQUIRE(patternStorage.getSet(varOne) == expectedMap[varOne]);
    }
  }

  SECTION("test Multiple entry StorePattern") {
    int stmtOne = 1;
    std::string varOne = "x";
    int stmtTwo = 5;
    int stmtThree = 7;
    std::unordered_map<std::string, std::unordered_set<int>> expectedMap;
    expectedMap[varOne].insert(stmtOne);
    expectedMap[varOne].insert(stmtTwo);
    expectedMap[varOne].insert(stmtThree);
    REQUIRE(patternStorage.getSet(varOne).empty());
    patternStorage.storeIfWhilePattern(stmtOne, varOne);
    patternStorage.storeIfWhilePattern(stmtTwo, varOne);
    patternStorage.storeIfWhilePattern(stmtThree, varOne);

    SECTION("test one variable") {
      REQUIRE(patternStorage.getSet(varOne) == expectedMap[varOne]);
    }
    int stmtFour = 2;
    std::string varTwo = "y";
    int stmtFive = 6;
    int stmtSix = 9;
    expectedMap[varTwo].insert(stmtFour);
    expectedMap[varTwo].insert(stmtFive);
    expectedMap[varTwo].insert(stmtSix);
    REQUIRE(patternStorage.getAllPatterns().size() == 1);
    patternStorage.storeIfWhilePattern(stmtFour, varTwo);
    patternStorage.storeIfWhilePattern(stmtFive, varTwo);
    patternStorage.storeIfWhilePattern(stmtSix, varTwo);

    SECTION("test multiple variables") {
      REQUIRE(patternStorage.getAllPatterns().size() == 2);
      REQUIRE(patternStorage.getSet(varOne) == expectedMap[varOne]);
      REQUIRE(patternStorage.getSet(varTwo) == expectedMap[varTwo]);
      REQUIRE_FALSE(patternStorage.getSet(varOne) == expectedMap[varTwo]);
    }
  }
}
}  // namespace PKB
