#include "catch.hpp"
#include "qps/exception/Messages.h"
#include "qps/parser/QPSParser.h"
#include "qps/tokenizer/QPSTokenizer.h"
#include "qps/validator/Validator.h"

TEST_CASE("Test QPS Validator") {
  /* ----- Valid tests ----- */
  SECTION("Valid declaration and select - 1") {
    const std::string input = "variable v; Select v";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(query.getClauses().size() == 0);
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration and select - 2") {
    const std::string input = "variable a, b,    BB;stmt bb; Select bb";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration and select - 3") {
    const std::string input = "Select BOOLEAN";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Redeclaration") {
    const std::string input = "read a; variable a; Select a";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Missing declaration - 1") {
    const std::string input = "read b; Select a";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Missing declaration - 2") {
    const std::string input = "read a; stmt s; Select <a,s,t>";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Missing declaration - 3") {
    const std::string input = "read a; Select <a,BOOLEAN>";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Valid declaration, select and Follows/Follows* clause - 1") {
    const std::string input = "stmt a; Select a such that Follows*(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Follows/Follows* clause - 2") {
    const std::string input = "stmt a; Select a such that Follows*(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Follows/Follows* clause - 3") {
    const std::string input = "read a; Select a such that Follows(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Follows/Follows* clause - 4") {
    const std::string input = "read a; Select a such that Follows(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Follows/Follows* clause - 5") {
    const std::string input = "print a; Select a such that Follows*(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Follows/Follows* clause - 6") {
    const std::string input = "print a; Select a such that Follows*(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Follows/Follows* clause - 7") {
    const std::string input = "call a; Select a such that Follows*(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Follows/Follows* clause - 8") {
    const std::string input = "call a; Select a such that Follows*(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Follows/Follows* clause - 9") {
    const std::string input = "while a; Select a such that Follows*(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Follows/Follows* clause - 10") {
    const std::string input = "while a; Select a such that Follows*(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Follows/Follows* clause - 11") {
    const std::string input = "if a; Select a such that Follows*(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Follows/Follows* clause - 12") {
    const std::string input = "if a; Select a such that Follows*(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Follows/Follows* clause - 13") {
    const std::string input = "assign a; Select a such that Follows(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Follows/Follows* clause - 14") {
    const std::string input = "assign a; Select a such that Follows(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Invalid declaration, select and Follows/Follows* clause - 1") {
    const std::string input = "variable a; Select a such that Follows*(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and Follows/Follows* clause - 2") {
    const std::string input = "variable a; Select a such that Follows*(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and Follows/Follows* clause - 3") {
    const std::string input = "constant a; Select a such that Follows*(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and Follows/Follows* clause - 4") {
    const std::string input = "constant a; Select a such that Follows*(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and Follows/Follows* clause - 5") {
    const std::string input = "procedure a; Select a such that Follows(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and Follows/Follows* clause - 6") {
    const std::string input = "procedure a; Select a such that Follows(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Valid declaration, select and Parent/Parent* clause - 1") {
    const std::string input = "stmt a; Select a such that Parent*(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Parent/Parent* clause - 2") {
    const std::string input = "stmt a; Select a such that Parent*(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Parent/Parent* clause - 3") {
    const std::string input = "read a; Select a such that Parent(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Parent/Parent* clause - 4") {
    const std::string input = "read a; Select a such that Parent(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Parent/Parent* clause - 5") {
    const std::string input = "print a; Select a such that Parent(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Parent/Parent* clause - 6") {
    const std::string input = "print a; Select a such that Parent(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Parent/Parent* clause - 7") {
    const std::string input = "call a; Select a such that Parent(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Parent/Parent* clause - 8") {
    const std::string input = "call a; Select a such that Parent(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Parent/Parent* clause - 9") {
    const std::string input = "while a; Select a such that Parent*(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Parent/Parent* clause - 10") {
    const std::string input = "while a; Select a such that Parent*(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Parent/Parent* clause - 11") {
    const std::string input = "if a; Select a such that Parent*(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Parent/Parent* clause - 12") {
    const std::string input = "if a; Select a such that Parent*(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Parent/Parent* clause - 13") {
    const std::string input = "assign a; Select a such that Parent(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Parent/Parent* clause - 14") {
    const std::string input = "assign a; Select a such that Parent(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Invalid declaration, select and Parent/Parent* clause - 1") {
    const std::string input = "variable a; Select a such that Parent(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and Parent/Parent* clause - 2") {
    const std::string input = "variable a; Select a such that Parent(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and Parent/Parent* clause - 3") {
    const std::string input = "constant a; Select a such that Parent(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and Parent/Parent* clause - 4") {
    const std::string input = "constant a; Select a such that Parent(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and Parent/Parent* clause - 5") {
    const std::string input = "procedure a; Select a such that Parent*(a, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and Parent/Parent* clause - 6") {
    const std::string input = "procedure a; Select a such that Parent*(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Valid declaration, select and Modifies clause - 1") {
    const std::string input =
        "read a; variable v; Select a such that Modifies(a, v)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Modifies clause - 2") {
    const std::string input =
        "call a; variable v; Select a such that Modifies(a, v)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Modifies clause - 3") {
    const std::string input =
        "while a; variable v; Select a such that Modifies(a, v)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Modifies clause - 4") {
    const std::string input =
        "if a; variable v; Select a such that Modifies(a, v)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Modifies clause - 5") {
    const std::string input =
        "assign a; variable v; Select a such that Modifies(a, v)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Modifies clause - 6") {
    const std::string input =
        "procedure a; variable v; Select a such that Modifies(a, v)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Modifies clause - 7") {
    const std::string input =
        "stmt a; variable v; Select a such that Modifies(a, v)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Modifies clause - 8") {
    const std::string input =
        "print a; variable v; Select a such that Modifies(a, v)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Invalid declaration, select and Modifies clause - 1") {
    const std::string input =
        "constant a; variable v; Select a such that Modifies(a, v)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and Modifies clause - 2") {
    const std::string input =
        "variable a; variable v; Select a such that Modifies(a, v)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and Modifies clause - 3") {
    const std::string input = "variable a; Select a such that Modifies(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and Modifies clause - 4") {
    const std::string input =
        "read a; while w; Select a such that Modifies(a, w)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Valid declaration, select and Uses clause - 1") {
    const std::string input =
        "print a; variable v; Select a such that Uses(a, v)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Uses clause - 2") {
    const std::string input =
        "call a; variable v; Select a such that Uses(a, v)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Uses clause - 3") {
    const std::string input =
        "while a; variable v; Select a such that Uses(a, v)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Uses clause - 4") {
    const std::string input = "if a; variable v; Select a such that Uses(a, v)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Uses clause - 5") {
    const std::string input =
        "assign a; variable v; Select a such that Uses(a, v)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Uses clause - 6") {
    const std::string input =
        "procedure a; variable v; Select a such that Uses(a, v)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Uses clause - 7") {
    const std::string input =
        "stmt a; variable v; Select a such that Uses(a, v)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Uses clause - 8") {
    const std::string input =
        "read a; variable v; Select a such that Uses(a, v)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Invalid declaration, select and Uses clause - 1") {
    const std::string input =
        "constant a; variable v; Select a such that Uses(a, v)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Valid declaration, select and Uses clause - 2") {
    const std::string input =
        "variable a; variable v; Select a such that Uses(a, v)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and Uses clause - 3") {
    const std::string input = "variable a; Select a such that Uses(_, a)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and Uses clause - 4") {
    const std::string input = "read a; while w; Select a such that Uses(a, w)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Valid declaration, select and Pattern clause - 1") {
    const std::string input =
        "assign a; variable v; Select a pattern a(v, \"1 + 2\")";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Pattern clause - 2") {
    const std::string input = "if if; variable v; Select v pattern if(v, _, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Valid declaration, select and Pattern clause - 3") {
    const std::string input =
        "while while; variable v; Select v pattern while(v, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE(validator.validate());
  };

  SECTION("Invalid declaration, select and Pattern clause - 1") {
    const std::string input =
        "assign a; while v; Select a pattern a(v, \"1 + 2\")";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and Pattern clause - 2") {
    const std::string input =
        "read a; variable v; Select a pattern a(v, \"1 + 2\")";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and Pattern clause - 3") {
    const std::string input = "if if; variable v; Select v pattern if(v, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and Pattern clause - 4") {
    const std::string input =
        "if if; variable v; Select v pattern if(v, \"count\")";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and Pattern clause - 5") {
    const std::string input =
        "while while; variable v; Select v pattern while(v, _, _)";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and valid pattern clause - 1") {
    const std::string input = R"(procedure p; Select p pattern p("yx" , _, _))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };

  SECTION("Invalid declaration, select and valid pattern clause - 2") {
    const std::string input = R"(procedure p; Select p pattern p("yx", _))";
    QPS::QPSParser qpsParser(QPS::QPSTokenizer(input).tokenize());
    qpsParser.parse();
    auto query = qpsParser.getQuery();

    QPS::Validator validator(query, qpsParser.getDeclaredNames());
    REQUIRE_THROWS(validator.validate());
  };
}
