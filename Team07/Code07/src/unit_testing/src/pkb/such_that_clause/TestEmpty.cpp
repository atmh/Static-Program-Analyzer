//
// Created by Volunteer The on 9/9/23.
//
//
// Created by Volunteer The on 7/9/23.
//
#include "catch.hpp"
#include "pkb/such_that_clause/SuchThatStorage.h"
#include "pkb/such_that_clause/operations/FollowsOperationStorage.h"
#include "pkb/such_that_clause/operations/ModifiesProcedureOperationStorage.h"
#include "pkb/such_that_clause/operations/ParentOperationStorage.h"
#include "pkb/such_that_clause/operations/UsesStatementOperationStorage.h"
#include "pkb/utils/BiDirectionalMap.h"

using namespace PKB;

TEST_CASE("Test empty") {
  FollowsOperationStorage followsStorage;
  ParentOperationStorage parentsStorage;
  UsesStatementOperationStorage usesStatementOperationStorage;
  ModifiesProcedureOperationStorage modifiesProcedureStorage;

  FollowsOperationStorage emptyFollowsStorage;
  ParentOperationStorage emptyParentsStorage;
  UsesStatementOperationStorage emptyUsesStorage;
  ModifiesProcedureOperationStorage emptyModifiesProcedureStorage;

  followsStorage.storeInformation(1, 2);
  parentsStorage.storeInformation(1, 2);
  usesStatementOperationStorage.storeInformation(2, "x");
  modifiesProcedureStorage.storeInformation("2", "x");

  SECTION("Test empty") {
    REQUIRE_FALSE(followsStorage.empty());
    REQUIRE(emptyFollowsStorage.empty());
    REQUIRE_FALSE(parentsStorage.empty());
    REQUIRE(emptyParentsStorage.empty());
    REQUIRE_FALSE(usesStatementOperationStorage.empty());
    REQUIRE(emptyUsesStorage.empty());
    REQUIRE_FALSE(modifiesProcedureStorage.empty());
    REQUIRE(emptyModifiesProcedureStorage.empty());
  }
}
