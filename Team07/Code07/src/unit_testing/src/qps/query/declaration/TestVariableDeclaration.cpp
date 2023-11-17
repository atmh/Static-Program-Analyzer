#include <memory>

#include "catch.hpp"
#include "qps/query/declaration/VariableDeclaration.h"

TEST_CASE("Variable instantiation") {
  // we should test the virtual destructor is invoked even if delete is
  // called via QPS::Declaration instead of QPS::Variable
  std::unique_ptr<QPS::Declaration> declaration =
      std::make_unique<QPS::VariableDeclaration>("v");
}
