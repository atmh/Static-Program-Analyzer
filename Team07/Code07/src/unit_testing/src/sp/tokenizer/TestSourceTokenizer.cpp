#include "catch.hpp"
#include "sp/tokenizer/SourceTokenizer.h"

using namespace SP;

using Token = Common::Token;
using Type = Common::TokenType;

TEST_CASE("Valid tokenize") {
  SECTION("Valid input + and = op") {
    std::string input = "procedure a1b2c3d { x = 1 + 222; }";
    std::stringstream ss(input);
    SourceTokenizer sourceTokenizer = SourceTokenizer(&ss);
    auto tokens = sourceTokenizer.tokenize();

    std::vector<Token> expected = {
        {"procedure", Type::name}, {"a1b2c3d", Type::name},
        {"{", Type::special},      {"x", Type::name},
        {"=", Type::special},      {"1", Type::integer},
        {"+", Type::special},      {"222", Type::integer},
        {";", Type::special},      {"}", Type::special}};

    REQUIRE(tokens == expected);
  };

  SECTION("Valid input < op") {
    std::string input = "procedure a { x < 1; }";
    std::stringstream ss(input);
    SourceTokenizer sourceTokenizer = SourceTokenizer(&ss);
    auto tokens = sourceTokenizer.tokenize();

    std::vector<Token> expected = {
        {"procedure", Type::name}, {"a", Type::name},    {"{", Type::special},
        {"x", Type::name},         {"<", Type::special}, {"1", Type::integer},
        {";", Type::special},      {"}", Type::special}};

    REQUIRE(tokens == expected);
  };

  SECTION("Valid input > op") {
    std::string input = "procedure a { x > 1; }";
    std::stringstream ss(input);
    SourceTokenizer sourceTokenizer = SourceTokenizer(&ss);
    auto tokens = sourceTokenizer.tokenize();

    std::vector<Token> expected = {
        {"procedure", Type::name}, {"a", Type::name},    {"{", Type::special},
        {"x", Type::name},         {">", Type::special}, {"1", Type::integer},
        {";", Type::special},      {"}", Type::special}};

    REQUIRE(tokens == expected);
  };

  SECTION("Valid input && op") {
    std::string input = "procedure a { x && y; }";
    std::stringstream ss(input);
    SourceTokenizer sourceTokenizer = SourceTokenizer(&ss);
    auto tokens = sourceTokenizer.tokenize();

    std::vector<Token> expected = {
        {"procedure", Type::name}, {"a", Type::name},     {"{", Type::special},
        {"x", Type::name},         {"&&", Type::special}, {"y", Type::name},
        {";", Type::special},      {"}", Type::special}};

    REQUIRE(tokens == expected);
  };

  SECTION("Valid input || op") {
    std::string input = "procedure a { x || y; }";
    std::stringstream ss(input);
    SourceTokenizer sourceTokenizer = SourceTokenizer(&ss);
    auto tokens = sourceTokenizer.tokenize();

    std::vector<Token> expected = {
        {"procedure", Type::name}, {"a", Type::name},     {"{", Type::special},
        {"x", Type::name},         {"||", Type::special}, {"y", Type::name},
        {";", Type::special},      {"}", Type::special}};

    REQUIRE(tokens == expected);
  };

  SECTION("Valid input all ops") {
    std::string input =
        "procedure a { ( ) ; % + - * / > >= < <= = == ! != && || }";
    std::stringstream ss(input);
    SourceTokenizer sourceTokenizer = SourceTokenizer(&ss);
    auto tokens = sourceTokenizer.tokenize();

    std::vector<Token> expected = {
        {"procedure", Type::name}, {"a", Type::name},     {"{", Type::special},
        {"(", Type::special},      {")", Type::special},  {";", Type::special},
        {"%", Type::special},      {"+", Type::special},  {"-", Type::special},
        {"*", Type::special},      {"/", Type::special},  {">", Type::special},
        {">=", Type::special},     {"<", Type::special},  {"<=", Type::special},
        {"=", Type::special},      {"==", Type::special}, {"!", Type::special},
        {"!=", Type::special},     {"&&", Type::special}, {"||", Type::special},
        {"}", Type::special}};

    REQUIRE(tokens == expected);
  };

  SECTION("Valid input with line break") {
    std::string input = "procedure a { \n x = 1; }";
    std::stringstream ss(input);
    SourceTokenizer sourceTokenizer = SourceTokenizer(&ss);
    auto tokens = sourceTokenizer.tokenize();

    std::vector<Token> expected = {
        {"procedure", Type::name}, {"a", Type::name},    {"{", Type::special},
        {"x", Type::name},         {"=", Type::special}, {"1", Type::integer},
        {";", Type::special},      {"}", Type::special}};

    REQUIRE(tokens == expected);
  };

  SECTION("Valid input without space 1") {
    std::string input = "procedure a{x=1;}";
    std::stringstream ss(input);
    SourceTokenizer sourceTokenizer = SourceTokenizer(&ss);
    auto tokens = sourceTokenizer.tokenize();

    std::vector<Token> expected = {
        {"procedure", Type::name}, {"a", Type::name},    {"{", Type::special},
        {"x", Type::name},         {"=", Type::special}, {"1", Type::integer},
        {";", Type::special},      {"}", Type::special}};

    REQUIRE(tokens == expected);
  };
}

TEST_CASE("Invalid tokenize") {
  SECTION("Invalid special token") {
    std::string input = "procedure a { x = ^; }";
    std::stringstream ss(input);
    SourceTokenizer sourceTokenizer = SourceTokenizer(&ss);
    REQUIRE_THROWS(sourceTokenizer.tokenize());
  };

  SECTION("Invalid & op") {
    std::string input = "procedure a { x & 1; }";
    std::stringstream ss(input);
    SourceTokenizer sourceTokenizer = SourceTokenizer(&ss);
    REQUIRE_THROWS(sourceTokenizer.tokenize());
  };

  SECTION("Invalid | op") {
    std::string input = "procedure a { x | 1; }";
    std::stringstream ss(input);
    SourceTokenizer sourceTokenizer = SourceTokenizer(&ss);
    REQUIRE_THROWS(sourceTokenizer.tokenize());
  };

  SECTION("Invalid > op") {
    std::string input = "procedure a { x >";
    std::stringstream ss(input);
    SourceTokenizer sourceTokenizer = SourceTokenizer(&ss);
    REQUIRE_THROWS(sourceTokenizer.tokenize());
  };

  SECTION("Invalid &> op") {
    std::string input = "procedure a { x &> 1; }";
    std::stringstream ss(input);
    SourceTokenizer sourceTokenizer = SourceTokenizer(&ss);
    REQUIRE_THROWS(sourceTokenizer.tokenize());
  };

  SECTION("Invalid <| op") {
    std::string input = "procedure a { x <| 1; }";
    std::stringstream ss(input);
    SourceTokenizer sourceTokenizer = SourceTokenizer(&ss);
    REQUIRE_THROWS(sourceTokenizer.tokenize());
  };

  SECTION("Invalid only |") {
    std::string input = "|";
    std::stringstream ss(input);
    SourceTokenizer sourceTokenizer = SourceTokenizer(&ss);
    REQUIRE_THROWS(sourceTokenizer.tokenize());
  };

  SECTION("Invalid [ op") {
    std::string input = "[";
    std::stringstream ss(input);
    SourceTokenizer sourceTokenizer = SourceTokenizer(&ss);
    REQUIRE_THROWS(sourceTokenizer.tokenize());
  };
}
