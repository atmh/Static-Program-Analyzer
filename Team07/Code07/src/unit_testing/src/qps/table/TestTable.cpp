#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "catch.hpp"
#include "qps/query/QueryResult.h"
#include "qps/query/declaration/AssignDeclaration.h"
#include "qps/query/declaration/CallDeclaration.h"
#include "qps/query/declaration/ConstantDeclaration.h"
#include "qps/query/declaration/Declaration.h"
#include "qps/query/declaration/IfDeclaration.h"
#include "qps/query/declaration/PrintDeclaration.h"
#include "qps/query/declaration/ProcedureDeclaration.h"
#include "qps/query/declaration/ReadDeclaration.h"
#include "qps/query/declaration/StatementDeclaration.h"
#include "qps/query/declaration/VariableDeclaration.h"
#include "qps/query/declaration/WhileDeclaration.h"
#include "qps/query/select/SelectClause.h"
#include "qps/table/NormalizedDataStorage.h"
#include "qps/table/Table.h"
#include "stubs/pkb/PKBStorageReadAPI.h"

TEST_CASE("Table equality") {
  SECTION("test 1") {
    std::unordered_map<std::string, std::vector<int>> m1;
    std::unordered_map<std::string, std::vector<int>> m2;
    QPS::Table t1{m1};
    QPS::Table t2{m2};

    REQUIRE(t1 == t2);
    REQUIRE(!(t1 != t2));
  }

  SECTION("test 2") {
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {1, 2, 3};
    std::unordered_map<std::string, std::vector<int>> m2;
    QPS::Table t1{m1};
    QPS::Table t2{m2};
    REQUIRE(t1 != t2);
  }

  SECTION("test 3") {
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {1, 2, 3};
    std::unordered_map<std::string, std::vector<int>> m2;
    m2["a"] = {1, 2};
    QPS::Table t1{m1};
    QPS::Table t2{m2};
    REQUIRE(t1 != t2);
  }

  SECTION("test 4") {
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {1, 2, 3};
    std::unordered_map<std::string, std::vector<int>> m2;
    m2["a"] = {1, 2};
    m2["a"].push_back(3);
    QPS::Table t1{m1};
    QPS::Table t2{m2};
    REQUIRE(t1 == t2);
  }

  SECTION("Semantics test 1") {
    // order should not matter
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {1, 2, 3};
    std::unordered_map<std::string, std::vector<int>> m2;
    m2["a"] = {3, 1, 2};
    QPS::Table t1{m1};
    QPS::Table t2{m2};
    REQUIRE(t1 == t2);
  }

  SECTION("Semantics test 2") {
    // order should not matter
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {1, 2, 3};
    m1["b"] = {4, 5, 6};
    std::unordered_map<std::string, std::vector<int>> m2;
    m2["a"] = {3, 1, 2};
    m2["b"] = {6, 4, 5};
    QPS::Table t1{m1};
    QPS::Table t2{m2};
    REQUIRE(t1 == t2);
  }

  SECTION("Semantics test 3") {
    // order should not matter
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {1, 2, 3};
    m1["b"] = {4, 5, 6};
    std::unordered_map<std::string, std::vector<int>> m2;
    m2["a"] = {3, 1, 2};
    m2["b"] = {4, 5, 6};
    QPS::Table t1{m1};
    QPS::Table t2{m2};
    REQUIRE(t1 != t2);
  }
}

TEST_CASE("Table operator<<") {
  SECTION("Empty Table") {
    std::unordered_map<std::string, std::vector<int>> m;
    QPS::Table table{m};

    std::ostringstream ss;
    ss << table;
    REQUIRE(ss.str() == "True Table");
  }

  SECTION("Test 1") {
    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {1, 2, 3};
    m["b"] = {4, 5, 6};

    QPS::Table table{m};

    std::ostringstream ss;
    ss << table;
    REQUIRE(ss.str() ==
            "|    a|    b|\n"
            "-------------\n"
            "|    1|    4|\n"
            "|    2|    5|\n"
            "|    3|    6|\n");
  }
}

