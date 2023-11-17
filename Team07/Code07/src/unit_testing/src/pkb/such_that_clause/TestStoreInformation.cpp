//
// Created by Volunteer The on 9/9/23.
//
//
// Created by Volunteer The on 7/9/23.
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

TEST_CASE("Test storeInformation") {
  FollowsOperationStorage followsStorage;
  ParentOperationStorage parentsStorage;
  UsesStatementOperationStorage usesStatementOperationStorage;
  UsesProcedureOperationStorage usesProcedureOperationStorage;
  ModifiesProcedureOperationStorage modifiesProcedureStorage;
  CallsOperationStorage callsStorage;
  NextOperationStorage nextStorage;

  followsStorage.storeInformation(1, 2);
  parentsStorage.storeInformation(1, 2);
  nextStorage.storeInformation(1, 2);
  usesStatementOperationStorage.storeInformation(2, "x");
  usesProcedureOperationStorage.storeInformation("proc2", "x");
  modifiesProcedureStorage.storeInformation("proc2", "x");
  callsStorage.storeInformation("proc2", "x");

  SECTION("test follows storage") {
    std::unordered_set<int> firstArgStorage =
        followsStorage.getFirstArgRelationships(1);
    REQUIRE(firstArgStorage.size() == 1);
    std::unordered_set<int> secondArgStorage =
        followsStorage.getSecondArgRelationships(2);
    REQUIRE(secondArgStorage.size() == 1);

    followsStorage.storeInformation(1, 3);
    followsStorage.storeInformation(1, 4);
    followsStorage.storeInformation(1, 5);
    followsStorage.storeInformation(6, 3);
    followsStorage.storeInformation(7, 3);
    followsStorage.storeInformation(8, 3);
    firstArgStorage = followsStorage.getFirstArgRelationships(1);
    secondArgStorage = followsStorage.getSecondArgRelationships(3);
    REQUIRE(firstArgStorage.size() == 4);
    REQUIRE(secondArgStorage.size() == 4);
    secondArgStorage = followsStorage.getSecondArgRelationships(2);
    REQUIRE(secondArgStorage.size() == 1);
  }

  SECTION("test parents storage") {
    std::unordered_set<int> firstArgStorage =
        parentsStorage.getFirstArgRelationships(1);
    REQUIRE(firstArgStorage.size() == 1);
    std::unordered_set<int> secondArgStorage =
        parentsStorage.getSecondArgRelationships(2);
    REQUIRE(secondArgStorage.size() == 1);

    parentsStorage.storeInformation(1, 3);
    parentsStorage.storeInformation(1, 4);
    parentsStorage.storeInformation(1, 5);
    parentsStorage.storeInformation(6, 3);
    parentsStorage.storeInformation(7, 3);
    parentsStorage.storeInformation(8, 3);
    firstArgStorage = parentsStorage.getFirstArgRelationships(1);
    secondArgStorage = parentsStorage.getSecondArgRelationships(3);
    REQUIRE(firstArgStorage.size() == 4);
    REQUIRE(secondArgStorage.size() == 4);
    secondArgStorage = parentsStorage.getSecondArgRelationships(2);
    REQUIRE(secondArgStorage.size() == 1);
  }

  SECTION("test uses Procedure storage") {
    std::unordered_set<std::string> firstArgStorage =
        usesProcedureOperationStorage.getFirstArgRelationships("proc2");
    REQUIRE(firstArgStorage.size() == 1);
    std::unordered_set<std::string> secondArgStorage =
        usesProcedureOperationStorage.getSecondArgRelationships("x");
    REQUIRE(secondArgStorage.size() == 1);

    usesProcedureOperationStorage.storeInformation("x", "z");
    usesProcedureOperationStorage.storeInformation("x", "a");
    usesProcedureOperationStorage.storeInformation("x", "b");
    usesProcedureOperationStorage.storeInformation("c", "y");
    usesProcedureOperationStorage.storeInformation("d", "y");
    usesProcedureOperationStorage.storeInformation("e", "y");
    firstArgStorage =
        usesProcedureOperationStorage.getFirstArgRelationships("x");
    secondArgStorage =
        usesProcedureOperationStorage.getSecondArgRelationships("y");
    REQUIRE(firstArgStorage.size() == 3);
    REQUIRE(secondArgStorage.size() == 3);
  }

  SECTION("test uses Statement storage") {
    std::unordered_set<std::string> firstArgStorage =
        usesStatementOperationStorage.getFirstArgRelationships(2);
    REQUIRE(firstArgStorage.size() == 1);
    std::unordered_set<int> secondArgStorage =
        usesStatementOperationStorage.getSecondArgRelationships("x");
    REQUIRE(secondArgStorage.size() == 1);

    usesStatementOperationStorage.storeInformation(5, "z");
    usesStatementOperationStorage.storeInformation(5, "a");
    usesStatementOperationStorage.storeInformation(5, "b");
    usesStatementOperationStorage.storeInformation(8, "y");
    usesStatementOperationStorage.storeInformation(9, "y");
    usesStatementOperationStorage.storeInformation(10, "y");
    firstArgStorage = usesStatementOperationStorage.getFirstArgRelationships(5);
    secondArgStorage =
        usesStatementOperationStorage.getSecondArgRelationships("y");
    REQUIRE(firstArgStorage.size() == 3);
    REQUIRE(secondArgStorage.size() == 3);
    secondArgStorage =
        usesStatementOperationStorage.getSecondArgRelationships("z");
    REQUIRE(secondArgStorage.size() == 1);
  }

  SECTION("test uses Procedure storage") {
    std::unordered_set<std::string> firstArgStorage =
        usesProcedureOperationStorage.getFirstArgRelationships("proc2");
    REQUIRE(firstArgStorage.size() == 1);
    std::unordered_set<std::string> secondArgStorage =
        usesProcedureOperationStorage.getSecondArgRelationships("x");
    REQUIRE(secondArgStorage.size() == 1);

    usesProcedureOperationStorage.storeInformation("x", "z");
    usesProcedureOperationStorage.storeInformation("x", "a");
    usesProcedureOperationStorage.storeInformation("x", "b");
    usesProcedureOperationStorage.storeInformation("c", "y");
    usesProcedureOperationStorage.storeInformation("d", "y");
    usesProcedureOperationStorage.storeInformation("e", "y");
    firstArgStorage =
        usesProcedureOperationStorage.getFirstArgRelationships("x");
    secondArgStorage =
        usesProcedureOperationStorage.getSecondArgRelationships("y");
    REQUIRE(firstArgStorage.size() == 3);
    REQUIRE(secondArgStorage.size() == 3);
  }

  SECTION("test calls storage") {
    std::unordered_set<std::string> firstArgStorage =
        callsStorage.getFirstArgRelationships("proc2");
    REQUIRE(firstArgStorage.size() == 1);
    std::unordered_set<std::string> secondArgStorage =
        callsStorage.getSecondArgRelationships("x");
    REQUIRE(secondArgStorage.size() == 1);

    callsStorage.storeInformation("x", "z");
    callsStorage.storeInformation("x", "a");
    callsStorage.storeInformation("x", "b");
    callsStorage.storeInformation("c", "y");
    callsStorage.storeInformation("d", "y");
    callsStorage.storeInformation("e", "y");
    firstArgStorage = callsStorage.getFirstArgRelationships("x");
    secondArgStorage = callsStorage.getSecondArgRelationships("y");
    REQUIRE(firstArgStorage.size() == 3);
    REQUIRE(secondArgStorage.size() == 3);
  }

  SECTION("test next storage") {
    std::unordered_set<int> firstArgStorage =
        nextStorage.getFirstArgRelationships(1);
    REQUIRE(firstArgStorage.size() == 1);
    std::unordered_set<int> secondArgStorage =
        nextStorage.getSecondArgRelationships(2);
    REQUIRE(secondArgStorage.size() == 1);

    nextStorage.storeInformation(1, 3);
    nextStorage.storeInformation(1, 4);
    nextStorage.storeInformation(1, 5);
    nextStorage.storeInformation(6, 3);
    nextStorage.storeInformation(7, 3);
    nextStorage.storeInformation(8, 3);
    firstArgStorage = nextStorage.getFirstArgRelationships(1);
    secondArgStorage = nextStorage.getSecondArgRelationships(3);
    REQUIRE(firstArgStorage.size() == 4);
    REQUIRE(secondArgStorage.size() == 4);
    secondArgStorage = nextStorage.getSecondArgRelationships(2);
    REQUIRE(secondArgStorage.size() == 1);
  }
}
