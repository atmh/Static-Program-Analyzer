//
// Created by Volunteer The on 9/9/23.
//
#include "catch.hpp"
#include "pkb/such_that_clause/SuchThatStorage.h"
#include "pkb/such_that_clause/operations/FollowsOperationStorage.h"
#include "pkb/such_that_clause/operations/ModifiesProcedureOperationStorage.h"
#include "pkb/such_that_clause/operations/ParentOperationStorage.h"
#include "pkb/such_that_clause/operations/UsesProcedureOperationStorage.h"
#include "pkb/such_that_clause/operations/UsesStatementOperationStorage.h"
#include "pkb/utils/BiDirectionalMap.h"

using namespace PKB;

TEST_CASE("Test getFirstArgRelationships") {
  SECTION("test for follows Storage") {
    FollowsOperationStorage followsStorage;
    std::unordered_set<int> expectedResult = {2};
    std::unordered_set<int> unExpectedResult = {100};
    std::unordered_set<int> emptyResult = {};
    // store single follows relationship
    followsStorage.storeInformation(1, 2);
    REQUIRE(followsStorage.getFirstArgRelationships(1) == expectedResult);
    REQUIRE_FALSE(followsStorage.getFirstArgRelationships(1) ==
                  unExpectedResult);
    REQUIRE(followsStorage.getFirstArgRelationships(5) == emptyResult);
    REQUIRE(followsStorage.getFirstArgRelationships(2) == emptyResult);

    followsStorage.storeInformation(2, 3);
    followsStorage.storeInformation(4, 5);
    followsStorage.storeInformation(3, 6);

    std::unordered_set<int> expectedResult2 = {3};
    REQUIRE(followsStorage.getFirstArgRelationships(2) == expectedResult2);
    std::unordered_set<int> expectedResult3 = {5};
    REQUIRE(followsStorage.getFirstArgRelationships(4) == expectedResult3);
    std::unordered_set<int> expectedResult4 = {6};
    REQUIRE(followsStorage.getFirstArgRelationships(3) == expectedResult4);

    REQUIRE(followsStorage.getFirstArgRelationships(5) == emptyResult);
    REQUIRE(followsStorage.getFirstArgRelationships(6) == emptyResult);
  }

  SECTION("test for follows Storage") {
    ParentOperationStorage parentStorage;
    std::unordered_set<int> expectedResult = {2};
    std::unordered_set<int> unExpectedResult = {100};
    std::unordered_set<int> emptyResult = {};
    // store single parent relationship
    parentStorage.storeInformation(1, 2);
    REQUIRE(parentStorage.getFirstArgRelationships(1) == expectedResult);
    REQUIRE_FALSE(parentStorage.getFirstArgRelationships(1) ==
                  unExpectedResult);
    REQUIRE(parentStorage.getFirstArgRelationships(5) == emptyResult);
    REQUIRE(parentStorage.getFirstArgRelationships(2) == emptyResult);

    parentStorage.storeInformation(2, 3);
    parentStorage.storeInformation(4, 5);
    parentStorage.storeInformation(3, 6);

    std::unordered_set<int> expectedResultTwo = {3};
    REQUIRE(parentStorage.getFirstArgRelationships(2) == expectedResultTwo);
    std::unordered_set<int> expectedResultThree = {5};
    REQUIRE(parentStorage.getFirstArgRelationships(4) == expectedResultThree);
    std::unordered_set<int> expectedResultFour = {6};
    REQUIRE(parentStorage.getFirstArgRelationships(3) == expectedResultFour);

    REQUIRE(parentStorage.getFirstArgRelationships(5) == emptyResult);
    REQUIRE(parentStorage.getFirstArgRelationships(6) == emptyResult);
  }

  SECTION("test uses Procedure Storage") {
    UsesProcedureOperationStorage usesStorage;
    std::unordered_set<std::string> expectedResult = {"x"};
    std::unordered_set<std::string> unExpectedResult = {"unexpected"};
    std::unordered_set<std::string> emptyResult = {};

    // store single uses relationship
    usesStorage.storeInformation("7", "x");
    REQUIRE(usesStorage.getRelationshipExists("7", "x"));
    REQUIRE_FALSE(usesStorage.getRelationshipExists("7", "a"));
    REQUIRE_FALSE(usesStorage.getRelationshipExists("x", "7"));

    usesStorage.storeInformation("10", "count");
    usesStorage.storeInformation("10", "it");
    usesStorage.storeInformation("main", "x");
    std::unordered_set<std::string> expectedResultTwo = {"count", "it"};
    REQUIRE(usesStorage.getFirstArgRelationships("10") == expectedResultTwo);
    std::unordered_set<std::string> expectedResultThree = {"x"};
    REQUIRE(usesStorage.getFirstArgRelationships("main") ==
            expectedResultThree);

    REQUIRE(usesStorage.getFirstArgRelationships("noRelation") == emptyResult);
    REQUIRE(usesStorage.getFirstArgRelationships("it") == emptyResult);
  }

  SECTION("test uses Statement Storage") {
    UsesStatementOperationStorage usesStorage;
    std::unordered_set<std::string> expectedResult = {"x"};
    std::unordered_set<std::string> unExpectedResult = {"unexpected"};
    std::unordered_set<std::string> emptyResult = {};

    // store single uses relationship
    usesStorage.storeInformation(7, "x");
    REQUIRE(usesStorage.getRelationshipExists(7, "x"));
    REQUIRE_FALSE(usesStorage.getRelationshipExists(7, "a"));
    REQUIRE_FALSE(usesStorage.getRelationshipExists(33, "k"));

    usesStorage.storeInformation(10, "count");
    usesStorage.storeInformation(10, "it");
    usesStorage.storeInformation(15, "x");
    std::unordered_set<std::string> expectedResultTwo = {"count", "it"};
    REQUIRE(usesStorage.getFirstArgRelationships(10) == expectedResultTwo);
    std::unordered_set<std::string> expectedResultThree = {"x"};
    REQUIRE(usesStorage.getFirstArgRelationships(15) == expectedResultThree);

    REQUIRE(usesStorage.getFirstArgRelationships(100) == emptyResult);
    REQUIRE(usesStorage.getFirstArgRelationships(1000) == emptyResult);
  }

  SECTION("test modifies Storage") {
    ModifiesProcedureOperationStorage modifiesProcedureStorage;
    std::unordered_set<std::string> expectedResult = {"x"};
    std::unordered_set<std::string> unExpectedResult = {"unexpected"};
    std::unordered_set<std::string> emptyResult = {};

    // store single modifies relationship
    modifiesProcedureStorage.storeInformation("7", "x");
    REQUIRE(modifiesProcedureStorage.getRelationshipExists("7", "x"));
    REQUIRE_FALSE(modifiesProcedureStorage.getRelationshipExists("7", "a"));
    REQUIRE_FALSE(modifiesProcedureStorage.getRelationshipExists("x", "7"));

    modifiesProcedureStorage.storeInformation("10", "count");
    modifiesProcedureStorage.storeInformation("10", "it");
    modifiesProcedureStorage.storeInformation("main", "x");
    std::unordered_set<std::string> expectedResultTwo = {"count", "it"};
    REQUIRE(modifiesProcedureStorage.getFirstArgRelationships("10") ==
            expectedResultTwo);
    std::unordered_set<std::string> expectedResultThree = {"x"};
    REQUIRE(modifiesProcedureStorage.getFirstArgRelationships("main") ==
            expectedResultThree);

    REQUIRE(modifiesProcedureStorage.getFirstArgRelationships("noRelation") ==
            emptyResult);
    REQUIRE(modifiesProcedureStorage.getFirstArgRelationships("it") ==
            emptyResult);
  }
}
