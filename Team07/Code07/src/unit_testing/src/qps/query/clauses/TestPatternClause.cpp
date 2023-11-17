#include "catch.hpp"
#include "qps/query/clauses/Argument.h"
#include "qps/query/clauses/PatternClause.h"
#include "qps/query/declaration/AssignDeclaration.h"
#include "qps/query/declaration/CallDeclaration.h"
#include "qps/query/declaration/ConstantDeclaration.h"
#include "qps/query/declaration/IfDeclaration.h"
#include "qps/query/declaration/PrintDeclaration.h"
#include "qps/query/declaration/ProcedureDeclaration.h"
#include "qps/query/declaration/ReadDeclaration.h"
#include "qps/query/declaration/StatementDeclaration.h"
#include "qps/query/declaration/VariableDeclaration.h"
#include "qps/query/declaration/WhileDeclaration.h"

TEST_CASE("Pattern Assign Clause Validation") {
  SECTION("pattern(assign, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(assign, call)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(assign, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(assign, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(assign, if)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(assign, num)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(assign, print)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(assign, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(assign, read)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(assign, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(assign, str)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(assign, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(assign, while)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(assign, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(call, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(call, call)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(call, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(call, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(call, if)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(call, num)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(call, print)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(call, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(call, read)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(call, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(call, str)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(call, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(call, while)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(call, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(constant, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(constant, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(constant, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(constant, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(constant, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(constant, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(constant, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(constant, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(constant, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(constant, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(constant, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(constant, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(constant, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(constant, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(expr, assign)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(expr, call)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(expr, constant)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(expr, expr)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{{"name"}, true};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(expr, if)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(expr, num)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{1};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(expr, print)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(expr, procedure)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(expr, read)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(expr, stmt)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(expr, str)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{"name"};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(expr, variable)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(expr, while)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(expr, wildcard)") {
    QPS::Argument arg1{{"name"}, true};
    QPS::Argument arg2{};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(if, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(if, call)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(if, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(if, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(if, if)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(if, num)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(if, print)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(if, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(if, read)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(if, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(if, str)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(if, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(if, while)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(if, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(num, assign)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(num, call)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(num, constant)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(num, expr)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{{"name"}, true};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(num, if)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(num, num)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{1};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(num, print)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(num, procedure)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(num, read)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(num, stmt)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(num, str)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{"name"};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(num, variable)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(num, while)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(num, wildcard)") {
    QPS::Argument arg1{1};
    QPS::Argument arg2{};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(print, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(print, call)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(print, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(print, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(print, if)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(print, num)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(print, print)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(print, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(print, read)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(print, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(print, str)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(print, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(print, while)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(print, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(procedure, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(procedure, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(procedure, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(procedure, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(procedure, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(procedure, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(procedure, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(procedure, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(procedure, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(procedure, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(procedure, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(procedure, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(procedure, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(procedure, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(read, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(read, call)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(read, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(read, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(read, if)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(read, num)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(read, print)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(read, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(read, read)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(read, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(read, str)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(read, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(read, while)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(read, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(stmt, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(stmt, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(stmt, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(stmt, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(stmt, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(stmt, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(stmt, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(stmt, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(stmt, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(stmt, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(stmt, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(stmt, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(stmt, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(stmt, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(str, assign)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(str, call)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(str, constant)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(str, expr)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{{"name"}, true};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == true);
  }

  SECTION("pattern(str, if)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(str, num)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{1};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(str, print)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(str, procedure)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(str, read)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(str, stmt)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(str, str)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{"name"};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(str, variable)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(str, while)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(str, wildcard)") {
    QPS::Argument arg1{"name"};
    QPS::Argument arg2{};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == true);
  }

  SECTION("pattern(variable, assign)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(variable, call)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(variable, constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(variable, expr)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == true);
  }

  SECTION("pattern(variable, if)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(variable, num)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(variable, print)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(variable, procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(variable, read)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(variable, stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(variable, str)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(variable, variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(variable, while)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(variable, wildcard)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == true);
  }

  SECTION("pattern(while, assign)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(while, call)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(while, constant)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(while, expr)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{{"name"}, true};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(while, if)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(while, num)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{1};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(while, print)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(while, procedure)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(while, read)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(while, stmt)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(while, str)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{"name"};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(while, variable)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(while, while)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(while, wildcard)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(wildcard, assign)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(wildcard, call)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(wildcard, constant)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(wildcard, expr)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{{"name"}, true};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == true);
  }

  SECTION("pattern(wildcard, if)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(wildcard, num)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{1};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(wildcard, print)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(wildcard, procedure)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(wildcard, read)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(wildcard, stmt)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(wildcard, str)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{"name"};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(wildcard, variable)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(wildcard, while)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern(wildcard, wildcard)") {
    QPS::Argument arg1{};
    QPS::Argument arg2{};

    QPS::PatternClause<QPS::Assign> patternClause(
        std::make_shared<QPS::AssignDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == true);
  }
}

TEST_CASE("Pattern If Clause Validation") {
  SECTION("pattern if(variable, any)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::PatternClause<QPS::If> patternClause(
        std::make_shared<QPS::IfDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern if(assign)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::PatternClause<QPS::If> patternClause(
        std::make_shared<QPS::IfDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern if(call)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::PatternClause<QPS::If> patternClause(
        std::make_shared<QPS::IfDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern if(constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::PatternClause<QPS::If> patternClause(
        std::make_shared<QPS::IfDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern if(expr)") {
    QPS::Argument arg1{{"name"}, true};

    QPS::PatternClause<QPS::If> patternClause(
        std::make_shared<QPS::IfDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern if(if)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::PatternClause<QPS::If> patternClause(
        std::make_shared<QPS::IfDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern if(num)") {
    QPS::Argument arg1{1};

    QPS::PatternClause<QPS::If> patternClause(
        std::make_shared<QPS::IfDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern if(print)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::PatternClause<QPS::If> patternClause(
        std::make_shared<QPS::IfDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern if(procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::PatternClause<QPS::If> patternClause(
        std::make_shared<QPS::IfDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern if(read)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::PatternClause<QPS::If> patternClause(
        std::make_shared<QPS::IfDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern if(stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::PatternClause<QPS::If> patternClause(
        std::make_shared<QPS::IfDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern if(str)") {
    QPS::Argument arg1{"name"};

    QPS::PatternClause<QPS::If> patternClause(
        std::make_shared<QPS::IfDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == true);
  }

  SECTION("pattern if(variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::PatternClause<QPS::If> patternClause(
        std::make_shared<QPS::IfDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == true);
  }

  SECTION("pattern if(while)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::PatternClause<QPS::If> patternClause(
        std::make_shared<QPS::IfDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern if(wildcard)") {
    QPS::Argument arg1{};

    QPS::PatternClause<QPS::If> patternClause(
        std::make_shared<QPS::IfDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == true);
  }
}

TEST_CASE("Pattern While Clause Validation") {
  SECTION("pattern while(variable, any)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};
    QPS::Argument arg2{};

    QPS::PatternClause<QPS::While> patternClause(
        std::make_shared<QPS::WhileDeclaration>("declaration"), arg1, arg2);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern while(assign)") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>("declaration")};

    QPS::PatternClause<QPS::While> patternClause(
        std::make_shared<QPS::WhileDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern while(call)") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>("declaration")};

    QPS::PatternClause<QPS::While> patternClause(
        std::make_shared<QPS::WhileDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern while(constant)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ConstantDeclaration>("declaration")};

    QPS::PatternClause<QPS::While> patternClause(
        std::make_shared<QPS::WhileDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern while(expr)") {
    QPS::Argument arg1{{"name"}, true};

    QPS::PatternClause<QPS::While> patternClause(
        std::make_shared<QPS::WhileDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern while(if)") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>("declaration")};

    QPS::PatternClause<QPS::While> patternClause(
        std::make_shared<QPS::WhileDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern while(num)") {
    QPS::Argument arg1{1};

    QPS::PatternClause<QPS::While> patternClause(
        std::make_shared<QPS::WhileDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern while(print)") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>("declaration")};

    QPS::PatternClause<QPS::While> patternClause(
        std::make_shared<QPS::WhileDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern while(procedure)") {
    QPS::Argument arg1{
        std::make_shared<QPS::ProcedureDeclaration>("declaration")};

    QPS::PatternClause<QPS::While> patternClause(
        std::make_shared<QPS::WhileDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern while(read)") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>("declaration")};

    QPS::PatternClause<QPS::While> patternClause(
        std::make_shared<QPS::WhileDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern while(stmt)") {
    QPS::Argument arg1{
        std::make_shared<QPS::StatementDeclaration>("declaration")};

    QPS::PatternClause<QPS::While> patternClause(
        std::make_shared<QPS::WhileDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern while(str)") {
    QPS::Argument arg1{"name"};

    QPS::PatternClause<QPS::While> patternClause(
        std::make_shared<QPS::WhileDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == true);
  }

  SECTION("pattern while(variable)") {
    QPS::Argument arg1{
        std::make_shared<QPS::VariableDeclaration>("declaration")};

    QPS::PatternClause<QPS::While> patternClause(
        std::make_shared<QPS::WhileDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == true);
  }

  SECTION("pattern while(while)") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>("declaration")};

    QPS::PatternClause<QPS::While> patternClause(
        std::make_shared<QPS::WhileDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == false);
  }

  SECTION("pattern while(wildcard)") {
    QPS::Argument arg1{};

    QPS::PatternClause<QPS::While> patternClause(
        std::make_shared<QPS::WhileDeclaration>("declaration"), arg1);
    REQUIRE(patternClause.validate() == true);
  }
}