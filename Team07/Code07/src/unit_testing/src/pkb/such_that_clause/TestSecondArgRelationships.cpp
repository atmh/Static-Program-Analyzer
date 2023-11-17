//
// Created by Volunteer The on 9/9/23.
//
#include "catch.hpp"
#include "pkb/such_that_clause/SuchThatStorage.h"
#include "pkb/such_that_clause/operations/CallsOperationStorage.h"
#include "pkb/such_that_clause/operations/FollowsOperationStorage.h"
#include "pkb/such_that_clause/operations/ModifiesProcedureOperationStorage.h"
#include "pkb/such_that_clause/operations/NextOperationStorage.h"
#include "pkb/such_that_clause/operations/ParentOperationStorage.h"
#include "pkb/such_that_clause/operations/UsesProcedureOperationStorage.h"
#include "pkb/such_that_clause/operations/UsesStatementOperationStorage.h"
#include "pkb/utils/BiDirectionalMap.h"

using namespace PKB;

TEST_CASE("Test getSecondArgRelationships") {
  SECTION("test for follows Storage") {
    FollowsOperationStorage followsStorage;
    std::unordered_set<int> expectedResult = {1};
    std::unordered_set<int> unExpectedResult = {100};
    std::unordered_set<int> emptyResult = {};
    // store single follows relationship
    followsStorage.storeInformation(1, 2);
    REQUIRE(followsStorage.getSecondArgRelationships(2) == expectedResult);
    REQUIRE_FALSE(followsStorage.getSecondArgRelationships(2) ==
                  unExpectedResult);
    REQUIRE(followsStorage.getSecondArgRelationships(5) == emptyResult);
    REQUIRE(followsStorage.getSecondArgRelationships(100) == emptyResult);

    followsStorage.storeInformation(2, 3);
    followsStorage.storeInformation(4, 5);
    followsStorage.storeInformation(3, 6);

    std::unordered_set<int> expectedResultTwo = {2};
    REQUIRE(followsStorage.getSecondArgRelationships(3) == expectedResultTwo);
    std::unordered_set<int> expectedResultThree = {4};
    REQUIRE(followsStorage.getSecondArgRelationships(5) == expectedResultThree);
    std::unordered_set<int> expectedResultFour = {3};
    REQUIRE(followsStorage.getSecondArgRelationships(6) == expectedResultFour);

    REQUIRE(followsStorage.getSecondArgRelationships(4) == emptyResult);
    REQUIRE(followsStorage.getSecondArgRelationships(100) == emptyResult);
  }

  SECTION("test for follows Storage") {
    ParentOperationStorage parentStorage;
    std::unordered_set<int> expectedResult = {1};
    std::unordered_set<int> unExpectedResult = {100};
    std::unordered_set<int> emptyResult = {};
    // store single parent relationship
    parentStorage.storeInformation(1, 2);
    REQUIRE(parentStorage.getSecondArgRelationships(2) == expectedResult);
    REQUIRE_FALSE(parentStorage.getSecondArgRelationships(2) ==
                  unExpectedResult);
    REQUIRE(parentStorage.getSecondArgRelationships(100) == emptyResult);
    REQUIRE(parentStorage.getSecondArgRelationships(1) == emptyResult);

    parentStorage.storeInformation(2, 3);
    parentStorage.storeInformation(4, 5);
    parentStorage.storeInformation(3, 6);

    std::unordered_set<int> expectedResultTwo = {2};
    REQUIRE(parentStorage.getSecondArgRelationships(3) == expectedResultTwo);
    std::unordered_set<int> expectedResultThree = {4};
    REQUIRE(parentStorage.getSecondArgRelationships(5) == expectedResultThree);
    std::unordered_set<int> expectedResultFour = {3};
    REQUIRE(parentStorage.getSecondArgRelationships(6) == expectedResultFour);

    REQUIRE(parentStorage.getSecondArgRelationships(4) == emptyResult);
    REQUIRE(parentStorage.getSecondArgRelationships(100) == emptyResult);
  }

  SECTION("test uses Procedure Storage") {
    UsesProcedureOperationStorage usesStorage;
    std::unordered_set<std::string> expectedResult = {"proc"};
    std::unordered_set<std::string> unExpectedResult = {"unexpected"};
    std::unordered_set<std::string> emptyResult = {};

    // store single uses relationship
    usesStorage.storeInformation("proc", "x");
    REQUIRE(usesStorage.getSecondArgRelationships("x") == expectedResult);
    REQUIRE_FALSE(usesStorage.getSecondArgRelationships("x") ==
                  unExpectedResult);
    REQUIRE(usesStorage.getSecondArgRelationships("nonRelation") ==
            emptyResult);
    REQUIRE(usesStorage.getSecondArgRelationships("proc") == emptyResult);

    usesStorage.storeInformation("proc2", "count");
    usesStorage.storeInformation("proc2", "it");
    usesStorage.storeInformation("main", "x");
    std::unordered_set<std::string> expectedResultTwo = {"proc2"};
    REQUIRE(usesStorage.getSecondArgRelationships("count") ==
            expectedResultTwo);
    REQUIRE(usesStorage.getSecondArgRelationships("it") == expectedResultTwo);
    std::unordered_set<std::string> expectedResultThree = {"main", "proc"};
    REQUIRE(usesStorage.getSecondArgRelationships("x") == expectedResultThree);

    REQUIRE(usesStorage.getSecondArgRelationships("noRelation") == emptyResult);
    REQUIRE(usesStorage.getSecondArgRelationships("proc2") == emptyResult);
  }

  SECTION("test modifies Storage") {
    ModifiesProcedureOperationStorage modifiesProcedureStorage;
    std::unordered_set<std::string> expectedResult = {"proc"};
    std::unordered_set<std::string> unExpectedResult = {"unexpected"};
    std::unordered_set<std::string> emptyResult = {};

    // store single uses relationship
    modifiesProcedureStorage.storeInformation("proc", "x");
    REQUIRE(modifiesProcedureStorage.getSecondArgRelationships("x") ==
            expectedResult);
    REQUIRE_FALSE(modifiesProcedureStorage.getSecondArgRelationships("x") ==
                  unExpectedResult);
    REQUIRE(modifiesProcedureStorage.getSecondArgRelationships("nonRelation") ==
            emptyResult);
    REQUIRE(modifiesProcedureStorage.getSecondArgRelationships("proc") ==
            emptyResult);

    modifiesProcedureStorage.storeInformation("proc2", "count");
    modifiesProcedureStorage.storeInformation("proc2", "it");
    modifiesProcedureStorage.storeInformation("main", "x");
    std::unordered_set<std::string> expectedResultTwo = {"proc2"};
    REQUIRE(modifiesProcedureStorage.getSecondArgRelationships("count") ==
            expectedResultTwo);
    REQUIRE(modifiesProcedureStorage.getSecondArgRelationships("it") ==
            expectedResultTwo);
    std::unordered_set<std::string> expectedResultThree = {"main", "proc"};
    REQUIRE(modifiesProcedureStorage.getSecondArgRelationships("x") ==
            expectedResultThree);

    REQUIRE(modifiesProcedureStorage.getSecondArgRelationships("noRelation") ==
            emptyResult);
    REQUIRE(modifiesProcedureStorage.getSecondArgRelationships("proc2") ==
            emptyResult);
  }

  SECTION("test calls Storage") {
    CallsOperationStorage callsStorage;
    std::unordered_set<std::string> expectedResult = {"proc"};
    std::unordered_set<std::string> unExpectedResult = {"unexpected"};
    std::unordered_set<std::string> emptyResult = {};

    // store single uses relationship
    callsStorage.storeInformation("proc", "x");
    REQUIRE(callsStorage.getSecondArgRelationships("x") == expectedResult);
    REQUIRE_FALSE(callsStorage.getSecondArgRelationships("x") ==
                  unExpectedResult);
    REQUIRE(callsStorage.getSecondArgRelationships("nonRelation") ==
            emptyResult);
    REQUIRE(callsStorage.getSecondArgRelationships("proc") == emptyResult);

    callsStorage.storeInformation("proc2", "count");
    callsStorage.storeInformation("proc2", "it");
    callsStorage.storeInformation("main", "x");
    std::unordered_set<std::string> expectedResultTwo = {"proc2"};
    REQUIRE(callsStorage.getSecondArgRelationships("count") ==
            expectedResultTwo);
    REQUIRE(callsStorage.getSecondArgRelationships("it") == expectedResultTwo);
    std::unordered_set<std::string> expectedResultThree = {"main", "proc"};
    REQUIRE(callsStorage.getSecondArgRelationships("x") == expectedResultThree);

    REQUIRE(callsStorage.getSecondArgRelationships("noRelation") ==
            emptyResult);
    REQUIRE(callsStorage.getSecondArgRelationships("proc2") == emptyResult);
  }

  SECTION("test for next Storage") {
    NextOperationStorage nextStorage;
    std::unordered_set<int> expectedResult = {1};
    std::unordered_set<int> unExpectedResult = {100};
    std::unordered_set<int> emptyResult = {};
    // store single parent relationship
    nextStorage.storeInformation(1, 2);
    REQUIRE(nextStorage.getSecondArgRelationships(2) == expectedResult);
    REQUIRE_FALSE(nextStorage.getSecondArgRelationships(2) == unExpectedResult);
    REQUIRE(nextStorage.getSecondArgRelationships(100) == emptyResult);
    REQUIRE(nextStorage.getSecondArgRelationships(1) == emptyResult);

    nextStorage.storeInformation(2, 3);
    nextStorage.storeInformation(4, 5);
    nextStorage.storeInformation(3, 6);

    std::unordered_set<int> expectedResultTwo = {2};
    REQUIRE(nextStorage.getSecondArgRelationships(3) == expectedResultTwo);
    std::unordered_set<int> expectedResultThree = {4};
    REQUIRE(nextStorage.getSecondArgRelationships(5) == expectedResultThree);
    std::unordered_set<int> expectedResultFour = {3};
    REQUIRE(nextStorage.getSecondArgRelationships(6) == expectedResultFour);

    REQUIRE(nextStorage.getSecondArgRelationships(4) == emptyResult);
    REQUIRE(nextStorage.getSecondArgRelationships(100) == emptyResult);
  }
}
