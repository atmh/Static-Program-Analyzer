//
// Created by Volunteer The on 8/9/23.
//
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "catch.hpp"
#include "pkb/PKBStorageAPI.h"

using namespace PKB;

TEST_CASE("test relationships") {
  std::shared_ptr<PKBStorageAPI> pkbStorageAPI =
      std::make_shared<PKBStorageAPI>();
  std::shared_ptr<PKBStorageWriteInterface> pkbWrite =
      pkbStorageAPI->getWriteStorage();
  std::shared_ptr<PKBStorageReadInterface> pkbRead =
      pkbStorageAPI->getReadStorage();

  SECTION("test follows storage related APIs") {
    REQUIRE_FALSE(pkbRead->getFollowsRelationshipExists(1, 2));

    // test single relationships
    pkbWrite->addFollowsRelationship(1, 2);
    REQUIRE(pkbRead->getFollowsRelationshipExists(1, 2));
    REQUIRE_FALSE(pkbRead->getFollowsRelationshipExists(1, 4));

    // test multiple relationships
    pkbWrite->addFollowsRelationship(4, 5);
    pkbWrite->addFollowsRelationship(5, 10);
    REQUIRE(pkbRead->getFollowsRelationshipExists(4, 5));
    REQUIRE(pkbRead->getFollowsRelationshipExists(5, 10));
    REQUIRE_FALSE(pkbRead->getFollowsRelationshipExists(5, 4));
    REQUIRE_FALSE(pkbRead->getFollowsRelationshipExists(10, 5));

    // test non-transitive follows
    REQUIRE_FALSE(pkbRead->getFollowsRelationshipExists(4, 10));
  }

  SECTION("test parents storage related APIs") {
    REQUIRE_FALSE(pkbRead->getParentRelationshipExists(1, 2));

    // test single relationships
    pkbWrite->addParentRelationship(1, 2);
    REQUIRE(pkbRead->getParentRelationshipExists(1, 2));
    REQUIRE_FALSE(pkbRead->getParentRelationshipExists(1, 4));

    // test multiple relationships
    pkbWrite->addParentRelationship(4, 5);
    pkbWrite->addParentRelationship(5, 10);
    REQUIRE(pkbRead->getParentRelationshipExists(4, 5));
    REQUIRE(pkbRead->getParentRelationshipExists(5, 10));
    REQUIRE_FALSE(pkbRead->getParentRelationshipExists(5, 4));
    REQUIRE_FALSE(pkbRead->getParentRelationshipExists(10, 5));
    REQUIRE_FALSE(pkbRead->getParentRelationshipExists(5, 15));

    // test non-transitive follows
    REQUIRE_FALSE(pkbRead->getParentRelationshipExists(4, 10));
  }

  SECTION("test modifies relationships") {
    REQUIRE_FALSE(pkbRead->getModifiesProcedureRelationshipExists("main", "y"));

    // test adding single relationships
    pkbWrite->addModifiesProcedureRelationship("main", "y");
    REQUIRE(pkbRead->getModifiesProcedureRelationshipExists("main", "y"));
    REQUIRE_FALSE(pkbRead->getModifiesProcedureRelationshipExists("y", "main"));

    // test adding multiple relationships
    pkbWrite->addModifiesProcedureRelationship("5", "x");
    pkbWrite->addModifiesProcedureRelationship("9", "x");
    REQUIRE(pkbRead->getModifiesProcedureRelationshipExists("5", "x"));
    REQUIRE(pkbRead->getModifiesProcedureRelationshipExists("9", "x"));
    REQUIRE_FALSE(pkbRead->getModifiesProcedureRelationshipExists("x", "5"));
    REQUIRE_FALSE(pkbRead->getModifiesProcedureRelationshipExists("x", "9"));
    REQUIRE_FALSE(pkbRead->getModifiesProcedureRelationshipExists("x", "15"));
  }

  SECTION("test uses Procedure relationships") {
    REQUIRE_FALSE(pkbRead->getUsesProcedureRelationshipExists("main", "y"));

    // test adding single relationships
    pkbWrite->addUsesProcedureRelationship("7", "x");
    REQUIRE(pkbRead->getUsesProcedureRelationshipExists("7", "x"));
    REQUIRE_FALSE(pkbRead->getUsesProcedureRelationshipExists("x", "7"));

    // test adding multiple relationships
    pkbWrite->addUsesProcedureRelationship("10", "count");
    pkbWrite->addUsesProcedureRelationship("10", "it");
    REQUIRE(pkbRead->getUsesProcedureRelationshipExists("10", "count"));
    REQUIRE(pkbRead->getUsesProcedureRelationshipExists("10", "it"));
    REQUIRE_FALSE(pkbRead->getUsesProcedureRelationshipExists("count", "10"));
    REQUIRE_FALSE(pkbRead->getUsesProcedureRelationshipExists("9", "it"));
    REQUIRE_FALSE(pkbRead->getUsesProcedureRelationshipExists("count", "15"));
  }

  SECTION("test uses Statement relationships") {
    REQUIRE_FALSE(pkbRead->getUsesStatementRelationshipExists(1, "y"));

    // test adding single relationships
    pkbWrite->addUsesStatementRelationship(1, "x");
    REQUIRE(pkbRead->getUsesStatementRelationshipExists(1, "x"));
    REQUIRE_FALSE(pkbRead->getUsesStatementRelationshipExists(10, "x"));

    // test adding multiple relationships
    pkbWrite->addUsesStatementRelationship(10, "count");
    pkbWrite->addUsesStatementRelationship(10, "it");
    REQUIRE(pkbRead->getUsesStatementRelationshipExists(10, "count"));
    REQUIRE(pkbRead->getUsesStatementRelationshipExists(10, "it"));
    REQUIRE_FALSE(pkbRead->getUsesStatementRelationshipExists(103, "10"));
    REQUIRE_FALSE(pkbRead->getUsesStatementRelationshipExists(9, "it"));
    REQUIRE_FALSE(pkbRead->getUsesStatementRelationshipExists(103, "15"));
  }
}