TEST_CASE("Table join") {
  SECTION("No Common Synonym 1") {
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {1, 2};
    m1["b"] = {1, 2};

    std::unordered_map<std::string, std::vector<int>> m2;
    m2["c"] = {2, 3};
    m2["d"] = {2, 4};

    std::unordered_map<std::string, std::vector<int>> expected_result;
    expected_result["a"] = {1, 1, 2, 2};
    expected_result["b"] = {1, 1, 2, 2};
    expected_result["c"] = {2, 3, 2, 3};
    expected_result["d"] = {2, 4, 2, 4};

    QPS::Table t1{m1};
    QPS::Table t2{m2};
    QPS::Table expected_table{expected_result};

    t1 = t1 * t2;

    REQUIRE(t1 == expected_table);
  }

  SECTION("No Common Synonym 2") {
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {1, 2};
    m1["c"] = {1, 2};

    std::unordered_map<std::string, std::vector<int>> m2;
    m2["b"] = {2, 3};
    m2["d"] = {2, 4};

    std::unordered_map<std::string, std::vector<int>> expected_result;
    expected_result["a"] = {1, 1, 2, 2};
    expected_result["c"] = {1, 1, 2, 2};
    expected_result["b"] = {2, 3, 2, 3};
    expected_result["d"] = {2, 4, 2, 4};

    QPS::Table t1{m1};
    QPS::Table t2{m2};
    QPS::Table expected_table{expected_result};

    t1 = t1 * t2;

    REQUIRE(t1 == expected_table);
  }

  SECTION("No Common Synonym 3") {
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {1, 2};
    m1["c"] = {1, 2};

    std::unordered_map<std::string, std::vector<int>> m2;
    m2["b"] = {};
    m2["d"] = {};

    std::unordered_map<std::string, std::vector<int>> expected_result;
    expected_result["a"] = {};
    expected_result["c"] = {};
    expected_result["b"] = {};
    expected_result["d"] = {};

    QPS::Table t1{m1};
    QPS::Table t2{m2};
    QPS::Table expected_table{expected_result};

    t1 = t1 * t2;

    REQUIRE(t1 == expected_table);
  }

  SECTION("Common Synonym - 1") {
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {1, 2, 1};
    m1["b"] = {2, 2, 3};

    std::unordered_map<std::string, std::vector<int>> m2;
    m2["b"] = {2, 2, 3};
    m2["c"] = {3, 4, 4};

    std::unordered_map<std::string, std::vector<int>> expected_result;
    expected_result["a"] = {1, 1, 2, 2, 1};
    expected_result["b"] = {2, 2, 2, 2, 3};
    expected_result["c"] = {3, 4, 3, 4, 4};

    QPS::Table t1{m1};
    QPS::Table t2{m2};
    QPS::Table expected_table{expected_result};

    t1 = t1 * t2;

    REQUIRE(t1 == expected_table);
  }

  SECTION("Common Synonym - 2") {
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {1, 2, 1};
    m1["b"] = {2, 2, 3};
    m1["d"] = {9, 9, 9};

    QPS::Table t2{
        std::vector<std::string>{"b", "c", "d"},
        std::unordered_map<std::string, int>{{"b", 0}, {"c", 1}, {"d", 2}},
        std::vector<std::vector<int>>{{2, 3, 9}, {2, 4, 9}, {3, 4, 9}}};

    std::unordered_map<std::string, std::vector<int>> expected_result;
    expected_result["a"] = {1, 1, 2, 2, 1};
    expected_result["b"] = {2, 2, 2, 2, 3};
    expected_result["c"] = {3, 4, 3, 4, 4};
    expected_result["d"] = {9, 9, 9, 9, 9};

    QPS::Table t1{m1};
    QPS::Table expected_table{expected_result};

    t1 = t1 * t2;

    REQUIRE(t1 == expected_table);
  }

  SECTION("Common Synonym - 3") {
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {1, 2, 1};
    m1["b"] = {2, 2, 3};
    m1["d"] = {9, 9, 9};

    QPS::Table t2{
        std::vector<std::string>{"d", "b", "c"},
        std::unordered_map<std::string, int>{{"d", 0}, {"b", 1}, {"c", 2}},
        std::vector<std::vector<int>>{{9, 2, 3}, {9, 2, 4}, {9, 3, 4}}};

    std::unordered_map<std::string, std::vector<int>> expected_result;
    expected_result["a"] = {1, 1, 2, 2, 1};
    expected_result["b"] = {2, 2, 2, 2, 3};
    expected_result["c"] = {3, 4, 3, 4, 4};
    expected_result["d"] = {9, 9, 9, 9, 9};

    QPS::Table t1{m1};
    QPS::Table expected_table{expected_result};

    t1 = t1 * t2;

    REQUIRE(t1 == expected_table);
  }

  SECTION("Common Synonym - 4") {
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {1, 2};
    m1["b"] = {1, 2};

    std::unordered_map<std::string, std::vector<int>> m2;
    m2["b"] = {};
    m2["d"] = {};

    std::unordered_map<std::string, std::vector<int>> expected_result;
    expected_result["a"] = {};
    expected_result["b"] = {};
    expected_result["d"] = {};

    QPS::Table t1{m1};
    QPS::Table t2{m2};
    QPS::Table expected_table{expected_result};

    t1 = t1 * t2;

    REQUIRE(t1 == expected_table);
  }

  SECTION("Multi Common Synonym - 1") {
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {1, 1, 2, 2};
    m1["b"] = {1, 1, 1, 2};
    m1["c"] = {2, 3, 2, 4};

    std::unordered_map<std::string, std::vector<int>> m2;
    m2["d"] = {5, 6, 3, 4};
    m2["c"] = {4, 2, 3, 2};
    m2["b"] = {2, 4, 3, 1};

    std::unordered_map<std::string, std::vector<int>> expected_result;
    expected_result["a"] = {1, 2, 2};
    expected_result["b"] = {1, 1, 2};
    expected_result["c"] = {2, 2, 4};
    expected_result["d"] = {4, 4, 5};

    QPS::Table t1{m1};
    QPS::Table t2{m2};
    QPS::Table expected_table{expected_result};

    t1 = t1 * t2;

    REQUIRE(t1 == expected_table);
  }

  SECTION("Empty join - 1") {
    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {1, 2, 1};
    m["b"] = {2, 2, 3};

    std::unordered_map<std::string, std::vector<int>> expected_result;
    expected_result["a"] = {2, 1, 1};
    expected_result["b"] = {2, 2, 3};

    QPS::Table t1{m};
    QPS::Table t2{};
    QPS::Table expected_table{expected_result};

    t1 = t1 * t2;

    REQUIRE(t1 == expected_table);
  }

  SECTION("Empty join - 2") {
    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {1, 2, 1};
    m["b"] = {2, 2, 3};

    std::unordered_map<std::string, std::vector<int>> expected_result;
    expected_result["a"] = {2, 1, 1};
    expected_result["b"] = {2, 2, 3};

    QPS::Table t1{};
    QPS::Table t2{m};
    QPS::Table expected_table{expected_result};

    t1 = t1 * t2;

    REQUIRE(t1 == expected_table);
  }

  SECTION("No result join - 1") {
    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {1, 2, 1};
    m["b"] = {2, 2, 3};
    m["d"] = {9, 9, 9};

    QPS::Table t1{m};
    QPS::Table t2{
        std::vector<std::string>{"b", "c", "d"},
        std::unordered_map<std::string, int>{{"b", 0}, {"c", 1}, {"d", 2}},
        std::vector<std::vector<int>>{}};
    QPS::Table expected_table{std::vector<std::string>{"b", "c", "d", "a"},
                              std::unordered_map<std::string, int>{
                                  {"b", 0}, {"c", 1}, {"d", 2}, {"a", 3}},
                              std::vector<std::vector<int>>{}};

    t1 = t1 * t2;

    REQUIRE(t1 == expected_table);
    REQUIRE(t1 != QPS::Table{});
  }

  SECTION("No result join - 2") {
    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {1, 2, 1};
    m["b"] = {2, 2, 3};
    m["d"] = {9, 9, 9};

    QPS::Table t1{
        std::vector<std::string>{"b", "c", "d"},
        std::unordered_map<std::string, int>{{"b", 0}, {"c", 1}, {"d", 2}},
        std::vector<std::vector<int>>{}};
    QPS::Table t2{m};
    QPS::Table expected_table{std::vector<std::string>{"b", "c", "d", "a"},
                              std::unordered_map<std::string, int>{
                                  {"b", 0}, {"c", 1}, {"d", 2}, {"a", 3}},
                              std::vector<std::vector<int>>{}};

    t1 = t1 * t2;

    REQUIRE(t1 == expected_table);
    REQUIRE(t1 != QPS::Table{});
  }

  SECTION("No result join - 3") {
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {1, 2, 1};
    m1["b"] = {2, 2, 3};
    m1["d"] = {9, 9, 9};

    std::unordered_map<std::string, std::vector<int>> m2;
    m2["a"] = {4};

    std::unordered_map<std::string, std::vector<int>> expected_result;
    expected_result["a"] = {};
    expected_result["b"] = {};
    expected_result["d"] = {};

    QPS::Table t1{m1};
    QPS::Table t2{m2};
    QPS::Table expected_table{expected_result};

    t1 = t1 * t2;

    REQUIRE(t1 == expected_table);
    REQUIRE(t1 != QPS::Table{});
  }

  SECTION("Filter join - 1")  // columns are subset of each other
  {
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {1, 2, 1};
    m1["b"] = {2, 2, 3};
    m1["d"] = {9, 9, 9};

    std::unordered_map<std::string, std::vector<int>> m2;
    m2["a"] = {1};

    std::unordered_map<std::string, std::vector<int>> expected_result;
    expected_result["a"] = {1, 1};
    expected_result["b"] = {2, 3};
    expected_result["d"] = {9, 9};

    QPS::Table t1{m1};
    QPS::Table t2{m2};
    QPS::Table expected_table{expected_result};

    t1 = t1 * t2;

    REQUIRE(t1 == expected_table);
  }

  SECTION("Filter join - 2")  // columns are subset of each other
  {
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {1, 2, 1};
    m1["b"] = {2, 2, 3};
    m1["d"] = {9, 9, 9};

    std::unordered_map<std::string, std::vector<int>> m2;
    m2["a"] = {2};

    std::unordered_map<std::string, std::vector<int>> expected_result;
    expected_result["a"] = {2};
    expected_result["b"] = {2};
    expected_result["d"] = {9};

    QPS::Table t1{m1};
    QPS::Table t2{m2};
    QPS::Table expected_table{expected_result};

    t1 = t1 * t2;

    REQUIRE(t1 == expected_table);
  }

  SECTION("Filter join - 3")  // columns are subset of each other
  {
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {2};

    std::unordered_map<std::string, std::vector<int>> m2;
    m2["a"] = {1, 2, 1};
    m2["b"] = {2, 2, 3};
    m2["d"] = {9, 9, 9};

    std::unordered_map<std::string, std::vector<int>> expected_result;
    expected_result["a"] = {2};
    expected_result["b"] = {2};
    expected_result["d"] = {9};

    QPS::Table t1{m1};
    QPS::Table t2{m2};
    QPS::Table expected_table{expected_result};

    t1 = t1 * t2;

    REQUIRE(t1 == expected_table);

    t1 = t1 * t2;

    REQUIRE(t1 == expected_table);
  }

  SECTION("Self join") {
    std::unordered_map<std::string, std::vector<int>> m;
    m["a"] = {1, 2, 1};
    m["b"] = {2, 2, 3};
    m["d"] = {9, 9, 9};

    QPS::Table t1{m};
    QPS::Table t2{m};
    QPS::Table expected{m};

    t1 = t1 * t1;

    // here t1 == t2 == expected so any number of joins should result in same
    REQUIRE(t1 == expected);
    t1 = t1 * t2;
    REQUIRE(t1 == expected);
    t1 = t1 * t1;
    REQUIRE(t1 == expected);
    t1 = t1 * t2;
    REQUIRE(t1 == expected);
  }
}

