//
// Created by Volunteer The on 11/9/23.
//

#include "catch.hpp"
#include "pkb/no_clause/design_entities/AssignEntityStorage.h"
#include "pkb/no_clause/design_entities/CallStatementEntityStorage.h"
#include "pkb/no_clause/design_entities/ConstantEntityStorage.h"
#include "pkb/no_clause/design_entities/IfEntityStorage.h"
#include "pkb/no_clause/design_entities/PrintStatementEntityStorage.h"
#include "pkb/no_clause/design_entities/ProcedureEntityStorage.h"
#include "pkb/no_clause/design_entities/ReadStatementEntityStorage.h"
#include "pkb/no_clause/design_entities/StatementEntityStorage.h"
#include "pkb/no_clause/design_entities/VariableEntityStorage.h"
#include "pkb/no_clause/design_entities/WhileEntityStorage.h"

using namespace PKB;

TEST_CASE("Test empty Entities") {
  // int Entities
  SECTION("Test Statement Entity Storage") {
    StatementEntityStorage storage;
    StatementEntityStorage emptyStorage;

    REQUIRE(storage.empty());
    storage.storeEntity(1);
    REQUIRE_FALSE(storage.empty());
    storage.storeEntity(2);
    storage.storeEntity(3);
    REQUIRE_FALSE(storage.empty());
    REQUIRE(emptyStorage.empty());
  }

  SECTION("Test Assign Entity") {
    AssignEntityStorage storage;
    AssignEntityStorage emptyStorage;

    REQUIRE(storage.empty());
    storage.storeEntity(1);
    REQUIRE_FALSE(storage.empty());
    storage.storeEntity(2);
    storage.storeEntity(3);
    REQUIRE_FALSE(storage.empty());
    REQUIRE(emptyStorage.empty());
  }

  SECTION("Test Call Statement Entity") {
    CallStatementEntityStorage storage;
    CallStatementEntityStorage emptyStorage;

    REQUIRE(storage.empty());
    storage.storeEntity(CallEntity(1, "PLACEHOLDER"));
    REQUIRE_FALSE(storage.empty());
    storage.storeEntity(CallEntity(2, "PLACEHOLDER"));
    storage.storeEntity(CallEntity(3, "PLACEHOLDER"));
    REQUIRE_FALSE(storage.empty());
    REQUIRE(emptyStorage.empty());
  }
  SECTION("Test If Entity") {
    IfEntityStorage storage;
    IfEntityStorage emptyStorage;

    REQUIRE(storage.empty());
    storage.storeEntity(1);
    REQUIRE_FALSE(storage.empty());
    storage.storeEntity(2);
    storage.storeEntity(3);
    REQUIRE_FALSE(storage.empty());
    REQUIRE(emptyStorage.empty());
  }
  SECTION("Test Print Statement Entity") {
    PrintStatementEntityStorage storage;
    PrintStatementEntityStorage emptyStorage;

    REQUIRE(storage.empty());
    storage.storeEntity(PrintEntity(1, "PLACEHOLDER"));
    REQUIRE_FALSE(storage.empty());
    storage.storeEntity(PrintEntity(2, "PLACEHOLDER"));
    storage.storeEntity(PrintEntity(3, "PLACEHOLDER"));
    REQUIRE_FALSE(storage.empty());
    REQUIRE(emptyStorage.empty());
  }

  SECTION("Test Read Statement Entity") {
    ReadStatementEntityStorage storage;
    ReadStatementEntityStorage emptyStorage;

    REQUIRE(storage.empty());
    storage.storeEntity(ReadEntity(1, "PLACEHOLDER"));
    REQUIRE_FALSE(storage.empty());
    storage.storeEntity(ReadEntity(2, "PLACEHOLDER"));
    storage.storeEntity(ReadEntity(3, "PLACEHOLDER"));
    REQUIRE_FALSE(storage.empty());
    REQUIRE(emptyStorage.empty());
  }

  SECTION("Test While Entity") {
    WhileEntityStorage storage;
    WhileEntityStorage emptyStorage;

    REQUIRE(storage.empty());
    storage.storeEntity(1);
    REQUIRE_FALSE(storage.empty());
    storage.storeEntity(2);
    storage.storeEntity(3);
    REQUIRE_FALSE(storage.empty());
    REQUIRE(emptyStorage.empty());
  }
  // std::string storages
  SECTION("Test Procedure Entity") {
    ProcedureEntityStorage storage;
    ProcedureEntityStorage emptyStorage;

    REQUIRE(storage.empty());
    storage.storeEntity("one");
    REQUIRE_FALSE(storage.empty());
    storage.storeEntity("two");
    storage.storeEntity("three");
    REQUIRE_FALSE(storage.empty());
    REQUIRE(emptyStorage.empty());
  }
  SECTION("Test Constant Entity") {
    ConstantEntityStorage storage;
    ConstantEntityStorage emptyStorage;

    REQUIRE(storage.empty());
    storage.storeEntity("one");
    REQUIRE_FALSE(storage.empty());
    storage.storeEntity("two");
    storage.storeEntity("three");
    REQUIRE_FALSE(storage.empty());
    REQUIRE(emptyStorage.empty());
  }

  SECTION("Test Variable Entity") {
    VariableEntityStorage storage;
    VariableEntityStorage emptyStorage;

    REQUIRE(storage.empty());
    storage.storeEntity("one");
    REQUIRE_FALSE(storage.empty());
    storage.storeEntity("two");
    storage.storeEntity("three");
    REQUIRE_FALSE(storage.empty());
    REQUIRE(emptyStorage.empty());
  }
}
