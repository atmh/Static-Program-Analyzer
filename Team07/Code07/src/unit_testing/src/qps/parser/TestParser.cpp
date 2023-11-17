#include "catch.hpp"
#include "qps/evaluator/decorator_evaluator/NotClauseEvaluator.h"
#include "qps/evaluator/pattern_evaluator/PatternClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/AffectsClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/CallsClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/CallsStarClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/FollowsClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/FollowsStarClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/ModifiesClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/NextClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/NextStarClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/ParentClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/ParentStarClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/UsesClauseEvaluator.h"
#include "qps/evaluator/with_evaluator/WithClauseEvaluator.h"

#include "qps/exception/Messages.h"
#include "qps/parser/QPSParser.h"
#include "qps/tokenizer/QPSTokenizer.h"

TEST_CASE("Basic Tests QPSParser") {
  /* ----- Valid tests ----- */
  SECTION("Valid declaration and select - 1") {
    const std::string input = "variable v; Select v";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();
    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "v");
    REQUIRE(query.getClauses().empty());
  };

  SECTION("Valid declaration and select - 2") {
    const std::string input = "variable a,bb, BB; Select BB";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "BB");
    REQUIRE(query.getClauses().empty());
  };

  SECTION("Valid declaration and select - 3") {
    const std::string input = "variable a, b,    BB;stmt bb; Select bb";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "bb");
    REQUIRE(query.getClauses().empty());
  };

  SECTION("Valid declaration and select - 4") {
    const std::string input = "variable a, b,    BB;stmt bb; Select bb";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "bb");
    REQUIRE(query.getClauses().empty());
  };

  SECTION("Valid declaration, select and follow clause") {
    const std::string input = "stmt a; Select a such that Follows(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::FollowsClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid declaration, select and follows* clause") {
    const std::string input = "stmt a; Select a such that Follows*(a, 10)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::FollowsStarClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid declaration, select and parent clause") {
    const std::string input = "stmt a; Select a such that Parent(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::ParentClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid declaration, select and parent* clause") {
    const std::string input = "stmt a; Select a such that Parent*(10, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::ParentStarClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid declaration, select and Modifies clause") {
    const std::string input =
        R"(variable a; Select a such that Modifies("hello", a))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::ModifiesClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid declaration, select and Uses clause") {
    const std::string input =
        R"(variable a; Select a such that Uses("hello", a))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::UsesClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid declaration, select and valid pattern clause - 1") {
    const std::string input =
        R"(assign a; Select a pattern a ( _ , "count + 1"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid declaration, select and valid pattern clause - 2") {
    const std::string input = R"(if if; Select if pattern if(_ , _, _))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "if");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid declaration, select and valid pattern clause - 3") {
    const std::string input =
        R"(while while; Select while pattern while( _, _))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() ==
            "while");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid declaration, select and valid pattern clause - 4") {
    const std::string input = R"(if if; Select if pattern if("yx" , _, _))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "if");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid declaration, select and valid pattern clause - 5") {
    const std::string input =
        R"(while while; Select while pattern while("yx", _))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() ==
            "while");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION(
      "Syntactically valid declaration, select and valid pattern clause - 1") {
    const std::string input = R"(procedure p; Select p pattern p("yx" , _, _))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "p");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION(
      "Syntactically valid declaration, select and valid pattern clause - 2") {
    const std::string input = R"(procedure p; Select p pattern p("yx", _))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "p");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid declaration, select and such that valid pattern clause") {
    const std::string input =
        R"(assign a; stmt s; Select a such that Follows*(a, s) pattern a("Follows", "Follows* 1"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 2);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::FollowsStarClauseEvaluator*>(evaluator.get()) !=
            nullptr);
    evaluator = query.getClauses()[1]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid such that clause with StmtRef") {
    const std::string input =
        R"(assign a; stmt b; Select a such that Parent(b , 10))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::ParentClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid such that clause with EntRef") {
    const std::string input =
        R"(assign a; variable v; Select a such that Modifies ("test", v))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::ModifiesClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid such that clause with and") {
    const std::string input =
        R"(assign a; variable v; stmt s1, s2; Select a such that Modifies ("test", v) and Parent (s1, s2))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 2);

    auto evaluator1 = query.getClauses()[0]->createEvaluator();
    auto evaluator2 = query.getClauses()[1]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::ModifiesClauseEvaluator*>(evaluator1.get()) !=
            nullptr);
    REQUIRE(dynamic_cast<QPS::ParentClauseEvaluator*>(evaluator2.get()) !=
            nullptr);
  };

  SECTION("Valid pattern clause with and") {
    const std::string input =
        R"(assign a; variable v; Select a pattern a("Follows", "Follows* 1") and a(v, _"Follows"_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 2);

    auto evaluator1 = query.getClauses()[0]->createEvaluator();
    auto evaluator2 = query.getClauses()[1]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator1.get()) !=
            nullptr);
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator2.get()) !=
            nullptr);
  };

  SECTION("Valid(Syntax) clause with and - 1") {
    const std::string input =
        R"(assign a; variable v; Select a pattern a("Follows", "Follows* 1") and Modifies(a, "Follows"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 2);

    auto evaluator1 = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator1.get()) !=
            nullptr);
    REQUIRE(query.getClauses()[1] == nullptr);
  };

  SECTION("Valid tuple Select") {
    const std::string input = R"(assign a; variable v; Select <a, v>)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().size() == 2);
    REQUIRE(query.getSelectClause().getDeclarations()[0]->name() == "a");
    REQUIRE(query.getSelectClause().getDeclarations()[1]->name() == "v");
  };

  SECTION("Valid not clause - 1") {
    const std::string input =
        R"(assign a; variable v; Select <a, v> such that not Modifies(a, v))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::NotClauseEvaluator*>(evaluator.get()) != nullptr);
  };

  SECTION("Valid not clause - 2") {
    const std::string input =
        R"(assign a; Select a pattern not a("count", "count +1"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::NotClauseEvaluator*>(evaluator.get()) != nullptr);
  };

  SECTION("Valid not clause - 3") {
    const std::string input =
        R"(assign a; Select <a, v> such that not Modifies(a, v) pattern not a("count", _))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getClauses().size() == 2);
    for (const auto& clause : query.getClauses()) {
      REQUIRE(dynamic_cast<QPS::NotClauseEvaluator*>(
                  clause->createEvaluator().get()) != nullptr);
    }
  };

  SECTION("Valid with clause - 1") {
    const std::string input = R"(assign a; Select a with a.stmt# = 10)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getClauses().size() == 1);
    REQUIRE(dynamic_cast<QPS::WithClauseEvaluator*>(
                query.getClauses().front()->createEvaluator().get()) !=
            nullptr);
  };

  SECTION("Valid with clause - 2") {
    const std::string input =
        R"(print pn; read r; Select pn with r1.varName = r2.stmt#)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getClauses().size() == 1);
  };

  /* ----- Invalid tests ----- */
  SECTION("Missing select") {
    const std::string input = "variable a, b,    BB;stmt bb; ";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid declaration - 1") {
    const std::string input = "variable ; Select v";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid declaration - 2") {
    const std::string input = "variable a,; Select a";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid select") {
    const std::string input = "variable v; Select *";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid such that - 1") {
    const std::string input = R"(assign a; stmt s; Select a such)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid such that - 2") {
    const std::string input = R"(assign a; stmt s; Select a such that)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid such that - 3") {
    const std::string input =
        R"(assign a; stmt s; Select a such that NotARelationship(a,s)))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid pattern - 1") {
    const std::string input = R"(assign a; stmt s; Select a pattern)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid pattern - 2") {
    const std::string input = R"(assign a; stmt s; Select a pattern a())";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid pattern - 3") {
    const std::string input =
        R"(assign a; stmt s; Select a pattern a(_,"count*"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid pattern - 4") {
    const std::string input =
        R"(assign a; variable v; Select a pattern("a", "a < 1"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid such that clause with StmtRef") {
    const std::string input =
        R"(assign a; stmt b; Select a such that Parent(b , "count"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid such that clause with EntRef") {
    const std::string input =
        R"(assign a; Select a such that Modifies (a, 10))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid clause with and - 1") {
    const std::string input =
        R"(assign a; variable v; Select a pattern a("Follows", "Follows* 1") and such that Modifies(a, "Follows"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid clause with and - 2") {
    const std::string input =
        R"(assign a; variable v; Select a such that Modifies(a, "Follows") and a("Follows", "Follows* 1"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid not clause - 1") {
    const std::string input =
        R"(assign a; Select <a, v> not such that  Modifies(a, v))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid not clause - 2") {
    const std::string input =
        R"(assign a; Select <a, v> not pattern  Modifies(a, v))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid not clause - 3") {
    const std::string input = R"(assign a; Select <a, v> not)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };
}

