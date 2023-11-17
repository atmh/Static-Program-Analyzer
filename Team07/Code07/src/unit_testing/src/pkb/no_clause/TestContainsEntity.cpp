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

TEST_CASE("Test contains Entities") {
  // int Entities
  SECTION("Test Statement Entity Storage") {
    StatementEntityStorage storage;
    storage.storeEntity(1);
    // test single entry
    REQUIRE(storage.contains(1));
    REQUIRE_FALSE(storage.contains(2));

    // test multiple entries
    storage.storeEntity(2);
    storage.storeEntity(3);
    REQUIRE(storage.contains(2));
    REQUIRE(storage.contains(3));
    REQUIRE_FALSE(storage.contains(4));
  }

  SECTION("Test Assign Entity") {
    AssignEntityStorage storage;
    storage.storeEntity(1);
    // test single entry
    REQUIRE(storage.contains(1));
    REQUIRE_FALSE(storage.contains(2));

    // test multiple entries
    storage.storeEntity(2);
    storage.storeEntity(3);
    REQUIRE(storage.contains(2));
    REQUIRE(storage.contains(3));
    REQUIRE_FALSE(storage.contains(4));
  }

  SECTION("Test Call Statement Entity") {
    CallStatementEntityStorage storage;
    storage.storeEntity(CallEntity(1, "PLACEHOLDER"));
    // test single entry
    REQUIRE(storage.contains(CallEntity(1, "PLACEHOLDER")));
    REQUIRE_FALSE(storage.contains(CallEntity(2, "PLACEHOLDER")));

    // test multiple entries
    storage.storeEntity(CallEntity(2, "PLACEHOLDER"));
    storage.storeEntity(CallEntity(3, "PLACEHOLDER"));
    storage.storeEntity(CallEntity(2, "proc"));
    REQUIRE(storage.contains(CallEntity(2, "PLACEHOLDER")));
    REQUIRE(storage.contains(CallEntity(2, "proc")));
    REQUIRE(storage.contains(CallEntity(3, "PLACEHOLDER")));
    REQUIRE_FALSE(storage.contains(CallEntity(4, "PLACEHOLDER")));
  }
  SECTION("Test If Entity") {
    IfEntityStorage storage;
    storage.storeEntity(1);
    // test single entry
    REQUIRE(storage.contains(1));
    REQUIRE_FALSE(storage.contains(2));

    // test multiple entries
    storage.storeEntity(2);
    storage.storeEntity(3);
    REQUIRE(storage.contains(2));
    REQUIRE(storage.contains(3));
    REQUIRE_FALSE(storage.contains(4));
  }
  SECTION("Test Print Statement Entity") {
    PrintStatementEntityStorage storage;
    storage.storeEntity(PrintEntity(1, "PLACEHOLDER"));
    // test single entry
    REQUIRE(storage.contains(PrintEntity(1, "PLACEHOLDER")));
    REQUIRE_FALSE(storage.contains(PrintEntity(2, "PLACEHOLDER")));

    // test multiple entries
    storage.storeEntity(PrintEntity(2, "PLACEHOLDER"));
    storage.storeEntity(PrintEntity(3, "PLACEHOLDER"));
    storage.storeEntity(PrintEntity(2, "var"));
    REQUIRE(storage.contains(PrintEntity(2, "PLACEHOLDER")));
    REQUIRE(storage.contains(PrintEntity(2, "var")));
    REQUIRE(storage.contains(PrintEntity(3, "PLACEHOLDER")));
    REQUIRE_FALSE(storage.contains(PrintEntity(4, "PLACEHOLDER")));
  }

  SECTION("Test Read Statement Entity") {
    ReadStatementEntityStorage storage;
    storage.storeEntity(ReadEntity(1, "PLACEHOLDER"));
    // test single entry
    REQUIRE(storage.contains(ReadEntity(1, "PLACEHOLDER")));
    REQUIRE_FALSE(storage.contains(ReadEntity(2, "PLACEHOLDER")));

    // test multiple entries
    storage.storeEntity(ReadEntity(2, "PLACEHOLDER"));
    storage.storeEntity(ReadEntity(3, "PLACEHOLDER"));
    storage.storeEntity(ReadEntity(2, "var"));
    REQUIRE(storage.contains(ReadEntity(2, "PLACEHOLDER")));
    REQUIRE(storage.contains(ReadEntity(2, "var")));
    REQUIRE(storage.contains(ReadEntity(3, "PLACEHOLDER")));
    REQUIRE_FALSE(storage.contains(ReadEntity(4, "PLACEHOLDER")));
  }
  SECTION("Test While Entity") {
    WhileEntityStorage storage;
    storage.storeEntity(1);
    // test single entry
    REQUIRE(storage.contains(1));
    REQUIRE_FALSE(storage.contains(2));

    // test multiple entries
    storage.storeEntity(2);
    storage.storeEntity(3);
    REQUIRE(storage.contains(2));
    REQUIRE(storage.contains(3));
    REQUIRE_FALSE(storage.contains(4));
  }
  // std::string storages
  SECTION("Test Procedure Entity") {
    ProcedureEntityStorage storage;
    storage.storeEntity("one");
    // test single entry
    REQUIRE(storage.contains("one"));
    REQUIRE_FALSE(storage.contains("two"));

    // test multiple entries
    storage.storeEntity("two");
    storage.storeEntity("three");
    REQUIRE(storage.contains("two"));
    REQUIRE(storage.contains("three"));
    REQUIRE_FALSE(storage.contains("four"));
  }
  SECTION("Test Constant Entity") {
    ConstantEntityStorage storage;
    storage.storeEntity("one");
    // test single entry
    REQUIRE(storage.contains("one"));
    REQUIRE_FALSE(storage.contains("two"));

    // test multiple entries
    storage.storeEntity("two");
    storage.storeEntity("three");
    REQUIRE(storage.contains("two"));
    REQUIRE(storage.contains("three"));
    REQUIRE_FALSE(storage.contains("four"));
  }

  SECTION("Test Variable Entity") {
    VariableEntityStorage storage;
    storage.storeEntity("one");
    // test single entry
    REQUIRE(storage.contains("one"));
    REQUIRE_FALSE(storage.contains("two"));

    // test multiple entries
    storage.storeEntity("two");
    storage.storeEntity("three");
    REQUIRE(storage.contains("two"));
    REQUIRE(storage.contains("three"));
    REQUIRE_FALSE(storage.contains("four"));
  }
}
