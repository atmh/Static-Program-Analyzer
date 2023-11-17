#include <string>
#include <unordered_set>

#include "catch.hpp"
#include "qps/table/NormalizedDataStorage.h"

TEST_CASE("Normalize variables") {
  QPS::NormalizedDataStorage dataStorage;
  auto v1 = dataStorage.encodeStrings({"d", "a", "b", "c"});
  REQUIRE(v1.size() == 4);
  REQUIRE(std::unordered_set<int>{v1.begin(), v1.end()} ==
          std::unordered_set<int>{0, 1, 2, 3});

  auto v2 = dataStorage.encodeStrings({"a"});
  REQUIRE(v2.size() == 1);
  REQUIRE("a" == dataStorage.decodeString(*v2.begin()));
}

TEST_CASE("Normalize int") {
  QPS::NormalizedDataStorage dataStorage;
  auto v1 = dataStorage.encodeInt(444);
  REQUIRE(v1 == 444);
}
