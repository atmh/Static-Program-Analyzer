#include "catch.hpp"
#include "qps/query/clauses/Argument.h"
#include "qps/query/clauses/PatternClause.h"
#include "qps/query/clauses/WithClause.h"
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

TEST_CASE("With Clause Relationship Validation") {

  SECTION("with assign.NAME = assign.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.NAME = assign.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.INTEGER = assign.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.INTEGER = assign.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with assign.NAME = call.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.NAME = call.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.INTEGER = call.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.INTEGER = call.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with assign.NAME = constant.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.NAME = constant.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.INTEGER = constant.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.INTEGER = constant.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with assign.NAME = if.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.NAME = if.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.INTEGER = if.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.INTEGER = if.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with assign.NAME = print.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.NAME = print.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.INTEGER = print.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.INTEGER = print.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with assign.NAME = procedure.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.NAME = procedure.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.INTEGER = procedure.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.INTEGER = procedure.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.NAME = read.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.NAME = read.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.INTEGER = read.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.INTEGER = read.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with assign.NAME = stmt.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.NAME = stmt.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.INTEGER = stmt.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.INTEGER = stmt.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with assign.NAME = variable.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.NAME = variable.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.INTEGER = variable.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.INTEGER = variable.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.NAME = while.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.NAME = while.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.INTEGER = while.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with assign.INTEGER = while.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with call.NAME = assign.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.NAME = assign.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.INTEGER = assign.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.INTEGER = assign.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with call.NAME = call.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with call.NAME = call.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.INTEGER = call.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.INTEGER = call.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with call.NAME = constant.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.NAME = constant.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.INTEGER = constant.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.INTEGER = constant.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with call.NAME = if.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.NAME = if.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.INTEGER = if.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.INTEGER = if.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with call.NAME = print.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with call.NAME = print.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.INTEGER = print.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.INTEGER = print.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with call.NAME = procedure.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with call.NAME = procedure.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.INTEGER = procedure.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.INTEGER = procedure.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.NAME = read.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with call.NAME = read.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.INTEGER = read.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.INTEGER = read.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with call.NAME = stmt.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.NAME = stmt.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.INTEGER = stmt.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.INTEGER = stmt.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with call.NAME = variable.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with call.NAME = variable.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.INTEGER = variable.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.INTEGER = variable.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.NAME = while.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.NAME = while.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.INTEGER = while.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with call.INTEGER = while.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with constant.NAME = assign.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.NAME = assign.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.INTEGER = assign.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.INTEGER = assign.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with constant.NAME = call.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.NAME = call.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.INTEGER = call.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.INTEGER = call.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with constant.NAME = constant.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.NAME = constant.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.INTEGER = constant.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.INTEGER = constant.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with constant.NAME = if.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.NAME = if.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.INTEGER = if.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.INTEGER = if.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with constant.NAME = print.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.NAME = print.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.INTEGER = print.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.INTEGER = print.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with constant.NAME = procedure.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.NAME = procedure.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.INTEGER = procedure.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.INTEGER = procedure.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.NAME = read.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.NAME = read.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.INTEGER = read.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.INTEGER = read.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with constant.NAME = stmt.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.NAME = stmt.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.INTEGER = stmt.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.INTEGER = stmt.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with constant.NAME = variable.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.NAME = variable.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.INTEGER = variable.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.INTEGER = variable.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.NAME = while.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.NAME = while.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.INTEGER = while.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with constant.INTEGER = while.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with if.NAME = assign.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.NAME = assign.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.INTEGER = assign.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.INTEGER = assign.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with if.NAME = call.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.NAME = call.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.INTEGER = call.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.INTEGER = call.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with if.NAME = constant.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.NAME = constant.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.INTEGER = constant.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.INTEGER = constant.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with if.NAME = if.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.NAME = if.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.INTEGER = if.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.INTEGER = if.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with if.NAME = print.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.NAME = print.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.INTEGER = print.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.INTEGER = print.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with if.NAME = procedure.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.NAME = procedure.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.INTEGER = procedure.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.INTEGER = procedure.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.NAME = read.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.NAME = read.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.INTEGER = read.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.INTEGER = read.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with if.NAME = stmt.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.NAME = stmt.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.INTEGER = stmt.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.INTEGER = stmt.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with if.NAME = variable.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.NAME = variable.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.INTEGER = variable.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.INTEGER = variable.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.NAME = while.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.NAME = while.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.INTEGER = while.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with if.INTEGER = while.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with print.NAME = assign.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.NAME = assign.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.INTEGER = assign.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.INTEGER = assign.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with print.NAME = call.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with print.NAME = call.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.INTEGER = call.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.INTEGER = call.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with print.NAME = constant.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.NAME = constant.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.INTEGER = constant.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.INTEGER = constant.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with print.NAME = if.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.NAME = if.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.INTEGER = if.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.INTEGER = if.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with print.NAME = print.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with print.NAME = print.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.INTEGER = print.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.INTEGER = print.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with print.NAME = procedure.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with print.NAME = procedure.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.INTEGER = procedure.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.INTEGER = procedure.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.NAME = read.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with print.NAME = read.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.INTEGER = read.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.INTEGER = read.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with print.NAME = stmt.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.NAME = stmt.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.INTEGER = stmt.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.INTEGER = stmt.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with print.NAME = variable.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with print.NAME = variable.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.INTEGER = variable.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.INTEGER = variable.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.NAME = while.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.NAME = while.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.INTEGER = while.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with print.INTEGER = while.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with procedure.NAME = assign.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.NAME = assign.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.INTEGER = assign.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.INTEGER = assign.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.NAME = call.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with procedure.NAME = call.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.INTEGER = call.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.INTEGER = call.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.NAME = constant.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.NAME = constant.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.INTEGER = constant.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.INTEGER = constant.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.NAME = if.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.NAME = if.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.INTEGER = if.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.INTEGER = if.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.NAME = print.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with procedure.NAME = print.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.INTEGER = print.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.INTEGER = print.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.NAME = procedure.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with procedure.NAME = procedure.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.INTEGER = procedure.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.INTEGER = procedure.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.NAME = read.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with procedure.NAME = read.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.INTEGER = read.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.INTEGER = read.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.NAME = stmt.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.NAME = stmt.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.INTEGER = stmt.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.INTEGER = stmt.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.NAME = variable.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with procedure.NAME = variable.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.INTEGER = variable.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.INTEGER = variable.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.NAME = while.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.NAME = while.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.INTEGER = while.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with procedure.INTEGER = while.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.NAME = assign.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.NAME = assign.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.INTEGER = assign.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.INTEGER = assign.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with read.NAME = call.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with read.NAME = call.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.INTEGER = call.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.INTEGER = call.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with read.NAME = constant.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.NAME = constant.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.INTEGER = constant.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.INTEGER = constant.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with read.NAME = if.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.NAME = if.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.INTEGER = if.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.INTEGER = if.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with read.NAME = print.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with read.NAME = print.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.INTEGER = print.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.INTEGER = print.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with read.NAME = procedure.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with read.NAME = procedure.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.INTEGER = procedure.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.INTEGER = procedure.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.NAME = read.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with read.NAME = read.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.INTEGER = read.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.INTEGER = read.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with read.NAME = stmt.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.NAME = stmt.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.INTEGER = stmt.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.INTEGER = stmt.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with read.NAME = variable.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with read.NAME = variable.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.INTEGER = variable.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.INTEGER = variable.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.NAME = while.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.NAME = while.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.INTEGER = while.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with read.INTEGER = while.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with stmt.NAME = assign.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.NAME = assign.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.INTEGER = assign.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.INTEGER = assign.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with stmt.NAME = call.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.NAME = call.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.INTEGER = call.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.INTEGER = call.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with stmt.NAME = constant.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.NAME = constant.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.INTEGER = constant.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.INTEGER = constant.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with stmt.NAME = if.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.NAME = if.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.INTEGER = if.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.INTEGER = if.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with stmt.NAME = print.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.NAME = print.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.INTEGER = print.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.INTEGER = print.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with stmt.NAME = procedure.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.NAME = procedure.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.INTEGER = procedure.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.INTEGER = procedure.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.NAME = read.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.NAME = read.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.INTEGER = read.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.INTEGER = read.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with stmt.NAME = stmt.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.NAME = stmt.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.INTEGER = stmt.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.INTEGER = stmt.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with stmt.NAME = variable.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.NAME = variable.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.INTEGER = variable.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.INTEGER = variable.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.NAME = while.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.NAME = while.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.INTEGER = while.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with stmt.INTEGER = while.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with variable.NAME = assign.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.NAME = assign.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.INTEGER = assign.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.INTEGER = assign.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.NAME = call.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with variable.NAME = call.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.INTEGER = call.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.INTEGER = call.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.NAME = constant.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.NAME = constant.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.INTEGER = constant.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.INTEGER = constant.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.NAME = if.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.NAME = if.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.INTEGER = if.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.INTEGER = if.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.NAME = print.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with variable.NAME = print.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.INTEGER = print.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.INTEGER = print.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.NAME = procedure.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with variable.NAME = procedure.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.INTEGER = procedure.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.INTEGER = procedure.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.NAME = read.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with variable.NAME = read.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.INTEGER = read.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.INTEGER = read.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.NAME = stmt.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.NAME = stmt.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.INTEGER = stmt.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.INTEGER = stmt.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.NAME = variable.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with variable.NAME = variable.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.INTEGER = variable.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.INTEGER = variable.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.NAME = while.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.NAME = while.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.INTEGER = while.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with variable.INTEGER = while.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.NAME = assign.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.NAME = assign.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.INTEGER = assign.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::AssignDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.INTEGER = assign.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::AssignDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with while.NAME = call.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.NAME = call.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.INTEGER = call.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.INTEGER = call.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::CallDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with while.NAME = constant.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.NAME = constant.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.INTEGER = constant.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ConstantDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.INTEGER = constant.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ConstantDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with while.NAME = if.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.NAME = if.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.INTEGER = if.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::IfDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.INTEGER = if.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::IfDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with while.NAME = print.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.NAME = print.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.INTEGER = print.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.INTEGER = print.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::PrintDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with while.NAME = procedure.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.NAME = procedure.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.INTEGER = procedure.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ProcedureDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.INTEGER = procedure.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::ProcedureDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.NAME = read.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.NAME = read.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.INTEGER = read.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.INTEGER = read.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::ReadDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with while.NAME = stmt.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.NAME = stmt.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.INTEGER = stmt.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::StatementDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.INTEGER = stmt.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::StatementDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }

  SECTION("with while.NAME = variable.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.NAME = variable.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.INTEGER = variable.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::VariableDeclaration>(
        "declaration", QPS::Declaration::Type::NAME)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.INTEGER = variable.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::VariableDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.NAME = while.NAME") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.NAME = while.INTEGER") {
    QPS::Argument arg1{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.INTEGER = while.NAME") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{
        static_cast<std::shared_ptr<QPS::WhileDeclaration>>(nullptr)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == false);
  }

  SECTION("with while.INTEGER = while.INTEGER") {
    QPS::Argument arg1{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};
    QPS::Argument arg2{std::make_shared<QPS::WhileDeclaration>(
        "declaration", QPS::Declaration::Type::INTEGER)};

    QPS::WithClause withClause(arg1, arg2);
    REQUIRE(withClause.validate() == true);
  }
}