#include "catch.hpp"
#include "qps/evaluator/such_that_clause_evaluator/FollowsClauseEvaluator.h"
#include "qps/query/clauses/Argument.h"
#include "qps/query/clauses/SuchThatClause.h"
#include "qps/query/declaration/StatementDeclaration.h"

TEST_CASE("Such That Clause instantiation") {
  QPS::Argument arg1 = 1;
  std::shared_ptr<QPS::Declaration> decl =
      std::make_shared<QPS::StatementDeclaration>("s");
  QPS::Argument arg2 = decl;

  QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
  auto evaluator = suchThatClause.createEvaluator();
  REQUIRE(dynamic_cast<QPS::FollowsClauseEvaluator*>(evaluator.get()) !=
          nullptr);
}

TEST_CASE("Follows Relationship Validation") {
  SECTION("Follows(assign, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(assign, call)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(assign, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(assign, if)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(assign, num)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(assign, print)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(assign, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(assign, read)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(assign, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(assign, str)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(assign, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(assign, while)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(assign, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(call, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(call, call)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(call, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(call, if)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(call, num)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(call, print)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(call, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(call, read)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(call, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(call, str)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(call, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(call, while)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(call, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(constant, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(constant, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(constant, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(constant, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(constant, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(constant, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(constant, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(constant, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(constant, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(constant, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(constant, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(constant, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(constant, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(if, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(if, call)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(if, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(if, if)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(if, num)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(if, print)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(if, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(if, read)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(if, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(if, str)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(if, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(if, while)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(if, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(num, assign)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(num, call)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(num, constant)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(num, if)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(num, num)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(num, print)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(num, procedure)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(num, read)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(num, stmt)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(num, str)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(num, variable)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(num, while)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(num, wildcard)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(print, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(print, call)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(print, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(print, if)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(print, num)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(print, print)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(print, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(print, read)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(print, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(print, str)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(print, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(print, while)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(print, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(procedure, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(procedure, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(procedure, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(procedure, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(procedure, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(procedure, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(procedure, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(procedure, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(procedure, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(procedure, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(procedure, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(procedure, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(procedure, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(read, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(read, call)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(read, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(read, if)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(read, num)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(read, print)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(read, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(read, read)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(read, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(read, str)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(read, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(read, while)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(read, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(stmt, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(stmt, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(stmt, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(stmt, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(stmt, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(stmt, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(stmt, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(stmt, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(stmt, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(stmt, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(stmt, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(stmt, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(stmt, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(str, assign)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(str, call)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(str, constant)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(str, if)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(str, num)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(str, print)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(str, procedure)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(str, read)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(str, stmt)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(str, str)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(str, variable)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(str, while)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(str, wildcard)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(variable, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(variable, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(variable, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(variable, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(variable, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(variable, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(variable, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(variable, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(variable, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(variable, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(variable, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(variable, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(variable, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(while, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(while, call)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(while, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(while, if)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(while, num)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(while, print)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(while, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(while, read)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(while, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(while, str)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(while, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(while, while)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(while, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(wildcard, assign)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(wildcard, call)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(wildcard, constant)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(wildcard, if)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(wildcard, num)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(wildcard, print)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(wildcard, procedure)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(wildcard, read)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(wildcard, stmt)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(wildcard, str)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(wildcard, variable)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows(wildcard, while)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows(wildcard, wildcard)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }
}

TEST_CASE("Follows* Relationship Validation") {
  SECTION("Follows*(assign, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(assign, call)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(assign, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(assign, if)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(assign, num)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(assign, print)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(assign, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(assign, read)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(assign, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(assign, str)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(assign, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(assign, while)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(assign, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(call, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(call, call)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(call, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(call, if)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(call, num)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(call, print)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(call, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(call, read)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(call, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(call, str)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(call, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(call, while)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(call, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(constant, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(constant, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(constant, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(constant, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(constant, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(constant, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(constant, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(constant, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(constant, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(constant, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(constant, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(constant, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(constant, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(if, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(if, call)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(if, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(if, if)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(if, num)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(if, print)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(if, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(if, read)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(if, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(if, str)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(if, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(if, while)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(if, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(num, assign)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(num, call)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(num, constant)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(num, if)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(num, num)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(num, print)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(num, procedure)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(num, read)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(num, stmt)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(num, str)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(num, variable)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(num, while)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(num, wildcard)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(print, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(print, call)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(print, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(print, if)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(print, num)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(print, print)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(print, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(print, read)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(print, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(print, str)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(print, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(print, while)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(print, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(procedure, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(procedure, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(procedure, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(procedure, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(procedure, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(procedure, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(procedure, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(procedure, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(procedure, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(procedure, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(procedure, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(procedure, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(procedure, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(read, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(read, call)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(read, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(read, if)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(read, num)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(read, print)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(read, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(read, read)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(read, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(read, str)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(read, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(read, while)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(read, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(stmt, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(stmt, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(stmt, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(stmt, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(stmt, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(stmt, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(stmt, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(stmt, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(stmt, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(stmt, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(stmt, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(stmt, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(stmt, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(str, assign)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(str, call)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(str, constant)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(str, if)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(str, num)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(str, print)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(str, procedure)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(str, read)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(str, stmt)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(str, str)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(str, variable)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(str, while)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(str, wildcard)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(variable, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(variable, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(variable, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(variable, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(variable, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(variable, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(variable, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(variable, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(variable, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(variable, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(variable, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(variable, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(variable, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(while, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(while, call)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(while, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(while, if)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(while, num)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(while, print)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(while, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(while, read)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(while, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(while, str)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(while, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(while, while)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(while, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(wildcard, assign)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(wildcard, call)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(wildcard, constant)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(wildcard, if)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(wildcard, num)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(wildcard, print)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(wildcard, procedure)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(wildcard, read)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(wildcard, stmt)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(wildcard, str)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(wildcard, variable)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Follows*(wildcard, while)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Follows*(wildcard, wildcard)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::FollowsStarRelationship> suchThatClause(arg1,
                                                                     arg2);
    REQUIRE(suchThatClause.validate() == true);
  }
}

