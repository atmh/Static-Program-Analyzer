//
// Created by Volunteer The on 11/9/23.
//

#include "catch.hpp"
#include "pkb/no_clause/NoClauseStorage.h"
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

TEST_CASE("Test store Entities") {
  // int Entities
  SECTION("Test Statement Entity Storage") {
    StatementEntityStorage statementsStorage;
    // test single entry
    std::unordered_set<int> expected = {1};
    std::unordered_set<int> nonExpected = {};
    statementsStorage.storeEntity(1);
    REQUIRE(statementsStorage.getAllEntities() == expected);
    REQUIRE_FALSE(statementsStorage.getAllEntities() == nonExpected);

    // test multiple entries
    std::unordered_set<int> expectedMultiple = {1, 2, 3};
    statementsStorage.storeEntity(2);
    statementsStorage.storeEntity(3);
    REQUIRE(statementsStorage.getAllEntities() == expectedMultiple);

    // test storing duplicate entity
    REQUIRE(statementsStorage.getAllEntities().size() == 3);
    statementsStorage.storeEntity(2);
    REQUIRE(statementsStorage.getAllEntities().size() == 3);
  }

  SECTION("Test Assign Entity") {
    AssignEntityStorage assignStorage;
    // test single entry
    std::unordered_set<int> expected = {1};
    std::unordered_set<int> nonExpected = {};
    assignStorage.storeEntity(1);
    REQUIRE(assignStorage.getAllEntities() == expected);
    REQUIRE_FALSE(assignStorage.getAllEntities() == nonExpected);

    // test multiple entries
    std::unordered_set<int> expectedMultiple = {1, 2, 3};
    assignStorage.storeEntity(2);
    assignStorage.storeEntity(3);
    REQUIRE(assignStorage.getAllEntities() == expectedMultiple);

    // test storing duplicate entities
    REQUIRE(assignStorage.getAllEntities().size() == 3);
    assignStorage.storeEntity(2);
    REQUIRE(assignStorage.getAllEntities().size() == 3);
  }

  SECTION("Test Call Statement Entity") {
    CallStatementEntityStorage callStatementStorage;
    // test single entry
    std::unordered_set<int> expected = {1};
    std::unordered_set<int> nonExpected = {};
    callStatementStorage.storeEntity(CallEntity(1, "PLACEHOLDER"));
    REQUIRE(callStatementStorage.getStmtNos() == expected);
    REQUIRE_FALSE(callStatementStorage.getStmtNos() == nonExpected);

    // test multiple entries
    std::unordered_set<int> expectedMultiple = {1, 2, 3};
    callStatementStorage.storeEntity(CallEntity(2, "PLACEHOLDER"));
    callStatementStorage.storeEntity(CallEntity(2, "proc"));
    callStatementStorage.storeEntity(CallEntity(3, "PLACEHOLDER"));
    REQUIRE(callStatementStorage.getStmtNos() == expectedMultiple);

    // test storing duplicate entity
    REQUIRE(callStatementStorage.getAllEntities().size() == 4);
    callStatementStorage.storeEntity(CallEntity(2, "PLACEHOLDER"));
    REQUIRE(callStatementStorage.getAllEntities().size() == 4);
  }

  SECTION("Test If Entity") {
    IfEntityStorage ifStorage;
    // test single entry
    std::unordered_set<int> expected = {1};
    std::unordered_set<int> nonExpected = {};
    ifStorage.storeEntity(1);
    REQUIRE(ifStorage.getAllEntities() == expected);
    REQUIRE_FALSE(ifStorage.getAllEntities() == nonExpected);

    // test multiple entries
    std::unordered_set<int> expectedMultiple = {1, 2, 3};
    ifStorage.storeEntity(2);
    ifStorage.storeEntity(3);
    REQUIRE(ifStorage.getAllEntities() == expectedMultiple);

    // test storing duplicate entity
    REQUIRE(ifStorage.getAllEntities().size() == 3);
    ifStorage.storeEntity(2);
    REQUIRE(ifStorage.getAllEntities().size() == 3);
  }

  SECTION("Test Print Statement Entity") {
    PrintStatementEntityStorage printStatementStorage;
    // test single entry
    std::unordered_set<int> expected = {1};
    std::unordered_set<int> nonExpected = {};
    printStatementStorage.storeEntity(PrintEntity(1, "PLACEHOLDER"));
    REQUIRE(printStatementStorage.getStmtNos() == expected);
    REQUIRE_FALSE(printStatementStorage.getStmtNos() == nonExpected);

    // test multiple entries
    std::unordered_set<int> expectedMultiple = {1, 2, 3};
    printStatementStorage.storeEntity(PrintEntity(2, "PLACEHOLDER"));
    printStatementStorage.storeEntity(PrintEntity(2, "var"));
    printStatementStorage.storeEntity(PrintEntity(3, "PLACEHOLDER"));
    REQUIRE(printStatementStorage.getStmtNos() == expectedMultiple);

    // test storing duplicate entity
    REQUIRE(printStatementStorage.getAllEntities().size() == 4);
    printStatementStorage.storeEntity(PrintEntity(2, "PLACEHOLDER"));
    REQUIRE(printStatementStorage.getAllEntities().size() == 4);
  }

  SECTION("Test Read Statement Entity") {
    ReadStatementEntityStorage readStatementEntityStorage;
    // test single entry
    std::unordered_set<int> expected = {1};
    std::unordered_set<int> nonExpected = {};
    readStatementEntityStorage.storeEntity(ReadEntity(1, "PLACEHOLDER"));
    REQUIRE(readStatementEntityStorage.getStmtNos() == expected);
    REQUIRE_FALSE(readStatementEntityStorage.getStmtNos() == nonExpected);

    // test multiple entries
    std::unordered_set<int> expectedMultiple = {1, 2, 3};
    readStatementEntityStorage.storeEntity(ReadEntity(2, "PLACEHOLDER"));
    readStatementEntityStorage.storeEntity(ReadEntity(2, "var"));
    readStatementEntityStorage.storeEntity(ReadEntity(3, "PLACEHOLDER"));
    REQUIRE(readStatementEntityStorage.getStmtNos() == expectedMultiple);

    // test storing duplicate entity
    REQUIRE(readStatementEntityStorage.getAllEntities().size() == 4);
    readStatementEntityStorage.storeEntity(ReadEntity(2, "PLACEHOLDER"));
    REQUIRE(readStatementEntityStorage.getAllEntities().size() == 4);
  }

  SECTION("Test While Entity") {
    WhileEntityStorage whileStorage;
    // test single entry
    std::unordered_set<int> expected = {1};
    std::unordered_set<int> nonExpected = {};
    whileStorage.storeEntity(1);
    REQUIRE(whileStorage.getAllEntities() == expected);
    REQUIRE_FALSE(whileStorage.getAllEntities() == nonExpected);

    // test multiple entries
    std::unordered_set<int> expectedMultiple = {1, 2, 3};
    whileStorage.storeEntity(2);
    whileStorage.storeEntity(3);
    REQUIRE(whileStorage.getAllEntities() == expectedMultiple);

    // test storing duplicate entity
    REQUIRE(whileStorage.getAllEntities().size() == 3);
    whileStorage.storeEntity(2);
    REQUIRE(whileStorage.getAllEntities().size() == 3);
  }

  // std::string storages
  SECTION("Test Procedure Entity") {
    ProcedureEntityStorage procedureEntityStorage;
    // test single entry
    std::unordered_set<std::string> expected = {"one"};
    std::unordered_set<std::string> nonExpected = {};
    procedureEntityStorage.storeEntity("one");
    REQUIRE(procedureEntityStorage.getAllEntities() == expected);
    REQUIRE_FALSE(procedureEntityStorage.getAllEntities() == nonExpected);

    // test multiple entries
    std::unordered_set<std::string> expectedMultiple = {"one", "two", "three"};
    procedureEntityStorage.storeEntity("two");
    procedureEntityStorage.storeEntity("three");
    REQUIRE(procedureEntityStorage.getAllEntities() == expectedMultiple);
  }
  SECTION("Test Constant Entity") {
    ConstantEntityStorage constantEntityStorage;
    // test single entry
    std::unordered_set<std::string> expected = {"one"};
    std::unordered_set<std::string> nonExpected = {};
    constantEntityStorage.storeEntity("one");
    REQUIRE(constantEntityStorage.getAllEntities() == expected);
    REQUIRE_FALSE(constantEntityStorage.getAllEntities() == nonExpected);

    // test multiple entries
    std::unordered_set<std::string> expectedMultiple = {"one", "two", "three"};
    constantEntityStorage.storeEntity("two");
    constantEntityStorage.storeEntity("three");
    REQUIRE(constantEntityStorage.getAllEntities() == expectedMultiple);
  }
  SECTION("Test Variable Entity") {
    VariableEntityStorage variableStorage;
    // test single entry
    std::unordered_set<std::string> expected = {"one"};
    std::unordered_set<std::string> nonExpected = {};
    variableStorage.storeEntity("one");
    REQUIRE(variableStorage.getAllEntities() == expected);
    REQUIRE_FALSE(variableStorage.getAllEntities() == nonExpected);

    // test multiple entries
    std::unordered_set<std::string> expectedMultiple = {"one", "two", "three"};
    variableStorage.storeEntity("two");
    variableStorage.storeEntity("three");
    REQUIRE(variableStorage.getAllEntities() == expectedMultiple);
  }
}