TEST_CASE("Comprehensive Tests QPSParser - Declarations") {
  SECTION("Valid No Declaration") {
    const std::string input = R"(Select BOOLEAN)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().empty());
  };

  SECTION("Valid Declarations") {
    const std::string input = R"(assign Select, b; stmt stmt; Select Select)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    const auto& declarations = query.getSelectClause().getDeclarations();
    REQUIRE(declarations[0]->name() == "Select");
  };

  SECTION("Invalid Declaration - 1") {
    const std::string input = R"(assign* a; Select a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Declaration - 2") {
    const std::string input = R"(assign Modifies*, a; Select a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Declaration - 3") {
    const std::string input = R"(assign , a; Select BOOLEAN)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };
}

TEST_CASE("Comprehensive Tests QPSParser - Select Clause") {
  SECTION("Valid Select Elem") {
    const std::string input = R"(procedure Modifies; Select Modifies)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations()[0]->name() == "Modifies");
  };

  SECTION("Valid Select Tuple - 1") {
    const std::string input =
        R"(procedure Modifies; Select <Modifies, Modifies>)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations()[0]->name() == "Modifies");
    REQUIRE(query.getSelectClause().getDeclarations()[1]->name() == "Modifies");
  };

  SECTION("Valid Select Tuple - 2") {
    const std::string input =
        R"(procedure Modifies; assign BOOLEAN, Select; Select <BOOLEAN, Select, Modifies>)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    std::vector<std::string> declaredNames = {"BOOLEAN", "Select", "Modifies"};
    for (int i = 0; i < declaredNames.size(); i++) {
      REQUIRE(query.getSelectClause().getDeclarations()[i]->name() ==
              declaredNames[i]);
    }
  };

  SECTION("Syntactically Valid Select Elem") {
    const std::string input = R"(Select Affects)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
  };

  SECTION("Syntactically Valid Select Tuple - 1") {
    const std::string input = R"(Select <Modifies, Modifies>)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations()[0] == nullptr);
    REQUIRE(query.getSelectClause().getDeclarations()[1] == nullptr);
  };

  SECTION("Syntactically Valid Select Tuple - 2") {
    const std::string input = R"(Select <BOOLEAN, Select, Modifies>)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    for (int i = 0; i < 3; i++) {
      REQUIRE(query.getSelectClause().getDeclarations()[i] == nullptr);
    }
  };

  SECTION("Invalid Select Elem") {
    const std::string input = R"(Select Parent*)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Select Tuple - 1") {
    const std::string input = R"(Select <a,>)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Select Tuple - 2") {
    const std::string input = R"(Select <a,321>)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Select Tuple - 3") {
    const std::string input = R"(Select <a,Modifies*>)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };
}

TEST_CASE(
    "Comprehensive Tests QPSParser - Such That Clause (StmtRef, StmtRef)") {

  SECTION("Syntactically Valid Follows clause") {
    const std::string input =
        R"(assign a; Select a such that Follows(123,321))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::FollowsClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Follows* clause") {
    const std::string input =
        R"(assign a; Select a such that Follows*(123,321))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::FollowsStarClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Parent clause") {
    const std::string input = R"(assign a; Select a such that Parent(123,321))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::ParentClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Parent* clause") {
    const std::string input =
        R"(assign a; Select a such that Parent*(123,321))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::ParentStarClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Invalid Calls clause") {
    const std::string input = R"(assign a; Select a such that Calls(123,321))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Calls* clause") {
    const std::string input = R"(assign a; Select a such that Calls*(123,321))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Syntactically Valid Next clause") {
    const std::string input = R"(assign a; Select a such that Next(123,321))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::NextClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Next* clause") {
    const std::string input = R"(assign a; Select a such that Next*(123,321))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::NextStarClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Affects clause") {
    const std::string input =
        R"(assign a; Select a such that Affects(123,321))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::AffectsClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Follows clause") {
    const std::string input = R"(assign a; Select a such that Follows(123,_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::FollowsClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Follows* clause") {
    const std::string input = R"(assign a; Select a such that Follows*(123,_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::FollowsStarClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Parent clause") {
    const std::string input = R"(assign a; Select a such that Parent(123,_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::ParentClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Parent* clause") {
    const std::string input = R"(assign a; Select a such that Parent*(123,_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::ParentStarClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Invalid Calls clause") {
    const std::string input = R"(assign a; Select a such that Calls(123,_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Calls* clause") {
    const std::string input = R"(assign a; Select a such that Calls*(123,_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Syntactically Valid Next clause") {
    const std::string input = R"(assign a; Select a such that Next(123,_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::NextClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Next* clause") {
    const std::string input = R"(assign a; Select a such that Next*(123,_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::NextStarClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Affects clause") {
    const std::string input = R"(assign a; Select a such that Affects(123,_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::AffectsClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Follows clause") {
    const std::string input = R"(assign a; Select a such that Follows(_,123))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::FollowsClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Follows* clause") {
    const std::string input = R"(assign a; Select a such that Follows*(_,123))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::FollowsStarClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Parent clause") {
    const std::string input = R"(assign a; Select a such that Parent(_,123))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::ParentClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Parent* clause") {
    const std::string input = R"(assign a; Select a such that Parent*(_,123))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::ParentStarClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Invalid Calls clause") {
    const std::string input = R"(assign a; Select a such that Calls(_,123))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Calls* clause") {
    const std::string input = R"(assign a; Select a such that Calls*(_,123))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Syntactically Valid Next clause") {
    const std::string input = R"(assign a; Select a such that Next(_,123))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::NextClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Next* clause") {
    const std::string input = R"(assign a; Select a such that Next*(_,123))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::NextStarClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Affects clause") {
    const std::string input = R"(assign a; Select a such that Affects(_,123))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::AffectsClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };
}

TEST_CASE("Comprehensive Tests QPSParser - Such That Clause (EntRef, EntRef)") {

  SECTION("Invalid Follows clause") {
    const std::string input =
        R"(assign a; Select a such that Follows("Calls","Affects"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Follows* clause") {
    const std::string input =
        R"(assign a; Select a such that Follows*("Calls","Affects"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Parent clause") {
    const std::string input =
        R"(assign a; Select a such that Parent("Calls","Affects"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Parent* clause") {
    const std::string input =
        R"(assign a; Select a such that Parent*("Calls","Affects"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Syntactically Valid Modifies clause") {
    const std::string input =
        R"(assign a; Select a such that Modifies("Calls","Affects"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::ModifiesClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Uses clause") {
    const std::string input =
        R"(assign a; Select a such that Uses("Calls","Affects"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::UsesClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Calls clause") {
    const std::string input =
        R"(assign a; Select a such that Calls("Calls","Affects"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::CallsClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Calls* clause") {
    const std::string input =
        R"(assign a; Select a such that Calls*("Calls","Affects"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::CallsStarClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Invalid Next clause") {
    const std::string input =
        R"(assign a; Select a such that Next("Calls","Affects"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Next* clause") {
    const std::string input =
        R"(assign a; Select a such that Next*("Calls","Affects"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Affects clause") {
    const std::string input =
        R"(assign a; Select a such that Affects("Calls","Affects"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Follows clause") {
    const std::string input =
        R"(assign a; Select a such that Follows("Next",_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Follows* clause") {
    const std::string input =
        R"(assign a; Select a such that Follows*("Next",_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Parent clause") {
    const std::string input =
        R"(assign a; Select a such that Parent("Next",_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Parent* clause") {
    const std::string input =
        R"(assign a; Select a such that Parent*("Next",_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Syntactically Valid Modifies clause") {
    const std::string input =
        R"(assign a; Select a such that Modifies("Next",_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::ModifiesClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Uses clause") {
    const std::string input = R"(assign a; Select a such that Uses("Next",_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::UsesClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Calls clause") {
    const std::string input = R"(assign a; Select a such that Calls("Next",_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::CallsClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Calls* clause") {
    const std::string input =
        R"(assign a; Select a such that Calls*("Next",_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::CallsStarClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Invalid Next clause") {
    const std::string input = R"(assign a; Select a such that Next("Next",_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Next* clause") {
    const std::string input = R"(assign a; Select a such that Next*("Next",_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Affects clause") {
    const std::string input =
        R"(assign a; Select a such that Affects("Next",_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Follows clause") {
    const std::string input =
        R"(assign a; Select a such that Follows(_,"not"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Follows* clause") {
    const std::string input =
        R"(assign a; Select a such that Follows*(_,"not"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Parent clause") {
    const std::string input = R"(assign a; Select a such that Parent(_,"not"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Parent* clause") {
    const std::string input =
        R"(assign a; Select a such that Parent*(_,"not"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Syntactically Valid Modifies clause") {
    const std::string input =
        R"(assign a; Select a such that Modifies(_,"not"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::ModifiesClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Uses clause") {
    const std::string input = R"(assign a; Select a such that Uses(_,"not"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::UsesClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Calls clause") {
    const std::string input = R"(assign a; Select a such that Calls(_,"not"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::CallsClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Calls* clause") {
    const std::string input = R"(assign a; Select a such that Calls*(_,"not"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::CallsStarClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Invalid Next clause") {
    const std::string input = R"(assign a; Select a such that Next(_,"not"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Next* clause") {
    const std::string input = R"(assign a; Select a such that Next*(_,"not"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Affects clause") {
    const std::string input =
        R"(assign a; Select a such that Affects(_,"not"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };
}

TEST_CASE(
    "Comprehensive Tests QPSParser - Such That Clause (StmtRef, EntRef)") {
  SECTION("Invalid Follows clause") {
    const std::string input =
        R"(assign a; Select a such that Follows(123,"a123"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Follows* clause") {
    const std::string input =
        R"(assign a; Select a such that Follows*(123,"a123"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Parent clause") {
    const std::string input =
        R"(assign a; Select a such that Parent(123,"a123"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Parent* clause") {
    const std::string input =
        R"(assign a; Select a such that Parent*(123,"a123"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Syntactically Valid Modifies clause") {
    const std::string input =
        R"(assign a; Select a such that Modifies(123,"a123"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::ModifiesClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Uses clause") {
    const std::string input =
        R"(assign a; Select a such that Uses(123,"a123"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::UsesClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Invalid Calls clause") {
    const std::string input =
        R"(assign a; Select a such that Calls(123,"a123"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Calls* clause") {
    const std::string input =
        R"(assign a; Select a such that Calls*(123,"a123"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Next clause") {
    const std::string input =
        R"(assign a; Select a such that Next(123,"a123"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Next* clause") {
    const std::string input =
        R"(assign a; Select a such that Next*(123,"a123"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Affects clause") {
    const std::string input =
        R"(assign a; Select a such that Affects(123,"a123"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };
}

TEST_CASE(
    "Comprehensive Tests QPSParser - Such That Clause (EntRef, StmtRef)") {

  SECTION("Invalid Follows clause") {
    const std::string input =
        R"(assign a; Select a such that Follows("a123",123))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Follows* clause") {
    const std::string input =
        R"(assign a; Select a such that Follows*("a123",123))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Parent clause") {
    const std::string input =
        R"(assign a; Select a such that Parent("a123",123))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Parent* clause") {
    const std::string input =
        R"(assign a; Select a such that Parent*("a123",123))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Modifies clause") {
    const std::string input =
        R"(assign a; Select a such that Modifies("a123",123))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Uses clause") {
    const std::string input =
        R"(assign a; Select a such that Uses("a123",123))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Calls clause") {
    const std::string input =
        R"(assign a; Select a such that Calls("a123",123))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Calls* clause") {
    const std::string input =
        R"(assign a; Select a such that Calls*("a123",123))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Next clause") {
    const std::string input =
        R"(assign a; Select a such that Next("a123",123))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Next* clause") {
    const std::string input =
        R"(assign a; Select a such that Next*("a123",123))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Affects clause") {
    const std::string input =
        R"(assign a; Select a such that Affects("a123",123))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };
}

TEST_CASE("Comprehensive Tests QPSParser - Such That Clause - Invalid") {
  SECTION("Invalid clause - 1") {
    const std::string input = R"(assign a; Select a such that Affects(__,_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid clause - 2") {
    const std::string input = R"(assign a; Select a such that Uses(_,_,))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid clause - 3") {
    const std::string input = R"(assign a; Select a such that Modifies(%,_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid clause - 4") {
    const std::string input = R"(assign a; Select a such that Affects(_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };
}

TEST_CASE("Comprehensive Tests QPSParser - Pattern Clause") {
  SECTION("Syntactically Valid Assign Pattern clause - 1") {
    const std::string input =
        R"(assign a; Select a pattern a("a123", "expression"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Assign Pattern clause - 2") {
    const std::string input =
        R"(assign a; Select a pattern a("a123", "expression + 753"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Assign Pattern clause - 3") {
    const std::string input = R"(assign a; Select a pattern a(_, _))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid Assign Pattern clause - 4") {
    const std::string input =
        "assign a; Select a pattern a(_, _\"expression + ((753))\"_)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid If Pattern clause - 5") {
    const std::string input = "if if; Select if pattern if(_, _, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "if");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid If Pattern clause - 6") {
    const std::string input =
        "while while; Select while pattern while(_, _, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() ==
            "while");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid If Pattern clause - 7") {
    const std::string input = "if if; Select if pattern if(\"hello\", _, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "if");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid If Pattern clause - 8") {
    const std::string input = "if if; Select if pattern if(_, _, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "if");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid If Pattern clause - 9") {
    const std::string input = "while while; Select while pattern while(_, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() ==
            "while");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid If Pattern clause - 10") {
    const std::string input =
        "while while; Select while pattern while(\"hello\", _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() ==
            "while");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::PatternClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };
}

TEST_CASE("Comprehensive Tests QPSParser - With Clause") {
  SECTION("Valid With Clause - 1") {
    const std::string input =
        R"(procedure p; call c; Select p with p.procName = c.procName)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "p");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::WithClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid With Clause - 2") {
    const std::string input =
        R"(procedure p; variable v; Select p with p.procName = v.varName)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "p");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::WithClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid With Clause - 3") {
    const std::string input =
        R"(procedure p; read r; Select p with p.procName = r.varName)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "p");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::WithClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid With Clause - 4") {
    const std::string input =
        R"(procedure p; print pn; Select p with p.procName = pn.varName)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "p");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::WithClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid With Clause - 5") {
    const std::string input =
        R"(constant c; stmt s; Select c with s.stmt# = c.value)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "c");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::WithClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid With Clause - 6") {
    const std::string input =
        R"(constant c; read r; Select c with r.stmt# = c.value)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "c");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::WithClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid With Clause - 7") {
    const std::string input =
        R"(constant c; print pn; Select c with pn.stmt# = c.value)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "c");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::WithClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid With Clause - 8") {
    const std::string input =
        R"(constant c; call call; Select c with call.stmt# = c.value)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "c");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::WithClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid With Clause - 9") {
    const std::string input =
        R"(constant c; while w; Select c with w.stmt# = c.value)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "c");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::WithClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid With Clause - 10") {
    const std::string input =
        R"(constant c; if if; Select c with if.stmt# = c.value)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "c");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::WithClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Valid With Clause - 11") {
    const std::string input =
        R"(constant c; assign a; Select c with a.stmt# = c.value)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "c");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::WithClauseEvaluator*>(evaluator.get()) !=
            nullptr);
  };

  SECTION("Syntactically Valid With Clause - 1") {
    const std::string input =
        R"(procedure p; assign a; Select p with p.stmt# = a.value)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "p");
    REQUIRE(query.getClauses().size() == 1);
  };

  SECTION("Syntactically Valid With Clause - 2") {
    const std::string input =
        R"(constant c; call call; Select call with c.procName = call.varName)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() ==
            "call");
    REQUIRE(query.getClauses().size() == 1);
  };

  SECTION("Syntactically Valid With Clause - 3") {
    const std::string input = R"(Select c with a.stmt# = c.value)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front() == nullptr);
    REQUIRE(query.getClauses().size() == 1);
  };

  SECTION("Invalid With Clause - 1") {
    const std::string input =
        R"(constant c; call call; Select call with c.value == call.varName)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid With Clause - 2") {
    const std::string input =
        R"(constant c; call call; Select call with c.attr = call.varName)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid With Clause - 3") {
    const std::string input =
        R"(constant c; call call; Select call with c.value == call.varname)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid With Clause - 3") {
    const std::string input =
        R"(constant c; call call; Select call with c.value == call)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };
}

TEST_CASE("Comprehensive Tests QPSParser - Such That Clause - Not Clause") {
  SECTION("Syntactically Valid Not clause") {
    const std::string input =
        R"(assign a; Select a such that not Follows(123,321))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::NotClauseEvaluator*>(evaluator.get()) != nullptr);
  };

  SECTION("Syntactically Valid Not clause - 2") {
    const std::string input =
        "assign a; Select a pattern not a(_, _\"expression + ((753))\"_)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::NotClauseEvaluator*>(evaluator.get()) != nullptr);
  };

  SECTION("Syntactically Valid Not clause - 3") {
    const std::string input =
        "print pn; read read; Select <pn, read> with not pn.varName = "
        "read.varName";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations()[0]->name() == "pn");
    REQUIRE(query.getSelectClause().getDeclarations()[1]->name() == "read");
    REQUIRE(query.getClauses().size() == 1);

    auto evaluator = query.getClauses()[0]->createEvaluator();
    REQUIRE(dynamic_cast<QPS::NotClauseEvaluator*>(evaluator.get()) != nullptr);
  };

  SECTION("Invalid Not clause - 1") {
    const std::string input =
        R"(assign a; Select a such that not Calls(123,"a123"))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Not clause - 2") {
    const std::string input =
        R"(assign a; Select a not such that Follows(123,321))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Not clause - 3") {
    const std::string input = "if if; Select if pattern not if(_, _, \"aaa\")";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };

  SECTION("Invalid Not clause - 2") {
    const std::string input =
        "while while; Select while not pattern while(_, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };
}

TEST_CASE("Comprehensive Tests QPSParser - Such That Clause - MultiClause") {
  SECTION("Syntactically Valid MultiClause") {
    const std::string input =
        R"(assign a; variable v; Select a such that Follows(123,321) and Follows(456,567) and Modifies(a, v) pattern a(_,_) and not a("count", "count + 1") with a.stmt# = 1)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    REQUIRE(query.isValid());
    REQUIRE(query.getSelectClause().getDeclarations().front()->name() == "a");
    REQUIRE(query.getClauses().size() == 6);
  };

  SECTION("Invalid MultiClause") {
    const std::string input =
        R"(assign a; variable v; Select a such that Follows(123,321) and pattern a(_,_))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    REQUIRE_THROWS(qpsParser.parse());
  };
}
