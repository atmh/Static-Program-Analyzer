#include <string>
#include <vector>

#include "catch.hpp"
#include "qps/tokenizer/QPSTokenizer.h"

TEST_CASE("Test QPS Tokenizer") {
  /* ----- Valid tests ----- */
  using tt = Common::TokenType;

  SECTION("Valid declaration") {
    std::string input = "variable v; stmt s;";
    QPS::QPSTokenizer qps_tokenizer = QPS::QPSTokenizer(input);
    auto tokens = qps_tokenizer.tokenize();
    std::vector<Common::Token> expected{
        {"variable", tt::name}, {"v", tt::name}, {";", tt::special},
        {"stmt", tt::name},     {"s", tt::name}, {";", tt::special},
    };

    REQUIRE(tokens == expected);
  };

  SECTION("Valid select") {
    std::string input = "Select a";
    QPS::QPSTokenizer qps_tokenizer = QPS::QPSTokenizer(input);
    auto tokens = qps_tokenizer.tokenize();

    std::vector<Common::Token> expected{
        {"Select", tt::name},
        {"a", tt::name},
    };

    REQUIRE(tokens == expected);
  };

  SECTION("Valid pattern without wildcards") {
    std::string input = R"(pattern a(    "x","y"))";
    QPS::QPSTokenizer qps_tokenizer = QPS::QPSTokenizer(input);
    auto tokens = qps_tokenizer.tokenize();

    std::vector<Common::Token> expected{
        {"pattern", tt::name}, {"a", tt::name},     {"(", tt::special},
        {"\"", tt::special},   {"x", tt::name},     {"\"", tt::special},
        {",", tt::special},    {"\"", tt::special}, {"y", tt::name},
        {"\"", tt::special},   {")", tt::special}};

    REQUIRE(tokens == expected);
  };

  SECTION("Valid pattern with wildcards") {
    std::string input = R"(pattern a(_, _"x*y"_))";
    QPS::QPSTokenizer qps_tokenizer = QPS::QPSTokenizer(input);
    auto tokens = qps_tokenizer.tokenize();

    std::vector<Common::Token> expected{
        {"pattern", tt::name}, {"a", tt::name},     {"(", tt::special},
        {"_", tt::special},    {",", tt::special},  {"_", tt::special},
        {"\"", tt::special},   {"x", tt::name},     {"*", tt::special},
        {"y", tt::name},       {"\"", tt::special}, {"_", tt::special},
        {")", tt::special}};

    REQUIRE(tokens == expected);
  };

  SECTION("Valid such that clause without * or _") {
    std::string input = R"(such that Uses (a, "x"))";
    QPS::QPSTokenizer qps_tokenizer = QPS::QPSTokenizer(input);
    auto tokens = qps_tokenizer.tokenize();

    std::vector<Common::Token> expected{
        {"such", tt::name},  {"that", tt::name}, {"Uses", tt::name},
        {"(", tt::special},  {"a", tt::name},    {",", tt::special},
        {"\"", tt::special}, {"x", tt::name},    {"\"", tt::special},
        {")", tt::special}};

    REQUIRE(tokens == expected);
  };

  SECTION("Valid such that clause with *") {
    std::string input = R"(such that Parent* (w, a))";
    QPS::QPSTokenizer qps_tokenizer = QPS::QPSTokenizer(input);
    auto tokens = qps_tokenizer.tokenize();

    std::vector<Common::Token> expected{
        {"such", tt::name}, {"that", tt::name}, {"Parent*", tt::name},
        {"(", tt::special}, {"w", tt::name},    {",", tt::special},
        {"a", tt::name},    {")", tt::special}};

    REQUIRE(tokens == expected);
  };

  SECTION("Valid tuple select") {
    std::string input = R"(Select <a, v>)";
    QPS::QPSTokenizer qps_tokenizer = QPS::QPSTokenizer(input);
    auto tokens = qps_tokenizer.tokenize();

    std::vector<Common::Token> expected{
        {"Select", tt::name}, {"<", tt::special}, {"a", tt::name},
        {",", tt::special},   {"v", tt::name},    {">", tt::special}};
    REQUIRE(tokens == expected);
  };

  SECTION("Valid select stmt#") {
    std::string input = R"(Select v.stmt#)";
    QPS::QPSTokenizer qps_tokenizer = QPS::QPSTokenizer(input);
    auto tokens = qps_tokenizer.tokenize();

    std::vector<Common::Token> expected{{"Select", tt::name},
                                        {"v", tt::name},
                                        {".", tt::special},
                                        {"stmt#", tt::name}};
    REQUIRE(tokens == expected);
  };

  /* ----- Invalid tests ----- */
  SECTION("Invalid integer") {
    std::string input = "stmt 11c";
    QPS::QPSTokenizer qps_tokenizer = QPS::QPSTokenizer(input);
    REQUIRE_THROWS(qps_tokenizer.tokenize());
  };

  SECTION("Invalid op - 1") {
    std::string input = R"(pattern a(_, _"x&y"_))";
    QPS::QPSTokenizer qps_tokenizer = QPS::QPSTokenizer(input);
    REQUIRE_THROWS(qps_tokenizer.tokenize());
  };

  SECTION("Invalid op - 2") {
    std::string input = R"(pattern a(_, _"x#y"_))";
    QPS::QPSTokenizer qps_tokenizer = QPS::QPSTokenizer(input);
    REQUIRE_THROWS(qps_tokenizer.tokenize());
  };
}
