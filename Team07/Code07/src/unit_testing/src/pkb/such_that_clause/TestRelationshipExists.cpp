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
#include "pkb/such_that_clause/operations/UsesStatementOperationStorage.h"
#include "pkb/utils/BiDirectionalMap.h"

using namespace PKB;

TEST_CASE("Test RelationshipExists") {
  SECTION("test follows Storage") {
    FollowsOperationStorage followsStorage;

    // store single follows relationship
    followsStorage.storeInformation(1, 2);
    REQUIRE(followsStorage.getRelationshipExists(1, 2));
    REQUIRE_FALSE(followsStorage.getRelationshipExists(1, 5));
    REQUIRE_FALSE(followsStorage.getRelationshipExists(2, 1));

    followsStorage.storeInformation(2, 3);
    followsStorage.storeInformation(4, 5);
    followsStorage.storeInformation(3, 6);
    REQUIRE(followsStorage.getRelationshipExists(2, 3));
    REQUIRE(followsStorage.getRelationshipExists(4, 5));
    REQUIRE(followsStorage.getRelationshipExists(3, 6));
    REQUIRE_FALSE(followsStorage.getRelationshipExists(2, 6));
    REQUIRE_FALSE(followsStorage.getRelationshipExists(5, 6));
  }

  SECTION("test parents Storage") {
    ParentOperationStorage parentStorage;

    // store single parents relationship
    parentStorage.storeInformation(1, 2);
    REQUIRE(parentStorage.getRelationshipExists(1, 2));
    REQUIRE_FALSE(parentStorage.getRelationshipExists(1, 5));
    REQUIRE_FALSE(parentStorage.getRelationshipExists(2, 1));

    parentStorage.storeInformation(2, 3);
    parentStorage.storeInformation(4, 5);
    parentStorage.storeInformation(3, 6);
    REQUIRE(parentStorage.getRelationshipExists(2, 3));
    REQUIRE(parentStorage.getRelationshipExists(4, 5));
    REQUIRE(parentStorage.getRelationshipExists(3, 6));
    REQUIRE_FALSE(parentStorage.getRelationshipExists(2, 6));
    REQUIRE_FALSE(parentStorage.getRelationshipExists(5, 6));
  }

  SECTION("test uses Storage") {
    UsesStatementOperationStorage usesStorage;

    // store single uses relationship
    usesStorage.storeInformation(7, "x");
    REQUIRE(usesStorage.getRelationshipExists(7, "x"));
    REQUIRE_FALSE(usesStorage.getRelationshipExists(7, "a"));
    REQUIRE_FALSE(usesStorage.getRelationshipExists(11, "a"));

    usesStorage.storeInformation(10, "count");
    usesStorage.storeInformation(10, "it");
    REQUIRE(usesStorage.getRelationshipExists(10, "count"));
    REQUIRE(usesStorage.getRelationshipExists(10, "it"));
    REQUIRE_FALSE(usesStorage.getRelationshipExists(10, "x"));
    REQUIRE_FALSE(usesStorage.getRelationshipExists(101, "it"));
  }

  SECTION("test modifies procedure Storage") {
    ModifiesProcedureOperationStorage modifiesProcedureStorage;

    // store single uses relationship
    modifiesProcedureStorage.storeInformation("proc", "x");
    REQUIRE(modifiesProcedureStorage.getRelationshipExists("proc", "x"));
    REQUIRE_FALSE(modifiesProcedureStorage.getRelationshipExists("proc", "a"));
    REQUIRE_FALSE(modifiesProcedureStorage.getRelationshipExists("x", "proc"));

    modifiesProcedureStorage.storeInformation("func", "count");
    modifiesProcedureStorage.storeInformation("func", "it");
    modifiesProcedureStorage.storeInformation("main", "x");
    REQUIRE(modifiesProcedureStorage.getRelationshipExists("func", "count"));
    REQUIRE(modifiesProcedureStorage.getRelationshipExists("func", "it"));
    REQUIRE(modifiesProcedureStorage.getRelationshipExists("main", "x"));
    REQUIRE_FALSE(modifiesProcedureStorage.getRelationshipExists("func", "x"));
    REQUIRE_FALSE(
        modifiesProcedureStorage.getRelationshipExists("count", "it"));
  }

  SECTION("test calls Storage") {
    CallsOperationStorage callsStorage;

    // store single uses relationship
    callsStorage.storeInformation("proc", "x");
    REQUIRE(callsStorage.getRelationshipExists("proc", "x"));
    REQUIRE_FALSE(callsStorage.getRelationshipExists("proc", "a"));
    REQUIRE_FALSE(callsStorage.getRelationshipExists("x", "proc"));

    callsStorage.storeInformation("func", "count");
    callsStorage.storeInformation("func", "it");
    callsStorage.storeInformation("main", "x");
    REQUIRE(callsStorage.getRelationshipExists("func", "count"));
    REQUIRE(callsStorage.getRelationshipExists("func", "it"));
    REQUIRE(callsStorage.getRelationshipExists("main", "x"));
    REQUIRE_FALSE(callsStorage.getRelationshipExists("func", "x"));
    REQUIRE_FALSE(callsStorage.getRelationshipExists("count", "it"));
  }

  SECTION("test next Storage") {
    NextOperationStorage nextStorage;

    // store single parents relationship
    nextStorage.storeInformation(1, 2);
    REQUIRE(nextStorage.getRelationshipExists(1, 2));
    REQUIRE_FALSE(nextStorage.getRelationshipExists(1, 5));
    REQUIRE_FALSE(nextStorage.getRelationshipExists(2, 1));

    nextStorage.storeInformation(2, 3);
    nextStorage.storeInformation(4, 5);
    nextStorage.storeInformation(3, 6);
    REQUIRE(nextStorage.getRelationshipExists(2, 3));
    REQUIRE(nextStorage.getRelationshipExists(4, 5));
    REQUIRE(nextStorage.getRelationshipExists(3, 6));
    REQUIRE_FALSE(nextStorage.getRelationshipExists(2, 6));
    REQUIRE_FALSE(nextStorage.getRelationshipExists(5, 6));
  }
}
