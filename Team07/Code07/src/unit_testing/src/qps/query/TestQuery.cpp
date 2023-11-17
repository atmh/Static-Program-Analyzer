#include <memory>
#include <utility>

#include "catch.hpp"
#include "qps/query/Query.h"
#include "qps/query/declaration/Declaration.h"
#include "qps/query/declaration/VariableDeclaration.h"
#include "qps/query/select/SelectClause.h"

TEST_CASE("Query instantiation") {
  std::unique_ptr<QPS::Declaration> declaration =
      std::make_unique<QPS::VariableDeclaration>("v");
  QPS::SelectClause sc({std::move(declaration)});
  QPS::Query q(std::move(sc));
}
