#include <list>
#include <memory>
#include <string>
#include <utility>

#include "catch.hpp"
#include "qps/query/declaration/Declaration.h"
#include "qps/query/declaration/VariableDeclaration.h"
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

class SelectClausePKBStub : public PKB::PKBStorageReadStub {
 public:
  virtual const std::string getCallProcName(
      int stmtNo) const noexcept override {
    if (stmtNo == 1) {
      return "calls";
    }
    return "";
  }

  virtual const std::string getPrintVarName(
      int stmtNo) const noexcept override {
    if (stmtNo == 1) {
      return "print";
    }
    return "";
  }

  virtual const std::string getReadVarName(int stmtNo) const noexcept override {
    if (stmtNo == 1) {
      return "read";
    }
    return "";
  }

  const std::unordered_set<int>& getReads() const noexcept override {
    return reads;
  }

  std::unordered_set<int> reads{1};
};

}  // namespace

TEST_CASE("SelectClause instantiation") {
  std::unique_ptr<QPS::Declaration> declaration =
      std::make_unique<QPS::VariableDeclaration>("v");
  QPS::SelectClause sc({std::move(declaration)});
}

TEST_CASE("Boolean select") {
  SECTION("False") {
    QPS::SelectClause sc;
    auto empty_table = QPS::EMPTY_TABLE;  // copy and drop const

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<PKB::PKBStorageReadStub>()};
    REQUIRE(std::list<std::string>{sc.select(empty_table, pkb, dataStorage)} ==
            std::list<std::string>{"FALSE"});
  }

  SECTION("True Table") {
    QPS::SelectClause sc;
    QPS::Table table;  // copy and drop const

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<PKB::PKBStorageReadStub>()};
    REQUIRE(std::list<std::string>{sc.select(table, pkb, dataStorage)} ==
            std::list<std::string>{"TRUE"});
  }

  SECTION("Non empty table") {
    QPS::SelectClause sc;
    QPS::Table table{{{"a", {1, 2, 3}}}};  // copy and drop const

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<PKB::PKBStorageReadStub>()};
    REQUIRE(std::list<std::string>{sc.select(table, pkb, dataStorage)} ==
            std::list<std::string>{"TRUE"});
  }
}

TEST_CASE("Multi projection") {
  SECTION("project a b") {
    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {1, 2, 1};
    m["b"] = {2, 2, 3};
    QPS::Table table(m);

    std::vector<std::shared_ptr<QPS::Declaration>> declarations{
        std::make_shared<QPS::StatementDeclaration>("a"),
        std::make_shared<QPS::StatementDeclaration>("b")};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage =
        std::make_shared<QPS::NormalizedDataStorage>();
    QPS::SelectClause sc{declarations};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<PKB::PKBStorageReadStub>()};
    table = sc.project(pkb, table, dataStorage);
    std::list<std::string> res = sc.select(table, pkb, dataStorage);
    REQUIRE(isSameList(res, {"1 2", "1 3", "2 2"}));
  }

  SECTION("project b a") {
    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {1, 2, 1};
    m["b"] = {2, 2, 3};
    QPS::Table table(m);

    std::vector<std::shared_ptr<QPS::Declaration>> declarations{
        std::make_shared<QPS::StatementDeclaration>("b"),
        std::make_shared<QPS::StatementDeclaration>("a")};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage =
        std::make_shared<QPS::NormalizedDataStorage>();
    QPS::SelectClause sc{declarations};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<PKB::PKBStorageReadStub>()};
    table = sc.project(pkb, table, dataStorage);
    std::list<std::string> res = sc.select(table, pkb, dataStorage);
    REQUIRE(isSameList(res, {"2 1", "2 2", "3 1"}));
  }
}

