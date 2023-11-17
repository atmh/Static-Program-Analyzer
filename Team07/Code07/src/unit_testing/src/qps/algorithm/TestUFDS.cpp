#include "catch.hpp"
#include "qps/algorithm/UFDS.h"

TEST_CASE("UFDS") {
  QPS::UFDS ufds(10);

  SECTION("getPar") {
    for (int i = 0; i < 10; i++) {
      REQUIRE(ufds.getPar(i) == i);
    }
  }

  SECTION("Merge") {
    for (int i = 0; i < 9; i++) {
      ufds.merge(i, i + 1);
      REQUIRE(ufds.getPar(i) == ufds.getPar(i + 1));
    }
  }
}