TEST_CASE("dedup") {
  std::unordered_map<std::string, std::vector<int>> m;
  m["a"] = {1, 2, 1};
  m["b"] = {2, 2, 3};
  QPS::Table table(m);

  std::shared_ptr<QPS::Declaration> declaration =
      std::make_shared<QPS::StatementDeclaration>("a");
  std::shared_ptr<QPS::NormalizedDataStorage> dataStorage =
      std::make_shared<QPS::NormalizedDataStorage>();
  QPS::SelectClause sc({declaration});
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
      std::make_shared<PKB::PKBStorageReadStub>()};
  table = sc.project(pkb, table, dataStorage);
  std::list<std::string> res = sc.select(table, pkb, dataStorage);
  REQUIRE(res.size() == 2);
}

TEST_CASE("Test difference") {
  SECTION("Test 1") {
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {1, 1};
    m1["b"] = {1, 2};
    QPS::Table table1(m1);
    std::unordered_map<std::string, std::vector<int>> m2;
    m2["a"] = {1};
    m2["b"] = {1};
    QPS::Table table2(m2);
    std::unordered_map<std::string, std::vector<int>> m3;
    m3["a"] = {1};
    m3["b"] = {2};
    QPS::Table table3(m3);

    REQUIRE(table1 - table2 == table3);
  }

  SECTION("Test 2") {
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {1};
    m1["b"] = {1};
    QPS::Table table1(m1);

    REQUIRE(QPS::EMPTY_TABLE - table1 == QPS::EMPTY_TABLE);
  }

  SECTION("Test 3") {
    std::unordered_map<std::string, std::vector<int>> m1;
    QPS::Table table1;

    REQUIRE(QPS::EMPTY_TABLE - table1 == QPS::EMPTY_TABLE);
  }

  SECTION("Test 4") {
    std::unordered_map<std::string, std::vector<int>> m1;
    m1["a"] = {1, 1};
    m1["b"] = {1, 2};
    QPS::Table table1(m1);

    REQUIRE(QPS::EMPTY_TABLE - table1 == QPS::EMPTY_TABLE);
  }
}