TEST_CASE("Parent Relationship Validation") {
  SECTION("Parent(assign, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(assign, call)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(assign, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(assign, if)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(assign, num)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(assign, print)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(assign, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(assign, read)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(assign, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(assign, str)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(assign, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(assign, while)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(assign, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(call, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(call, call)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(call, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(call, if)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(call, num)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(call, print)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(call, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(call, read)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(call, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(call, str)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(call, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(call, while)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(call, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(constant, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(constant, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(constant, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(constant, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(constant, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(constant, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(constant, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(constant, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(constant, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(constant, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(constant, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(constant, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(constant, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(if, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(if, call)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(if, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(if, if)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(if, num)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(if, print)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(if, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(if, read)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(if, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(if, str)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(if, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(if, while)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(if, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(num, assign)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(num, call)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(num, constant)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(num, if)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(num, num)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(num, print)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(num, procedure)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(num, read)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(num, stmt)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(num, str)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(num, variable)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(num, while)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(num, wildcard)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(print, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(print, call)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(print, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(print, if)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(print, num)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(print, print)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(print, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(print, read)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(print, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(print, str)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(print, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(print, while)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(print, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(procedure, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(procedure, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(procedure, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(procedure, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(procedure, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(procedure, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(procedure, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(procedure, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(procedure, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(procedure, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(procedure, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(procedure, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(procedure, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(read, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(read, call)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(read, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(read, if)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(read, num)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(read, print)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(read, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(read, read)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(read, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(read, str)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(read, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(read, while)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(read, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(stmt, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(stmt, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(stmt, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(stmt, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(stmt, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(stmt, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(stmt, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(stmt, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(stmt, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(stmt, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(stmt, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(stmt, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(stmt, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(str, assign)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(str, call)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(str, constant)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(str, if)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(str, num)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(str, print)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(str, procedure)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(str, read)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(str, stmt)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(str, str)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(str, variable)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(str, while)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(str, wildcard)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(variable, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(variable, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(variable, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(variable, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(variable, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(variable, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(variable, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(variable, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(variable, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(variable, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(variable, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(variable, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(variable, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(while, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(while, call)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(while, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(while, if)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(while, num)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(while, print)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(while, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(while, read)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(while, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(while, str)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(while, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(while, while)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(while, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(wildcard, assign)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(wildcard, call)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(wildcard, constant)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(wildcard, if)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(wildcard, num)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(wildcard, print)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(wildcard, procedure)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(wildcard, read)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(wildcard, stmt)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(wildcard, str)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(wildcard, variable)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent(wildcard, while)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent(wildcard, wildcard)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }
}

TEST_CASE("Parent* Relationship Validation") {
  SECTION("Parent*(assign, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(assign, call)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(assign, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(assign, if)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(assign, num)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(assign, print)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(assign, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(assign, read)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(assign, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(assign, str)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(assign, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(assign, while)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(assign, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(call, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(call, call)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(call, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(call, if)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(call, num)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(call, print)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(call, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(call, read)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(call, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(call, str)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(call, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(call, while)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(call, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(constant, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(constant, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(constant, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(constant, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(constant, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(constant, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(constant, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(constant, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(constant, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(constant, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(constant, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(constant, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(constant, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(if, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(if, call)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(if, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(if, if)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(if, num)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(if, print)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(if, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(if, read)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(if, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(if, str)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(if, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(if, while)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(if, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(num, assign)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(num, call)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(num, constant)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(num, if)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(num, num)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(num, print)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(num, procedure)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(num, read)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(num, stmt)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(num, str)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(num, variable)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(num, while)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(num, wildcard)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(print, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(print, call)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(print, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(print, if)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(print, num)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(print, print)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(print, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(print, read)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(print, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(print, str)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(print, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(print, while)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(print, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(procedure, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(procedure, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(procedure, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(procedure, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(procedure, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(procedure, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(procedure, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(procedure, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(procedure, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(procedure, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(procedure, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(procedure, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(procedure, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(read, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(read, call)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(read, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(read, if)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(read, num)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(read, print)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(read, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(read, read)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(read, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(read, str)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(read, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(read, while)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(read, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(stmt, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(stmt, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(stmt, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(stmt, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(stmt, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(stmt, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(stmt, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(stmt, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(stmt, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(stmt, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(stmt, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(stmt, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(stmt, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(str, assign)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(str, call)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(str, constant)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(str, if)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(str, num)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(str, print)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(str, procedure)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(str, read)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(str, stmt)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(str, str)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(str, variable)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(str, while)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(str, wildcard)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(variable, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(variable, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(variable, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(variable, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(variable, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(variable, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(variable, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(variable, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(variable, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(variable, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(variable, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(variable, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(variable, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(while, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(while, call)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(while, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(while, if)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(while, num)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(while, print)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(while, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(while, read)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(while, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(while, str)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(while, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(while, while)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(while, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(wildcard, assign)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(wildcard, call)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(wildcard, constant)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(wildcard, if)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(wildcard, num)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(wildcard, print)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(wildcard, procedure)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(wildcard, read)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(wildcard, stmt)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(wildcard, str)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(wildcard, variable)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Parent*(wildcard, while)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Parent*(wildcard, wildcard)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ParentStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }
}

TEST_CASE("Modifies Relationship Validation") {
  SECTION("Modifies(assign, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(assign, call)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(assign, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(assign, if)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(assign, num)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(assign, print)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(assign, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(assign, read)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(assign, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(assign, str)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(assign, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(assign, while)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(assign, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(call, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(call, call)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(call, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(call, if)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(call, num)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(call, print)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(call, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(call, read)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(call, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(call, str)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(call, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(call, while)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(call, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(constant, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(constant, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(constant, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(constant, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(constant, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(constant, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(constant, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(constant, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(constant, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(constant, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(constant, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(constant, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(constant, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(if, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(if, call)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(if, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(if, if)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(if, num)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(if, print)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(if, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(if, read)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(if, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(if, str)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(if, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(if, while)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(if, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(num, assign)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(num, call)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(num, constant)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(num, if)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(num, num)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(num, print)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(num, procedure)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(num, read)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(num, stmt)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(num, str)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(num, variable)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(num, while)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(num, wildcard)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(print, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(print, call)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(print, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(print, if)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(print, num)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(print, print)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(print, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(print, read)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(print, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(print, str)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(print, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(print, while)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(print, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(procedure, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(procedure, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(procedure, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(procedure, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(procedure, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(procedure, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(procedure, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(procedure, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(procedure, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(procedure, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(procedure, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(procedure, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(procedure, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(read, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(read, call)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(read, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(read, if)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(read, num)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(read, print)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(read, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(read, read)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(read, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(read, str)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(read, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(read, while)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(read, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(stmt, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(stmt, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(stmt, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(stmt, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(stmt, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(stmt, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(stmt, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(stmt, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(stmt, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(stmt, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(stmt, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(stmt, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(stmt, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(str, assign)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(str, call)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(str, constant)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(str, if)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(str, num)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(str, print)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(str, procedure)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(str, read)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(str, stmt)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(str, str)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(str, variable)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(str, while)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(str, wildcard)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(variable, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(variable, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(variable, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(variable, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(variable, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(variable, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(variable, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(variable, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(variable, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(variable, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(variable, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(variable, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(variable, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(while, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(while, call)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(while, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(while, if)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(while, num)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(while, print)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(while, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(while, read)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(while, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(while, str)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(while, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(while, while)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(while, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Modifies(wildcard, assign)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(wildcard, call)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(wildcard, constant)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(wildcard, if)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(wildcard, num)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(wildcard, print)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(wildcard, procedure)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(wildcard, read)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(wildcard, stmt)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(wildcard, str)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(wildcard, variable)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(wildcard, while)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Modifies(wildcard, wildcard)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::ModifiesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }
}

TEST_CASE("Uses Relationship Validation") {
  SECTION("Uses(assign, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(assign, call)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(assign, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(assign, if)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(assign, num)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(assign, print)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(assign, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(assign, read)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(assign, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(assign, str)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(assign, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(assign, while)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(assign, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(call, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(call, call)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(call, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(call, if)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(call, num)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(call, print)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(call, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(call, read)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(call, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(call, str)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(call, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(call, while)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(call, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(constant, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(constant, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(constant, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(constant, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(constant, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(constant, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(constant, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(constant, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(constant, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(constant, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(constant, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(constant, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(constant, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(if, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(if, call)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(if, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(if, if)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(if, num)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(if, print)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(if, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(if, read)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(if, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(if, str)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(if, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(if, while)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(if, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(num, assign)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(num, call)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(num, constant)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(num, if)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(num, num)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(num, print)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(num, procedure)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(num, read)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(num, stmt)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(num, str)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(num, variable)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(num, while)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(num, wildcard)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(print, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(print, call)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(print, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(print, if)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(print, num)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(print, print)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(print, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(print, read)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(print, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(print, str)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(print, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(print, while)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(print, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(procedure, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(procedure, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(procedure, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(procedure, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(procedure, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(procedure, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(procedure, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(procedure, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(procedure, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(procedure, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(procedure, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(procedure, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(procedure, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(read, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(read, call)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(read, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(read, if)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(read, num)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(read, print)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(read, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(read, read)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(read, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(read, str)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(read, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(read, while)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(read, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(stmt, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(stmt, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(stmt, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(stmt, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(stmt, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(stmt, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(stmt, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(stmt, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(stmt, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(stmt, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(stmt, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(stmt, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(stmt, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(str, assign)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(str, call)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(str, constant)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(str, if)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(str, num)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(str, print)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(str, procedure)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(str, read)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(str, stmt)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(str, str)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(str, variable)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(str, while)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(str, wildcard)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(variable, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(variable, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(variable, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(variable, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(variable, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(variable, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(variable, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(variable, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(variable, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(variable, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(variable, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(variable, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(variable, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(while, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(while, call)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(while, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(while, if)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(while, num)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(while, print)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(while, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(while, read)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(while, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(while, str)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(while, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(while, while)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(while, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Uses(wildcard, assign)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(wildcard, call)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(wildcard, constant)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(wildcard, if)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(wildcard, num)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(wildcard, print)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(wildcard, procedure)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(wildcard, read)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(wildcard, stmt)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(wildcard, str)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(wildcard, variable)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(wildcard, while)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Uses(wildcard, wildcard)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::UsesRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }
}

TEST_CASE("Calls Relationship Validation") {

  SECTION("Calls(assign, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(assign, call)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(assign, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(assign, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(assign, if)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(assign, num)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(assign, print)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(assign, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(assign, read)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(assign, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(assign, str)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(assign, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(assign, while)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(assign, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(call, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(call, call)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(call, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(call, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(call, if)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(call, num)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(call, print)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(call, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(call, read)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(call, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(call, str)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(call, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(call, while)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(call, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(constant, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(constant, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(constant, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(constant, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(constant, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(constant, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(constant, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(constant, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(constant, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(constant, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(constant, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(constant, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(constant, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(constant, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(expr, assign)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(expr, call)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(expr, constant)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(expr, expr)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(expr, if)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(expr, num)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(expr, print)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(expr, procedure)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(expr, read)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(expr, stmt)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(expr, str)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(expr, variable)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(expr, while)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(expr, wildcard)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(if, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(if, call)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(if, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(if, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(if, if)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(if, num)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(if, print)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(if, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(if, read)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(if, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(if, str)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(if, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(if, while)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(if, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(num, assign)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(num, call)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(num, constant)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(num, expr)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(num, if)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(num, num)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(num, print)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(num, procedure)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(num, read)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(num, stmt)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(num, str)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(num, variable)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(num, while)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(num, wildcard)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(print, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(print, call)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(print, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(print, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(print, if)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(print, num)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(print, print)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(print, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(print, read)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(print, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(print, str)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(print, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(print, while)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(print, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(procedure, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(procedure, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(procedure, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(procedure, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(procedure, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(procedure, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(procedure, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(procedure, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Calls(procedure, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(procedure, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(procedure, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Calls(procedure, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(procedure, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(procedure, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Calls(read, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(read, call)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(read, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(read, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(read, if)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(read, num)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(read, print)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(read, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(read, read)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(read, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(read, str)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(read, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(read, while)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(read, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(stmt, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(stmt, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(stmt, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(stmt, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(stmt, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(stmt, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(stmt, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(stmt, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(stmt, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(stmt, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(stmt, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(stmt, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(stmt, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(stmt, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(str, assign)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(str, call)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(str, constant)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(str, expr)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(str, if)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(str, num)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(str, print)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(str, procedure)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Calls(str, read)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(str, stmt)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(str, str)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Calls(str, variable)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(str, while)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(str, wildcard)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Calls(variable, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(variable, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(variable, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(variable, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(variable, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(variable, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(variable, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(variable, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(variable, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(variable, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(variable, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(variable, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(variable, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(variable, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(while, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(while, call)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(while, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(while, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(while, if)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(while, num)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(while, print)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(while, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(while, read)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(while, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(while, str)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(while, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(while, while)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(while, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(wildcard, assign)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(wildcard, call)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(wildcard, constant)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(wildcard, expr)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(wildcard, if)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(wildcard, num)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(wildcard, print)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(wildcard, procedure)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Calls(wildcard, read)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(wildcard, stmt)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(wildcard, str)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Calls(wildcard, variable)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(wildcard, while)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls(wildcard, wildcard)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }
}

TEST_CASE("Calls* Relationship Validation") {
  SECTION("Calls*(assign, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(assign, call)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(assign, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(assign, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(assign, if)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(assign, num)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(assign, print)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(assign, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(assign, read)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(assign, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(assign, str)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(assign, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(assign, while)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(assign, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(call, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(call, call)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(call, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(call, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(call, if)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(call, num)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(call, print)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(call, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(call, read)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(call, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(call, str)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(call, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(call, while)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(call, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(constant, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(constant, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(constant, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(constant, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(constant, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(constant, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(constant, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(constant, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(constant, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(constant, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(constant, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(constant, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(constant, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(constant, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(expr, assign)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(expr, call)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(expr, constant)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(expr, expr)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(expr, if)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(expr, num)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(expr, print)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(expr, procedure)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(expr, read)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(expr, stmt)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(expr, str)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(expr, variable)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(expr, while)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(expr, wildcard)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(if, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(if, call)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(if, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(if, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(if, if)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(if, num)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(if, print)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(if, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(if, read)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(if, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(if, str)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(if, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(if, while)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(if, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(num, assign)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(num, call)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(num, constant)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(num, expr)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(num, if)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(num, num)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(num, print)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(num, procedure)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(num, read)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(num, stmt)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(num, str)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(num, variable)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(num, while)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(num, wildcard)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(print, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(print, call)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(print, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(print, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(print, if)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(print, num)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(print, print)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(print, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(print, read)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(print, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(print, str)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(print, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(print, while)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(print, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(procedure, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(procedure, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(procedure, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(procedure, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(procedure, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(procedure, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(procedure, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(procedure, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Calls*(procedure, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(procedure, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(procedure, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Calls*(procedure, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(procedure, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(procedure, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Calls*(read, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(read, call)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(read, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(read, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(read, if)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(read, num)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(read, print)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(read, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(read, read)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(read, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(read, str)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(read, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(read, while)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(read, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(stmt, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(stmt, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(stmt, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(stmt, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(stmt, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(stmt, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(stmt, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(stmt, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(stmt, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(stmt, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(stmt, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(stmt, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(stmt, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(stmt, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(str, assign)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(str, call)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(str, constant)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(str, expr)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(str, if)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(str, num)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(str, print)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(str, procedure)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Calls*(str, read)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(str, stmt)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(str, str)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Calls*(str, variable)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(str, while)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(str, wildcard)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Calls*(variable, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(variable, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(variable, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(variable, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(variable, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(variable, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(variable, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(variable, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(variable, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(variable, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(variable, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(variable, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(variable, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(variable, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(while, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(while, call)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(while, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(while, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(while, if)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(while, num)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(while, print)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(while, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(while, read)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(while, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(while, str)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(while, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(while, while)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(while, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(wildcard, assign)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(wildcard, call)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(wildcard, constant)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(wildcard, expr)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(wildcard, if)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(wildcard, num)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(wildcard, print)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(wildcard, procedure)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Calls*(wildcard, read)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(wildcard, stmt)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(wildcard, str)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Calls*(wildcard, variable)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(wildcard, while)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Calls*(wildcard, wildcard)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::CallsStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }
}

TEST_CASE("Next Relationship Validation") {

  SECTION("Next(assign, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(assign, call)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(assign, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(assign, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(assign, if)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(assign, num)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(assign, print)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(assign, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(assign, read)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(assign, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(assign, str)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(assign, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(assign, while)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(assign, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(call, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(call, call)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(call, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(call, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(call, if)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(call, num)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(call, print)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(call, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(call, read)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(call, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(call, str)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(call, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(call, while)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(call, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(constant, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(constant, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(constant, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(constant, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(constant, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(constant, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(constant, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(constant, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(constant, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(constant, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(constant, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(constant, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(constant, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(constant, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(expr, assign)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(expr, call)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(expr, constant)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(expr, expr)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(expr, if)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(expr, num)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(expr, print)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(expr, procedure)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(expr, read)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(expr, stmt)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(expr, str)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(expr, variable)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(expr, while)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(expr, wildcard)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(if, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(if, call)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(if, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(if, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(if, if)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(if, num)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(if, print)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(if, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(if, read)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(if, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(if, str)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(if, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(if, while)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(if, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(num, assign)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(num, call)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(num, constant)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(num, expr)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(num, if)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(num, num)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(num, print)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(num, procedure)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(num, read)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(num, stmt)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(num, str)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(num, variable)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(num, while)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(num, wildcard)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(print, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(print, call)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(print, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(print, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(print, if)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(print, num)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(print, print)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(print, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(print, read)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(print, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(print, str)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(print, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(print, while)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(print, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(procedure, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(procedure, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(procedure, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(procedure, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(procedure, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(procedure, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(procedure, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(procedure, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(procedure, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(procedure, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(procedure, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(procedure, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(procedure, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(procedure, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(read, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(read, call)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(read, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(read, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(read, if)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(read, num)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(read, print)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(read, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(read, read)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(read, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(read, str)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(read, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(read, while)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(read, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(stmt, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(stmt, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(stmt, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(stmt, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(stmt, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(stmt, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(stmt, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(stmt, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(stmt, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(stmt, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(stmt, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(stmt, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(stmt, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(stmt, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(str, assign)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(str, call)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(str, constant)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(str, expr)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(str, if)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(str, num)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(str, print)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(str, procedure)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(str, read)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(str, stmt)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(str, str)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(str, variable)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(str, while)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(str, wildcard)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(variable, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(variable, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(variable, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(variable, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(variable, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(variable, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(variable, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(variable, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(variable, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(variable, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(variable, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(variable, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(variable, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(variable, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(while, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(while, call)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(while, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(while, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(while, if)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(while, num)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(while, print)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(while, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(while, read)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(while, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(while, str)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(while, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(while, while)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(while, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(wildcard, assign)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(wildcard, call)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(wildcard, constant)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(wildcard, expr)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(wildcard, if)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(wildcard, num)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(wildcard, print)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(wildcard, procedure)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(wildcard, read)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(wildcard, stmt)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(wildcard, str)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(wildcard, variable)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next(wildcard, while)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next(wildcard, wildcard)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }
}

TEST_CASE("Next* Relationship Validation") {

  SECTION("Next*(assign, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(assign, call)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(assign, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(assign, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(assign, if)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(assign, num)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(assign, print)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(assign, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(assign, read)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(assign, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(assign, str)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(assign, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(assign, while)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(assign, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(call, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(call, call)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(call, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(call, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(call, if)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(call, num)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(call, print)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(call, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(call, read)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(call, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(call, str)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(call, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(call, while)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(call, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(constant, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(constant, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(constant, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(constant, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(constant, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(constant, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(constant, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(constant, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(constant, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(constant, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(constant, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(constant, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(constant, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(constant, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(expr, assign)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(expr, call)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(expr, constant)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(expr, expr)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(expr, if)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(expr, num)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(expr, print)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(expr, procedure)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(expr, read)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(expr, stmt)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(expr, str)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(expr, variable)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(expr, while)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(expr, wildcard)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(if, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(if, call)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(if, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(if, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(if, if)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(if, num)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(if, print)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(if, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(if, read)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(if, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(if, str)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(if, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(if, while)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(if, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(num, assign)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(num, call)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(num, constant)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(num, expr)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(num, if)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(num, num)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(num, print)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(num, procedure)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(num, read)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(num, stmt)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(num, str)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(num, variable)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(num, while)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(num, wildcard)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(print, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(print, call)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(print, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(print, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(print, if)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(print, num)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(print, print)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(print, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(print, read)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(print, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(print, str)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(print, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(print, while)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(print, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(procedure, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(procedure, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(procedure, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(procedure, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(procedure, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(procedure, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(procedure, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(procedure, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(procedure, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(procedure, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(procedure, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(procedure, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(procedure, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(procedure, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(read, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(read, call)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(read, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(read, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(read, if)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(read, num)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(read, print)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(read, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(read, read)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(read, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(read, str)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(read, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(read, while)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(read, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(stmt, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(stmt, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(stmt, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(stmt, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(stmt, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(stmt, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(stmt, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(stmt, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(stmt, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(stmt, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(stmt, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(stmt, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(stmt, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(stmt, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(str, assign)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(str, call)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(str, constant)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(str, expr)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(str, if)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(str, num)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(str, print)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(str, procedure)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(str, read)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(str, stmt)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(str, str)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(str, variable)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(str, while)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(str, wildcard)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(variable, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(variable, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(variable, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(variable, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(variable, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(variable, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(variable, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(variable, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(variable, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(variable, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(variable, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(variable, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(variable, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(variable, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(while, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(while, call)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(while, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(while, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(while, if)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(while, num)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(while, print)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(while, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(while, read)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(while, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(while, str)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(while, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(while, while)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(while, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(wildcard, assign)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(wildcard, call)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(wildcard, constant)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(wildcard, expr)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(wildcard, if)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(wildcard, num)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(wildcard, print)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(wildcard, procedure)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(wildcard, read)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(wildcard, stmt)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(wildcard, str)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(wildcard, variable)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Next*(wildcard, while)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Next*(wildcard, wildcard)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::NextStarRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }
}

TEST_CASE("Affects Relationship Validation") {

  SECTION("Affects(assign, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(assign, call)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(assign, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(assign, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(assign, if)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(assign, num)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(assign, print)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(assign, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(assign, read)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(assign, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(assign, str)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(assign, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(assign, while)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(assign, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(call, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(call, call)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(call, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(call, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(call, if)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(call, num)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(call, print)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(call, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(call, read)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(call, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(call, str)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(call, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(call, while)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(call, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(constant, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(constant, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(constant, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(constant, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(constant, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(constant, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(constant, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(constant, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(constant, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(constant, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(constant, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(constant, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(constant, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(constant, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(expr, assign)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(expr, call)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(expr, constant)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(expr, expr)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(expr, if)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(expr, num)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(expr, print)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(expr, procedure)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(expr, read)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(expr, stmt)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(expr, str)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(expr, variable)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(expr, while)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(expr, wildcard)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(if, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(if, call)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(if, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(if, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(if, if)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(if, num)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(if, print)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(if, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(if, read)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(if, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(if, str)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(if, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(if, while)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(if, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(num, assign)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(num, call)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(num, constant)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(num, expr)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(num, if)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(num, num)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(num, print)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(num, procedure)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(num, read)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(num, stmt)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(num, str)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(num, variable)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(num, while)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(num, wildcard)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(print, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(print, call)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(print, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(print, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(print, if)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(print, num)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(print, print)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(print, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(print, read)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(print, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(print, str)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(print, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(print, while)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(print, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(procedure, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(procedure, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(procedure, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(procedure, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(procedure, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(procedure, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(procedure, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(procedure, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(procedure, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(procedure, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(procedure, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(procedure, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(procedure, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(procedure, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(read, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(read, call)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(read, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(read, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(read, if)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(read, num)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(read, print)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(read, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(read, read)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(read, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(read, str)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(read, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(read, while)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(read, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(stmt, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(stmt, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(stmt, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(stmt, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(stmt, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(stmt, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(stmt, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(stmt, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(stmt, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(stmt, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(stmt, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(stmt, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(stmt, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(stmt, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(str, assign)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(str, call)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(str, constant)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(str, expr)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(str, if)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(str, num)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(str, print)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(str, procedure)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(str, read)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(str, stmt)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(str, str)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(str, variable)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(str, while)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(str, wildcard)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(variable, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(variable, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(variable, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(variable, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(variable, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(variable, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(variable, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(variable, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(variable, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(variable, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(variable, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(variable, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(variable, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(variable, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(while, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(while, call)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(while, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(while, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(while, if)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(while, num)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(while, print)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(while, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(while, read)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(while, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(while, str)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(while, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(while, while)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(while, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(wildcard, assign)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(wildcard, call)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(wildcard, constant)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(wildcard, expr)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{{"name"}, true};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(wildcard, if)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(wildcard, num)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{1};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(wildcard, print)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(wildcard, procedure)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(wildcard, read)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(wildcard, stmt)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(wildcard, str)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{"name"};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(wildcard, variable)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == false);
  }

  SECTION("Affects(wildcard, while)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }

  SECTION("Affects(wildcard, wildcard)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{};

    QPS::SuchThatClause<QPS::AffectsRelationship> suchThatClause(arg1, arg2);
    REQUIRE(suchThatClause.validate() == true);
  }
}