TEST_CASE("test entities") {
  std::shared_ptr<PKBStorageAPI> pkbStorageAPI =
      std::make_shared<PKBStorageAPI>();
  std::shared_ptr<PKBStorageWriteInterface> pkbWrite =
      pkbStorageAPI->getWriteStorage();
  std::shared_ptr<PKBStorageReadInterface> pkbRead =
      pkbStorageAPI->getReadStorage();
  // basic test some API;

  SECTION("test assign entities") {
    // testing single assign stmt entity
    std::unordered_set<int> assignEntities;
    assignEntities.insert(1);
    REQUIRE(pkbRead->getAssigns().empty());
    pkbWrite->addAssignEntity(1);
    REQUIRE(pkbRead->getAssigns() == assignEntities);

    // adding multiple entities
    pkbWrite->addAssignEntity(2);
    pkbWrite->addAssignEntity(3);
    REQUIRE_FALSE(pkbRead->getAssigns() == assignEntities);
    assignEntities.insert(2);
    REQUIRE_FALSE(pkbRead->getAssigns() == assignEntities);
    assignEntities.insert(3);
    REQUIRE(pkbRead->getAssigns() == assignEntities);
  }

  SECTION("test call entities") {
    // testing single call stmt entity
    std::unordered_set<int> callStatementEntities;
    callStatementEntities.insert(1);
    REQUIRE(pkbRead->getCalls().empty());
    pkbWrite->addCallEntity(1, "proc");
    REQUIRE(pkbRead->getCalls() == callStatementEntities);

    // adding multiple entities
    pkbWrite->addCallEntity(2, "proc_two");
    pkbWrite->addCallEntity(3, "proc");
    REQUIRE_FALSE(pkbRead->getCalls() == callStatementEntities);
    callStatementEntities.insert(2);
    REQUIRE_FALSE(pkbRead->getCalls() == callStatementEntities);
    callStatementEntities.insert(3);
    REQUIRE(pkbRead->getCalls() == callStatementEntities);
    REQUIRE(pkbRead->getCallProcName(1) == "proc");
    REQUIRE_FALSE(pkbRead->getCallProcName(2) == "proc");
    REQUIRE(pkbRead->getCallProcName(3) == "proc");
  }

  SECTION("test constant entities") {
    // testing single constant entity
    std::unordered_set<std::string> constantEntities;
    constantEntities.insert("x");
    REQUIRE(pkbRead->getConstants().empty());
    pkbWrite->addConstantEntity("x");
    REQUIRE(pkbRead->getConstants() == constantEntities);

    // adding multiple entities
    pkbWrite->addConstantEntity("y");
    pkbWrite->addConstantEntity("z");
    REQUIRE_FALSE(pkbRead->getConstants() == constantEntities);
    constantEntities.insert("y");
    REQUIRE_FALSE(pkbRead->getConstants() == constantEntities);
    constantEntities.insert("z");
    REQUIRE(pkbRead->getConstants() == constantEntities);
  }

  SECTION("test ifs entities") {
    // testing single ifs stmt entity
    std::unordered_set<int> ifsEntities;
    ifsEntities.insert(1);
    REQUIRE(pkbRead->getIfs().empty());
    pkbWrite->addIfEntity(1);
    REQUIRE(pkbRead->getIfs() == ifsEntities);

    // adding multiple entities
    pkbWrite->addIfEntity(2);
    pkbWrite->addIfEntity(3);
    REQUIRE_FALSE(pkbRead->getIfs() == ifsEntities);
    ifsEntities.insert(2);
    REQUIRE_FALSE(pkbRead->getIfs() == ifsEntities);
    ifsEntities.insert(3);
    REQUIRE(pkbRead->getIfs() == ifsEntities);
  }

  SECTION("test print entities") {
    // testing single print stmt entity
    std::unordered_set<int> printEntities;
    printEntities.insert(1);
    REQUIRE(pkbRead->getPrints().empty());
    pkbWrite->addPrintEntity(1, "var");
    REQUIRE(pkbRead->getPrints() == printEntities);

    // adding multiple entities
    pkbWrite->addPrintEntity(2, "var_two");
    pkbWrite->addPrintEntity(3, "var");
    REQUIRE_FALSE(pkbRead->getPrints() == printEntities);
    printEntities.insert(2);
    REQUIRE_FALSE(pkbRead->getPrints() == printEntities);
    printEntities.insert(3);
    REQUIRE(pkbRead->getPrints() == printEntities);
    REQUIRE(pkbRead->getPrintVarName(1) == "var");
    REQUIRE_FALSE(pkbRead->getPrintVarName(2) == "var");
    REQUIRE(pkbRead->getPrintVarName(3) == "var");
  }

  SECTION("test procedures entities") {
    // testing single procedure entity
    std::unordered_set<std::string> procedureEntities;
    procedureEntities.insert("x");
    REQUIRE(pkbRead->getProcedures().empty());
    pkbWrite->addProcedureEntity("x");
    REQUIRE(pkbRead->getProcedures() == procedureEntities);

    // adding multiple entities
    pkbWrite->addProcedureEntity("y");
    pkbWrite->addProcedureEntity("z");
    REQUIRE_FALSE(pkbRead->getProcedures() == procedureEntities);
    procedureEntities.insert("y");
    REQUIRE_FALSE(pkbRead->getProcedures() == procedureEntities);
    procedureEntities.insert("z");
    REQUIRE(pkbRead->getProcedures() == procedureEntities);
  }

  SECTION("test read entities") {
    // testing single read stmt entity
    std::unordered_set<int> readEntities;
    readEntities.insert(1);
    REQUIRE(pkbRead->getReads().empty());
    pkbWrite->addReadEntity(1, "var");
    REQUIRE(pkbRead->getReads() == readEntities);

    // adding multiple entities
    pkbWrite->addReadEntity(2, "var_two");
    pkbWrite->addReadEntity(3, "var");
    REQUIRE_FALSE(pkbRead->getReads() == readEntities);
    readEntities.insert(2);
    REQUIRE_FALSE(pkbRead->getPrints() == readEntities);
    readEntities.insert(3);
    REQUIRE(pkbRead->getReads() == readEntities);
    REQUIRE(pkbRead->getReadVarName(1) == "var");
    REQUIRE_FALSE(pkbRead->getReadVarName(2) == "var");
    REQUIRE(pkbRead->getReadVarName(3) == "var");
  }

  SECTION("test variable entities") {
    // testing single variable entity
    std::unordered_set<std::string> variableEntities;
    variableEntities.insert("x");
    REQUIRE(pkbRead->getVariables().empty());
    pkbWrite->addVariableEntity("x");
    REQUIRE(pkbRead->getVariables() == variableEntities);

    // adding multiple entities
    pkbWrite->addVariableEntity("y");
    pkbWrite->addVariableEntity("z");
    REQUIRE_FALSE(pkbRead->getVariables() == variableEntities);
    variableEntities.insert("y");
    REQUIRE_FALSE(pkbRead->getVariables() == variableEntities);
    variableEntities.insert("z");
    REQUIRE(pkbRead->getVariables() == variableEntities);
  }

  SECTION("test while entities") {
    // testing single while stmt entity
    std::unordered_set<int> whileEntities;
    whileEntities.insert(1);
    REQUIRE(pkbRead->getWhiles().empty());
    pkbWrite->addWhileEntity(1);
    REQUIRE(pkbRead->getWhiles() == whileEntities);

    // adding multiple entities
    pkbWrite->addWhileEntity(2);
    pkbWrite->addWhileEntity(3);
    REQUIRE_FALSE(pkbRead->getWhiles() == whileEntities);
    whileEntities.insert(2);
    REQUIRE_FALSE(pkbRead->getWhiles() == whileEntities);
    whileEntities.insert(3);
    REQUIRE(pkbRead->getWhiles() == whileEntities);
  }
}

