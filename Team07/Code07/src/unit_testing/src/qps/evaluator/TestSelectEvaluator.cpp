#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "catch.hpp"
#include "qps/query/declaration/CallDeclaration.h"
#include "qps/query/declaration/Declaration.h"
#include "qps/query/declaration/StatementDeclaration.h"
#include "qps/query/select/SelectClause.h"
#include "qps/table/Table.h"
#include "stubs/pkb/PKBStorageReadAPI.h"

namespace {

bool isSameList(const std::list<std::string>& a,
                const std::list<std::string>& b) {
  return a.size() == b.size() &&
         std::unordered_set<std::string>{a.begin(), a.end()} ==
             std::unordered_set<std::string>{b.begin(), b.end()};
}

class MultiProjTestStub : public PKB::PKBStorageReadStub {
 public:
  virtual const std::unordered_set<int>& getCalls() const noexcept override {
    return calls;
  }
  std::unordered_set<int> calls{8, 9};
};

}  // namespace

TEST_CASE("Multi projection without all columns in table") {
  std::unordered_map<std::string, std::vector<int>> m;
  m["a"] = {1, 2, 1};
  m["b"] = {2, 2, 3};
  QPS::Table table(m);
  std::vector<std::shared_ptr<QPS::Declaration>> declarations{
      std::make_shared<QPS::StatementDeclaration>("a"),
      std::make_shared<QPS::StatementDeclaration>("b"),
      std::make_shared<QPS::CallDeclaration>("c")};
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage =
      std::make_shared<QPS::NormalizedDataStorage>();
  QPS::SelectClause sc{declarations};
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<MultiProjTestStub>()};
  table = sc.project(pkb, table, dataStorage);
  std::list<std::string> res = sc.select(table, pkb, dataStorage);
  REQUIRE(isSameList(res, std::list<std::string>{"1 2 8", "1 2 9", "1 3 8",
                                                 "1 3 9", "2 2 8", "2 2 9"}));
}