TEST_CASE("Attr ref selection") {
  SECTION("Test call") {
    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {1};
    QPS::Table table(m);
    std::vector<std::shared_ptr<QPS::Declaration>> declarations{
        std::make_shared<QPS::CallDeclaration>("a",
                                               QPS::Declaration::Type::NAME)};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage =
        std::make_shared<QPS::NormalizedDataStorage>();
    QPS::SelectClause sc{declarations};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<SelectClausePKBStub>()};
    table = sc.project(pkb, table, dataStorage);
    std::list<std::string> res = sc.select(table, pkb, dataStorage);
    REQUIRE(res == std::list<std::string>{"calls"});
  }

  SECTION("Test print") {
    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {1};
    QPS::Table table(m);
    std::vector<std::shared_ptr<QPS::Declaration>> declarations{
        std::make_shared<QPS::PrintDeclaration>("a",
                                                QPS::Declaration::Type::NAME)};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage =
        std::make_shared<QPS::NormalizedDataStorage>();
    QPS::SelectClause sc{declarations};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<SelectClausePKBStub>()};
    table = sc.project(pkb, table, dataStorage);
    std::list<std::string> res = sc.select(table, pkb, dataStorage);
    REQUIRE(isSameList(res, {"print"}));
  }

  SECTION("Test read") {
    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {1};
    QPS::Table table(m);
    std::vector<std::shared_ptr<QPS::Declaration>> declarations{
        std::make_shared<QPS::ReadDeclaration>("a",
                                               QPS::Declaration::Type::NAME)};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage =
        std::make_shared<QPS::NormalizedDataStorage>();
    QPS::SelectClause sc{declarations};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<SelectClausePKBStub>()};
    table = sc.project(pkb, table, dataStorage);
    std::list<std::string> res = sc.select(table, pkb, dataStorage);
    REQUIRE(isSameList(res, {"read"}));
  }
}

TEST_CASE("Project unrelated") {
  SECTION("Non empty table - lazy") {
    std::vector<std::shared_ptr<QPS::Declaration>> declarations{
        std::make_shared<QPS::ReadDeclaration>("b")};
    QPS::SelectClause sc{declarations};
    QPS::Table table{{{"a", {1}}}};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<SelectClausePKBStub>()};
    QPS::Table res = sc.project(pkb, table, dataStorage, false);
    REQUIRE(res.trueTable());
  }

  SECTION("Non empty table - eager") {
    std::vector<std::shared_ptr<QPS::Declaration>> declarations{
        std::make_shared<QPS::ReadDeclaration>("b")};
    QPS::SelectClause sc{declarations};
    QPS::Table table{{{"a", {1}}}};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<SelectClausePKBStub>()};
    QPS::Table res = sc.project(pkb, table, dataStorage, true);
    REQUIRE(!res.empty());
  }

  SECTION("Empty table 1 - lazy") {
    std::vector<std::shared_ptr<QPS::Declaration>> declarations{
        std::make_shared<QPS::ReadDeclaration>("b")};
    QPS::SelectClause sc{declarations};
    QPS::Table table{{{"a", {}}}};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<SelectClausePKBStub>()};
    QPS::Table res = sc.project(pkb, table, dataStorage, false);
    REQUIRE(res.empty());
  }

  SECTION("Empty table 1 - eager") {
    std::vector<std::shared_ptr<QPS::Declaration>> declarations{
        std::make_shared<QPS::ReadDeclaration>("b")};
    QPS::SelectClause sc{declarations};
    QPS::Table table{{{"a", {}}}};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<SelectClausePKBStub>()};
    QPS::Table res = sc.project(pkb, table, dataStorage, true);
    REQUIRE(res.empty());
  }

  SECTION("Empty table 2 - lazy") {
    std::vector<std::shared_ptr<QPS::Declaration>> declarations{
        std::make_shared<QPS::ReadDeclaration>("b")};
    QPS::SelectClause sc{declarations};
    QPS::Table table{QPS::EMPTY_TABLE};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<SelectClausePKBStub>()};
    QPS::Table res = sc.project(pkb, table, dataStorage, false);
    REQUIRE(res.empty());
  }

  SECTION("Empty table 2 - eager") {
    std::vector<std::shared_ptr<QPS::Declaration>> declarations{
        std::make_shared<QPS::ReadDeclaration>("b")};
    QPS::SelectClause sc{declarations};
    QPS::Table table{QPS::EMPTY_TABLE};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<SelectClausePKBStub>()};
    QPS::Table res = sc.project(pkb, table, dataStorage, true);
    REQUIRE(res.empty());
  }
}