using namespace PKB;
TEST_CASE("test pattern") {
  SECTION("test PatternStorage") {
    std::shared_ptr<PKBStorageAPI> pkbStorageAPI =
        std::make_shared<PKBStorageAPI>();
    std::shared_ptr<PKBStorageWriteInterface> pkbWrite =
        pkbStorageAPI->getWriteStorage();
    std::shared_ptr<PKBStorageReadInterface> pkbRead =
        pkbStorageAPI->getReadStorage();
    std::string lhs = "x";
    std::vector<std::string> rhs = {"a", "+", "b"};
    int stmtIndex = 1;

    // Test storeAssignPattern method
    REQUIRE(pkbRead->getAssignPatterns().empty());
    pkbWrite->addAssignPattern(stmtIndex, lhs, rhs);

    // Test getPatterns method
    const std::unordered_map<
        std::string, std::vector<std::pair<std::vector<std::string>, int>>>&
        allPatterns = pkbRead->getAssignPatterns();
    REQUIRE_FALSE(allPatterns.empty());

    // Test vectors and pairs
    auto it = allPatterns.find(lhs);
    REQUIRE(it != allPatterns.end());
    const std::vector<std::pair<std::vector<std::string>, int>>& patternVector =
        it->second;
    REQUIRE_FALSE(patternVector.empty());
    REQUIRE(patternVector.size() == 1);
    REQUIRE(patternVector[0].first == rhs);
    REQUIRE(patternVector[0].second == stmtIndex);
  }

  SECTION("test getAssignFirstArgPatterns") {
    std::shared_ptr<PKBStorageAPI> pkbStorageAPI =
        std::make_shared<PKBStorageAPI>();
    std::shared_ptr<PKBStorageWriteInterface> pkbWrite =
        pkbStorageAPI->getWriteStorage();
    std::shared_ptr<PKBStorageReadInterface> pkbRead =
        pkbStorageAPI->getReadStorage();

    std::vector<std::tuple<int, std::string, std::vector<std::string>>> data{
        {1, "v", {"a", "+", "b"}},
        {2, "v", {"b", "+", "c"}},
        {3, "z", {"x", "+", "y"}},
    };

    for (auto& [stmtNum, lhs, rhs] : data) {
      pkbWrite->addAssignPattern(stmtNum, lhs, rhs);
    }

    auto& res_v = pkbRead->getAssignFirstArgPatterns("v");
    REQUIRE(res_v.size() == 2);

    auto& res_z = pkbRead->getAssignFirstArgPatterns("z");
    REQUIRE(res_z.size() == 1);
    REQUIRE(res_z.front().second == 3);
  }
}
