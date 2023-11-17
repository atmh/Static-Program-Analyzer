#include <memory>
#include <string>
#include <vector>

#include "catch.hpp"
#include "qps/QPS.h"
#include "stubs/pkb/PKBStorageReadAPI.h"

TEST_CASE("QPS process valid query") {
  std::vector<std::string> variables{};
  QPS::QPS qps{std::make_shared<PKB::PKBStorageReadStub>()};
  auto res = qps.process("variable v; Select v");
  REQUIRE(res.empty());
}

TEST_CASE("QPS process invalid query - 1") {
  std::vector<std::string> variables{};
  QPS::QPS qps{std::make_shared<PKB::PKBStorageReadStub>()};
  auto res = qps.process("variable v;");
  REQUIRE((res.size() == 1 && res.front() == "SyntaxError"));
}

TEST_CASE("QPS process invalid query - 2") {
  std::vector<std::string> variables{};
  QPS::QPS qps{std::make_shared<PKB::PKBStorageReadStub>()};
  auto res = qps.process("variable v; Select c");
  REQUIRE((res.size() == 1 && res.front() == "SemanticError"));
}