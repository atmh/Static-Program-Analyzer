//
// Created by Ramapriyan Srivatsan PD on 10/10/23.
//
#include "catch.hpp"
#include "pkb/utils/entity_structs/CallEntity.h"
#include "pkb/utils/entity_structs/PrintEntity.h"
#include "pkb/utils/entity_structs/ReadEntity.h"

using namespace PKB;

TEST_CASE("Call Entity Tests") {
  CallEntity entityOne = CallEntity(1, "proc");
  CallEntity entityTwo = CallEntity(2, "proc_two");
  CallEntity entityThree = CallEntity(3, "proc");
  CallEntity entityOneCopy = CallEntity(1, "proc");
  CallEntity entityTwoPartialCopy = CallEntity(2, "proc");

  REQUIRE(entityOne.getStmtNo() == 1);
  REQUIRE(entityTwo.getStmtNo() == 2);
  REQUIRE(entityOne.getProcName() == "proc");
  REQUIRE_FALSE(entityTwo.getProcName() == "proc");
  REQUIRE_FALSE(entityOne == entityThree);
  REQUIRE_FALSE(entityOne == entityTwo);
  REQUIRE(entityOne == entityOneCopy);
  REQUIRE_FALSE(entityTwo == entityTwoPartialCopy);
}

TEST_CASE("Print Entity Tests") {
  PrintEntity entityOne = PrintEntity(1, "var");
  PrintEntity entityTwo = PrintEntity(2, "var_two");
  PrintEntity entityThree = PrintEntity(3, "var");
  PrintEntity entityOneCopy = PrintEntity(1, "var");
  PrintEntity entityTwoPartialCopy = PrintEntity(2, "var");

  REQUIRE(entityOne.getStmtNo() == 1);
  REQUIRE(entityTwo.getStmtNo() == 2);
  REQUIRE(entityOne.getVarName() == "var");
  REQUIRE_FALSE(entityTwo.getVarName() == "var");
  REQUIRE_FALSE(entityOne == entityThree);
  REQUIRE_FALSE(entityOne == entityTwo);
  REQUIRE(entityOne == entityOneCopy);
  REQUIRE_FALSE(entityTwo == entityTwoPartialCopy);
}

TEST_CASE("Read Entity Tests") {
  ReadEntity entityOne = ReadEntity(1, "var");
  ReadEntity entityTwo = ReadEntity(2, "var_two");
  ReadEntity entityThree = ReadEntity(3, "var");
  ReadEntity entityOneCopy = ReadEntity(1, "var");
  ReadEntity entityTwoPartialCopy = ReadEntity(2, "var");

  REQUIRE(entityOne.getStmtNo() == 1);
  REQUIRE(entityTwo.getStmtNo() == 2);
  REQUIRE(entityOne.getVarName() == "var");
  REQUIRE_FALSE(entityTwo.getVarName() == "var");
  REQUIRE_FALSE(entityOne == entityThree);
  REQUIRE_FALSE(entityOne == entityTwo);
  REQUIRE(entityOne == entityOneCopy);
  REQUIRE_FALSE(entityTwo == entityTwoPartialCopy);
}
