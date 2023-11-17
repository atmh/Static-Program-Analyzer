#include <filesystem>
#include <iostream>

#include "catch.hpp"
#include "sp/SPManager.h"
#include "sp/exception/SemanticException.h"
#include "stubs/pkb/PKBStorageWriteAPI.h"

TEST_CASE("Valid SP Manager process") {
  SECTION("Basic SIMPLE Program") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure test1 {\n"
        "    x = 10;\n"
        "    print x;\n"
        "}";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    // Relationship
    std::unordered_map<int, int> expectedFollows{{1, 2}};
    std::unordered_map<int, std::unordered_set<int>> expectedParent{};
    std::unordered_map<int, std::unordered_set<std::string>>
        expectedModifiesStatement{{1, {"x"}}};
    std::unordered_map<int, std::unordered_set<std::string>> expectedUses{
        {2, {"x"}}};
    std::unordered_map<int, std::unordered_set<int>> expectedNext{{1, {2}}};

    // Entity
    std::unordered_set<std::string> expectedVars{"x"};
    std::unordered_set<std::string> expectedConsts{"10"};
    std::unordered_set<std::string> expectedProcs{"test1"};
    std::unordered_set<int> expectedReads{};
    std::unordered_set<int> expectedPrints{2};
    std::unordered_set<int> expectedCalls{};
    std::unordered_set<int> expectedWhiles{};
    std::unordered_set<int> expectedAssigns{1};
    std::unordered_set<int> expectedIfs{};

    // Pattern
    std::unordered_map<std::string, std::unordered_set<int>>
        expectedIfPattern{};
    std::unordered_map<std::string, std::unordered_set<int>>
        expectedWhilePattern{};

    spManager.process(testFileName);

    // Relationship assertions
    REQUIRE(expectedFollows == pkbStub->followsStorage);
    REQUIRE(expectedParent == pkbStub->parentStorage);
    REQUIRE(expectedModifiesStatement == pkbStub->modifiesStatementStorage);
    REQUIRE(expectedUses == pkbStub->usesStatementStorage);
    REQUIRE(expectedNext == pkbStub->nextStorage);

    // Entity assertions
    REQUIRE(expectedProcs == pkbStub->procedureStorage);
    REQUIRE(expectedVars == pkbStub->variableStorage);
    REQUIRE(expectedConsts == pkbStub->constantStorage);
    REQUIRE(expectedReads == pkbStub->readStorage);
    REQUIRE(expectedPrints == pkbStub->printStorage);
    REQUIRE(expectedCalls == pkbStub->callStorage);
    REQUIRE(expectedWhiles == pkbStub->whileStorage);
    REQUIRE(expectedAssigns == pkbStub->assignStorage);
    REQUIRE(expectedIfs == pkbStub->ifStorage);

    // Pattern assertions
    REQUIRE(expectedIfPattern == pkbStub->ifPatternStorage);
    REQUIRE(expectedWhilePattern == pkbStub->whilePatternStorage);

    std::filesystem::remove(testFileName);
  }

  SECTION(
      "Basic SIMPLE Program with multiple assignment and print statements") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure test1 {\n"
        "  x = 30;\n"
        "  x = x + 1;\n"
        "  print x;\n"
        "  x = x + 20;\n"
        "  print x;\n"
        "}";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    // Relationship
    std::unordered_map<int, int> expectedFollows{
        {1, 2}, {2, 3}, {3, 4}, {4, 5}};
    std::unordered_map<int, std::unordered_set<int>> expectedParent{};
    std::unordered_map<int, std::unordered_set<std::string>>
        expectedModifiesStatement{{1, {"x"}}, {2, {"x"}}, {4, {"x"}}};
    std::unordered_map<int, std::unordered_set<std::string>> expectedUses{
        {2, {"x"}}, {3, {"x"}}, {4, {"x"}}, {5, {"x"}}};
    std::unordered_map<int, std::unordered_set<int>> expectedNext{
        {1, {2}}, {2, {3}}, {3, {4}}, {4, {5}}};

    // Entity
    std::unordered_set<std::string> expectedVars{"x"};
    std::unordered_set<std::string> expectedConsts{"1", "30", "20"};
    std::unordered_set<std::string> expectedProcs{"test1"};
    std::unordered_set<int> expectedReads{};
    std::unordered_set<int> expectedPrints{3, 5};
    std::unordered_set<int> expectedCalls{};
    std::unordered_set<int> expectedWhiles{};
    std::unordered_set<int> expectedAssigns{1, 2, 4};
    std::unordered_set<int> expectedIfs{};

    // Pattern
    std::unordered_map<std::string, std::unordered_set<int>>
        expectedIfPattern{};
    std::unordered_map<std::string, std::unordered_set<int>>
        expectedWhilePattern{};

    spManager.process(testFileName);

    // Relationship assertions
    REQUIRE(expectedFollows == pkbStub->followsStorage);
    REQUIRE(expectedParent == pkbStub->parentStorage);
    REQUIRE(expectedModifiesStatement == pkbStub->modifiesStatementStorage);
    REQUIRE(expectedUses == pkbStub->usesStatementStorage);
    REQUIRE(expectedNext == pkbStub->nextStorage);

    // Entity assertions
    REQUIRE(expectedProcs == pkbStub->procedureStorage);
    REQUIRE(expectedVars == pkbStub->variableStorage);
    REQUIRE(expectedConsts == pkbStub->constantStorage);
    REQUIRE(expectedReads == pkbStub->readStorage);
    REQUIRE(expectedPrints == pkbStub->printStorage);
    REQUIRE(expectedCalls == pkbStub->callStorage);
    REQUIRE(expectedWhiles == pkbStub->whileStorage);
    REQUIRE(expectedAssigns == pkbStub->assignStorage);
    REQUIRE(expectedIfs == pkbStub->ifStorage);

    // Pattern assertions
    REQUIRE(expectedIfPattern == pkbStub->ifPatternStorage);
    REQUIRE(expectedWhilePattern == pkbStub->whilePatternStorage);

    std::filesystem::remove(testFileName);
  }

  SECTION("While loop with multiple statements") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure test1 {\n"
        "    x = 10;\n"
        "    print x;\n"
        "    read z;\n"
        "    y = 1000;\n"
        "    while (x < y) {\n"
        "        x = x + 1 * 3 * 4 % 10 + z; \n"
        "        y = x + 1; \n"
        "    } \n"
        "    print y; \n"
        "}";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    // Relationship
    std::unordered_map<int, int> expectedFollows{{1, 2}, {2, 3}, {3, 4},
                                                 {4, 5}, {6, 7}, {5, 8}};
    std::unordered_map<int, std::unordered_set<int>> expectedParent{
        {5, {6, 7}}};
    std::unordered_map<int, std::unordered_set<std::string>> expectedModifies{
        {1, {"x"}},      {3, {"z"}}, {4, {"y"}},
        {5, {"x", "y"}}, {6, {"x"}}, {7, {"y"}}};
    std::unordered_map<int, std::unordered_set<std::string>> expectedUses{
        {2, {"x"}},
        {5, {"x", "y", "z"}},
        {6, {"x", "z"}},
        {7, {"x"}},
        {8, {"y"}}};
    std::unordered_map<int, std::unordered_set<int>> expectedNext{
        {1, {2}},    {2, {3}}, {3, {4}}, {4, {5}},
        {5, {6, 8}}, {6, {7}}, {7, {5}}};

    // Entity
    std::unordered_set<std::string> expectedVars{"x", "y", "z"};
    std::unordered_set<std::string> expectedConsts{"10", "1000", "1",
                                                   "3",  "4",    "10"};
    std::unordered_set<std::string> expectedProcs{"test1"};
    std::unordered_set<int> expectedReads{3};
    std::unordered_set<int> expectedPrints{2, 8};
    std::unordered_set<int> expectedCalls{};
    std::unordered_set<int> expectedWhiles{5};
    std::unordered_set<int> expectedAssigns{1, 4, 6, 7};
    std::unordered_set<int> expectedIfs{};

    // Pattern
    std::unordered_map<std::string, std::unordered_set<int>>
        expectedIfPattern{};
    std::unordered_map<std::string, std::unordered_set<int>>
        expectedWhilePattern{{"x", {5}}, {"y", {5}}};

    spManager.process(testFileName);

    // Relationship assertions
    REQUIRE(expectedFollows == pkbStub->followsStorage);
    REQUIRE(expectedParent == pkbStub->parentStorage);
    REQUIRE(expectedModifies == pkbStub->modifiesStatementStorage);
    REQUIRE(expectedUses == pkbStub->usesStatementStorage);

    // Entity assertions
    REQUIRE(expectedProcs == pkbStub->procedureStorage);
    REQUIRE(expectedVars == pkbStub->variableStorage);
    REQUIRE(expectedConsts == pkbStub->constantStorage);
    REQUIRE(expectedReads == pkbStub->readStorage);
    REQUIRE(expectedPrints == pkbStub->printStorage);
    REQUIRE(expectedCalls == pkbStub->callStorage);
    REQUIRE(expectedWhiles == pkbStub->whileStorage);
    REQUIRE(expectedAssigns == pkbStub->assignStorage);
    REQUIRE(expectedIfs == pkbStub->ifStorage);
    REQUIRE(expectedNext == pkbStub->nextStorage);

    // Pattern assertions
    REQUIRE(expectedIfPattern == pkbStub->ifPatternStorage);
    REQUIRE(expectedWhilePattern == pkbStub->whilePatternStorage);

    std::filesystem::remove(testFileName);
  }

  SECTION("Nested while loop") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure test1 {\n"
        "    while = 8;"                                          // 1
        "    while (while <= 10) {\n"                             // 2
        "     while = (while + 5 * 300);\n"                       // 3
        "     while ((while + 20) != (while * 10 - 20 + 0)) {\n"  // 4
        "        while = while - 5;\n"                            // 5
        "        read while;\n"                                   // 6
        "        call test2;\n"                                   // 7
        "        print while;\n"                                  // 8
        "     }\n"
        "    }\n"
        "}\n"
        "procedure test2 {\n"
        "    x = 10;\n"                                               // 9
        "    print x;\n"                                              // 10
        "    read z;\n"                                               // 11
        "    y = 1000;\n"                                             // 12
        "    while ((x + 234) < (y + 100000000000000000000000)) {\n"  // 13
        "        x = x + 1 * 3 * 4 % 10; \n"                          // 14
        "        y = x + 1; \n"                                       // 15
        "    } \n"
        "    print y; \n"  // 16
        "}";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    // Relationship
    std::unordered_map<int, int> expectedFollows{
        {1, 2},   {3, 4},   {5, 6},   {6, 7},   {7, 8},  {9, 10},
        {10, 11}, {11, 12}, {12, 13}, {14, 15}, {13, 16}};
    std::unordered_map<int, std::unordered_set<int>> expectedParent{
        {2, {3, 4}}, {4, {5, 6, 7, 8}}, {13, {14, 15}}};
    std::unordered_map<int, std::unordered_set<std::string>>
        expectedModifiesStatement{
            {1, {"while"}},       {2, {"while", "x", "z", "y"}},
            {3, {"while"}},       {4, {"while", "x", "z", "y"}},
            {5, {"while"}},       {6, {"while"}},
            {7, {"x", "y", "z"}}, {9, {"x"}},
            {11, {"z"}},          {12, {"y"}},
            {13, {"x", "y"}},     {14, {"x"}},
            {15, {"y"}}};
    std::unordered_map<int, std::unordered_set<std::string>> expectedUses{
        {2, {"while", "x", "y"}},
        {3, {"while"}},
        {4, {"while", "x", "y"}},
        {5, {"while"}},
        {7, {"x", "y"}},
        {8, {"while"}},
        {10, {"x"}},
        {13, {"x", "y"}},
        {14, {"x"}},
        {15, {"x"}},
        {16, {"y"}},
    };
    std::unordered_map<int, std::unordered_set<int>> expectedNext{
        {1, {2}},   {2, {3}},   {3, {4}},       {4, {5, 2}}, {5, {6}},
        {6, {7}},   {7, {8}},   {8, {4}},       {9, {10}},   {10, {11}},
        {11, {12}}, {12, {13}}, {13, {14, 16}}, {14, {15}},  {15, {13}}};

    // Entity
    std::unordered_set<std::string> expectedVars{"while", "x", "z", "y"};
    std::unordered_set<std::string> expectedConsts{
        "8",    "10",  "5",
        "300",  "20",  "0",
        "1000", "234", "100000000000000000000000",
        "1",    "3",   "4"};
    std::unordered_set<std::string> expectedProcs{"test1", "test2"};
    std::unordered_set<int> expectedReads{6, 11};
    std::unordered_set<int> expectedPrints{8, 10, 16};
    std::unordered_set<int> expectedCalls{7};
    std::unordered_set<int> expectedWhiles{2, 4, 13};
    std::unordered_set<int> expectedAssigns{1, 3, 5, 9, 12, 14, 15};
    std::unordered_set<int> expectedIfs{};

    // Pattern
    std::unordered_map<std::string, std::unordered_set<int>>
        expectedIfPattern{};
    std::unordered_map<std::string, std::unordered_set<int>>
        expectedWhilePattern{{"while", {2, 4}}, {"x", {13}}, {"y", {13}}};

    spManager.process(testFileName);

    // Relationship assertions
    REQUIRE(expectedFollows == pkbStub->followsStorage);
    REQUIRE(expectedParent == pkbStub->parentStorage);
    REQUIRE(expectedModifiesStatement == pkbStub->modifiesStatementStorage);
    REQUIRE(expectedUses == pkbStub->usesStatementStorage);

    // Entity assertions
    REQUIRE(expectedProcs == pkbStub->procedureStorage);
    REQUIRE(expectedVars == pkbStub->variableStorage);
    REQUIRE(expectedConsts == pkbStub->constantStorage);
    REQUIRE(expectedReads == pkbStub->readStorage);
    REQUIRE(expectedPrints == pkbStub->printStorage);
    REQUIRE(expectedCalls == pkbStub->callStorage);
    REQUIRE(expectedWhiles == pkbStub->whileStorage);
    REQUIRE(expectedAssigns == pkbStub->assignStorage);
    REQUIRE(expectedIfs == pkbStub->ifStorage);
    REQUIRE(expectedNext == pkbStub->nextStorage);

    // Pattern assertions
    REQUIRE(expectedIfPattern == pkbStub->ifPatternStorage);
    REQUIRE(expectedWhilePattern == pkbStub->whilePatternStorage);

    std::filesystem::remove(testFileName);
  }

  SECTION("Multiple Nesting") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure main { \n"
        "    x = 5; \n"                  // 1
        "    y = 0; \n"                  // 2
        "    z = 10; \n"                 // 3
        "    while (x > 0) { \n"         // 4
        "        if (x == 3) then { \n"  // 5
        "            print x; \n"        // 6
        "        } else { \n"
        "            read x; \n"  // 7
        "        } \n"
        "        while (y < 5) { \n"                   // 8
        "          if ((z + a) == (3 - b)) then { \n"  // 9
        "              print d; \n"                    // 10
        "          } else { \n"
        "              read l; \n"  // 11
        "          } \n"
        "        } \n"
        "        x = x - 1;\n"  // 12
        "    }\n"
        "}";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    // Relationship
    std::unordered_map<int, int> expectedFollows{
        {1, 2}, {2, 3}, {3, 4}, {5, 8}, {8, 12}};
    std::unordered_map<int, std::unordered_set<int>> expectedParent{
        {4, {5, 8, 12}}, {5, {6, 7}}, {8, {9}}, {9, {10, 11}}};
    std::unordered_map<int, std::unordered_set<std::string>>
        expectedModifiesStatement{{1, {"x"}},      {2, {"y"}}, {3, {"z"}},
                                  {4, {"x", "l"}}, {5, {"x"}}, {7, {"x"}},
                                  {8, {"l"}},      {8, {"l"}}, {9, {"l"}},
                                  {11, {"l"}},     {12, {"x"}}};

    std::unordered_map<int, std::unordered_set<std::string>> expectedUses{
        {4, {"x", "y", "z", "a", "b", "d"}},
        {5, {"x"}},
        {6, {"x"}},
        {8, {"y", "z", "a", "b", "d"}},
        {9, {"z", "a", "b", "d"}},
        {10, {"d"}},
        {12, {"x"}},
    };

    std::unordered_map<int, std::unordered_set<int>> expectedNext{
        {1, {2}},      {2, {3}},  {3, {4}},  {4, {5}},
        {5, {6, 7}},   {6, {8}},  {7, {8}},  {8, {9, 12}},
        {9, {10, 11}}, {10, {8}}, {11, {8}}, {12, {4}}};

    // Entity
    std::unordered_set<std::string> expectedProcs{"main"};
    std::unordered_set<std::string> expectedVars{"x", "y", "z", "a",
                                                 "b", "d", "l"};
    std::unordered_set<std::string> expectedConsts{"5", "0", "10", "3", "1"};
    std::unordered_set<int> expectedReads{7, 11};
    std::unordered_set<int> expectedPrints{6, 10};
    std::unordered_set<int> expectedCalls{};
    std::unordered_set<int> expectedWhiles{4, 8};
    std::unordered_set<int> expectedAssigns{1, 2, 3, 12};
    std::unordered_set<int> expectedIfs{5, 9};

    // Pattern
    std::unordered_map<std::string, std::unordered_set<int>> expectedIfPattern{
        {"x", {5}}, {"z", {9}}, {"a", {9}}, {"b", {9}}};
    std::unordered_map<std::string, std::unordered_set<int>>
        expectedWhilePattern{{"x", {4}}, {"y", {8}}};

    spManager.process(testFileName);

    // Relationship assertions
    REQUIRE(expectedFollows == pkbStub->followsStorage);
    REQUIRE(expectedParent == pkbStub->parentStorage);
    REQUIRE(expectedModifiesStatement == pkbStub->modifiesStatementStorage);

    REQUIRE(expectedUses == pkbStub->usesStatementStorage);

    // Entity assertions
    REQUIRE(expectedProcs == pkbStub->procedureStorage);
    REQUIRE(expectedVars == pkbStub->variableStorage);
    REQUIRE(expectedConsts == pkbStub->constantStorage);
    REQUIRE(expectedReads == pkbStub->readStorage);
    REQUIRE(expectedPrints == pkbStub->printStorage);
    REQUIRE(expectedCalls == pkbStub->callStorage);
    REQUIRE(expectedWhiles == pkbStub->whileStorage);
    REQUIRE(expectedAssigns == pkbStub->assignStorage);
    REQUIRE(expectedIfs == pkbStub->ifStorage);
    REQUIRE(expectedNext == pkbStub->nextStorage);

    // Pattern assertions
    REQUIRE(expectedIfPattern == pkbStub->ifPatternStorage);
    REQUIRE(expectedWhilePattern == pkbStub->whilePatternStorage);

    std::filesystem::remove(testFileName);
  }

  SECTION("Multiple Nesting with complex keywords") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure main { \n"
        "    while = 1; \n"  // 1
        "    if = 2; \n"     // 2
        "    read = 3; \n"   // 3
        "    call = 4; \n"   // 4
        "    print = 5; \n"  // 5
        "    while ( \n"     // 6
        "    (!( (if + then) * else / \n "
        "    (while-read) % call < print + 2) ) \n"
        "    && (( a - b != 4 + 10) \n"
        "    || (!(c/d >= 100000 + 0 ))) \n"
        "    ) { \n"
        "        if ( \n"  // 7
        "        !(  (if < then) || ((else == while) \n"
        "        && (read != call))  ) \n"
        "        ) then { \n"
        "            print x; \n"  // 8
        "        } else { \n"
        "            read x; \n"  // 9
        "        } \n"
        "        while (main < 5) { \n"        // 10
        "          if (print == 1) then { \n"  // 11
        "              print d; \n"            // 12
        "          } else { \n"
        "              read l; \n"  // 13
        "          } \n"
        "        } \n"
        "        x = x - 1;\n"  // 14
        "    }\n"
        "}";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    // Relationship
    std::unordered_map<int, int> expectedFollows{
        {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {7, 10}, {10, 14}};
    std::unordered_map<int, std::unordered_set<int>> expectedParent{
        {6, {7, 10, 14}}, {7, {8, 9}}, {10, {11}}, {11, {12, 13}}};
    std::unordered_map<int, std::unordered_set<std::string>>
        expectedModifiesStatement{
            {1, {"while"}}, {2, {"if"}},     {3, {"read"}}, {4, {"call"}},
            {5, {"print"}}, {6, {"x", "l"}}, {7, {"x"}},    {9, {"x"}},
            {10, {"l"}},    {11, {"l"}},     {13, {"l"}},   {14, {"x"}}};

    std::unordered_map<int, std::unordered_set<std::string>> expectedUses{
        {6,
         {"if", "then", "else", "while", "read", "call", "print", "a", "b", "c",
          "d", "x", "main"}},
        {7, {"if", "then", "else", "while", "read", "call", "x"}},
        {8, {"x"}},
        {10, {"main", "print", "d"}},
        {11, {"print", "d"}},
        {12, {"d"}},
        {14, {"x"}},
    };

    std::unordered_map<int, std::unordered_set<int>> expectedNext{
        {1, {2}},       {2, {3}},    {3, {4}},   {4, {5}},  {5, {6}},
        {6, {7}},       {7, {8, 9}}, {8, {10}},  {9, {10}}, {10, {11, 14}},
        {11, {12, 13}}, {12, {10}},  {13, {10}}, {14, {6}}};

    // Entity
    std::unordered_set<std::string> expectedProcs{"main"};
    std::unordered_set<std::string> expectedVars{
        "if", "then", "else", "while", "read", "call", "print",
        "a",  "b",    "c",    "d",     "x",    "main", "l"};
    std::unordered_set<std::string> expectedConsts{"2",  "4", "1", "100000",
                                                   "10", "0", "5", "3"};
    std::unordered_set<int> expectedReads{9, 13};
    std::unordered_set<int> expectedPrints{8, 12};
    std::unordered_set<int> expectedCalls{};
    std::unordered_set<int> expectedWhiles{6, 10};
    std::unordered_set<int> expectedAssigns{1, 2, 3, 4, 5, 14};
    std::unordered_set<int> expectedIfs{7, 11};

    // Pattern
    std::unordered_map<std::string, std::unordered_set<int>> expectedIfPattern{
        {"if", {7}},   {"then", {7}}, {"else", {7}},  {"while", {7}},
        {"read", {7}}, {"call", {7}}, {"print", {11}}};
    std::unordered_map<std::string, std::unordered_set<int>>
        expectedWhilePattern{{"if", {6}},    {"then", {6}}, {"else", {6}},
                             {"while", {6}}, {"read", {6}}, {"call", {6}},
                             {"print", {6}}, {"a", {6}},    {"b", {6}},
                             {"c", {6}},     {"d", {6}},    {"main", {10}}};

    spManager.process(testFileName);

    // Relationship assertions
    REQUIRE(expectedFollows == pkbStub->followsStorage);
    REQUIRE(expectedParent == pkbStub->parentStorage);

    REQUIRE(expectedModifiesStatement == pkbStub->modifiesStatementStorage);
    REQUIRE(expectedUses == pkbStub->usesStatementStorage);

    // Entity assertions
    REQUIRE(expectedProcs == pkbStub->procedureStorage);
    REQUIRE(expectedVars == pkbStub->variableStorage);
    REQUIRE(expectedConsts == pkbStub->constantStorage);
    REQUIRE(expectedReads == pkbStub->readStorage);
    REQUIRE(expectedPrints == pkbStub->printStorage);
    REQUIRE(expectedCalls == pkbStub->callStorage);
    REQUIRE(expectedWhiles == pkbStub->whileStorage);
    REQUIRE(expectedAssigns == pkbStub->assignStorage);
    REQUIRE(expectedIfs == pkbStub->ifStorage);
    REQUIRE(expectedNext == pkbStub->nextStorage);

    // Pattern assertions
    REQUIRE(expectedIfPattern == pkbStub->ifPatternStorage);
    REQUIRE(expectedWhilePattern == pkbStub->whilePatternStorage);

    std::filesystem::remove(testFileName);
  }

  SECTION("Nested if while pattern") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure main { \n"
        "    a = 1; \n"                  // 1
        "    while (WHILE < main) { \n"  // 2
        "        while ( \n "
        "        (main < 5) && (WHILE >= while) \n"  // 3
        "        ) { \n"
        "          if (if == then) then { \n"  // 4
        "              print d; \n"            // 5
        "          } else { \n"
        "              if ( \n"
        "              !(  (IF < THEN) || ((if == while) \n"  // 6
        "              && (else != main))  ) \n"
        "              ) then { \n"
        "                  print x; \n"  // 7
        "              } else { \n"
        "                  read x; \n"  // 8
        "              } \n"
        "          } \n"
        "        } \n"
        "        x = y;\n"  // 9
        "    }\n"
        "}";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    // Pattern
    std::unordered_map<std::string, std::unordered_set<int>> expectedIfPattern{
        {"if", {4, 6}}, {"then", {4}}, {"IF", {6}},  {"THEN", {6}},
        {"while", {6}}, {"else", {6}}, {"main", {6}}};
    std::unordered_map<std::string, std::unordered_set<int>>
        expectedWhilePattern{
            {"WHILE", {2, 3}}, {"main", {2, 3}}, {"while", {3}}};

    spManager.process(testFileName);

    // Pattern assertions
    REQUIRE(expectedIfPattern == pkbStub->ifPatternStorage);
    REQUIRE(expectedWhilePattern == pkbStub->whilePatternStorage);

    std::filesystem::remove(testFileName);
  }

  SECTION("2 calls to a procedure from 2 different procedures") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure test1 { \n"
        "    call test3; \n"
        "} \n"
        "procedure test2 { \n"
        "    call test3; \n"
        "} \n"
        "procedure test3 { \n"
        "    x = 1; \n"
        "} \n";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    REQUIRE_NOTHROW(spManager.process(testFileName));

    std::filesystem::remove(testFileName);
  }

  SECTION("complex procedure calls") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure p1 { \n"
        "    call p3; \n"
        "} \n"
        "procedure p2 { \n"
        "    call p3; \n"
        "} \n"
        "procedure p3 { \n"
        "    call p4; \n"
        "} \n"
        "procedure p4 { \n"
        "    x = 1; \n"
        "} \n"
        "procedure p5 { \n"
        "    call p1; \n"
        "} \n"
        "procedure p6 { \n"
        "    call p5; \n"
        "} \n";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    REQUIRE_NOTHROW(spManager.process(testFileName));

    std::filesystem::remove(testFileName);
  }
}

TEST_CASE("Invalid SP Manager process") {
  SECTION("Empty") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput = "";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    REQUIRE_THROWS(spManager.process(testFileName));

    std::filesystem::remove(testFileName);
  }

  SECTION("Non existent file") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./nonExistent.txt";
    REQUIRE_THROWS(spManager.process(testFileName));
  }

  SECTION("Just white space") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput = " ";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    REQUIRE_THROWS(spManager.process(testFileName));

    std::filesystem::remove(testFileName);
  }

  SECTION("no procedure") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput = "x = 10;";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    REQUIRE_THROWS(spManager.process(testFileName));

    std::filesystem::remove(testFileName);
  }

  SECTION("No procedure keyword") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "test1 {\n"
        "    x = 10;\n"
        "}";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    REQUIRE_THROWS(spManager.process(testFileName));

    std::filesystem::remove(testFileName);
  }

  SECTION("One valid procedure and one invalid procedure") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure test1 { \n"
        "    x = 10; \n"
        "} \n"
        "test2 { \n"
        "    y = 11; \n"
        "}";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    REQUIRE_THROWS(spManager.process(testFileName));

    std::filesystem::remove(testFileName);
  }

  SECTION("Missing stmt list start") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure test1 \n"
        "    x = 10; \n"
        "}";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    REQUIRE_THROWS(spManager.process(testFileName));

    std::filesystem::remove(testFileName);
  }

  SECTION("Missing stmt list end") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure test1 {\n"
        "    x = 10;\n"
        "    print x;\n"
        "";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    REQUIRE_THROWS(spManager.process(testFileName));

    std::filesystem::remove(testFileName);
  }

  SECTION("Missing read semicolon") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure test1 {\n"
        "    read y\n"
        "    x = 10;\n"
        "    print x;\n"
        "}";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    REQUIRE_THROWS(spManager.process(testFileName));

    std::filesystem::remove(testFileName);
  }

  SECTION("Missing assign semicolon") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure test1 {\n"
        "    read y;\n"
        "    x = 10\n"
        "    print x;\n"
        "}";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    REQUIRE_THROWS(spManager.process(testFileName));

    std::filesystem::remove(testFileName);
  }

  SECTION("Missing print semicolon") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure test1 {\n"
        "    read y;\n"
        "    x = 10;\n"
        "    print x\n"
        "}";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    REQUIRE_THROWS(spManager.process(testFileName));

    std::filesystem::remove(testFileName);
  }

  SECTION("Missing call semicolon") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure test1 { \n"
        "    call test2 \n"
        "} \n"
        "procedure test2 { \n"
        "    y = 11; \n"
        "}";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    REQUIRE_THROWS(spManager.process(testFileName));

    std::filesystem::remove(testFileName);
  }

  SECTION("Create procedures with same name") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure test1 { \n"
        "    z = 10; \n"
        "} \n"
        "procedure test1 { \n"
        "    y = 11; \n"
        "}";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    REQUIRE_THROWS_MATCHES(spManager.process(testFileName),
                           SP::SemanticException,
                           Catch::Matchers::Message(SP::DUPLICATED_PROCEDURE));

    std::filesystem::remove(testFileName);
  }

  SECTION("Call non-existent procedure name") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure test1 { \n"
        "    z = 10; \n"
        "} \n"
        "procedure test2 { \n"
        "   call test3; \n"
        "}";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    REQUIRE_THROWS_MATCHES(
        spManager.process(testFileName), SP::SemanticException,
        Catch::Matchers::Message(SP::CALL_NON_EXSISTENT_PROCEDURE));

    std::filesystem::remove(testFileName);
  }

  SECTION("Recursive calls") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure test1 { \n"
        "    call test1; \n"
        "} \n";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    REQUIRE_THROWS_MATCHES(
        spManager.process(testFileName), SP::SemanticException,
        Catch::Matchers::Message(SP::RECURSIVE_OR_CYCLIC_CALL));

    std::filesystem::remove(testFileName);
  }

  SECTION("Cyclic calls") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure test1 { \n"
        "    call test2; \n"
        "} \n"
        "procedure test2 { \n"
        "    call test3; \n"
        "} \n"
        "procedure test3 { \n"
        "    call test3; \n"
        "} \n";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    REQUIRE_THROWS_MATCHES(
        spManager.process(testFileName), SP::SemanticException,
        Catch::Matchers::Message(SP::RECURSIVE_OR_CYCLIC_CALL));

    std::filesystem::remove(testFileName);
  }

  SECTION("Cyclic calls part2") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure test1 { \n"
        "    call test2; \n"
        "} \n"
        "procedure test2 { \n"
        "    call test3; \n"
        "} \n"
        "procedure test3 { \n"
        "    call test2; \n"
        "} \n";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    REQUIRE_THROWS_MATCHES(
        spManager.process(testFileName), SP::SemanticException,
        Catch::Matchers::Message(SP::RECURSIVE_OR_CYCLIC_CALL));

    std::filesystem::remove(testFileName);
  }
}

TEST_CASE("Test Next") {
  SECTION("Deeply nested if in a while stmt") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure main {\n"           //
        "  while (hello == 2) {\n"     // 1
        "    if (x == 1) then {\n"     // 2
        "       if (x == 2) then {\n"  // 3
        "         x = 1;\n"            // 4
        "       } else {\n"
        "         if (x == 3) then {\n"  // 5
        "           x = 3;\n"            // 6
        "         } else {\n"
        "           x = 4;\n"  // 7
        "         }\n"
        "       }\n"
        "    } else {\n"
        "       x = 2;\n"  // 8
        "    }\n"
        "  }\n"
        "}";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    spManager.process(testFileName);
    std::unordered_map<int, std::unordered_set<int>> expectedNext{
        {1, {2}}, {2, {3, 8}}, {8, {1}}, {3, {4, 5}},
        {4, {1}}, {5, {6, 7}}, {6, {1}}, {7, {1}}};

    REQUIRE(expectedNext == pkbStub->nextStorage);

    std::filesystem::remove(testFileName);
  }

  SECTION("Multiple Ifs in a single nesting") {
    std::shared_ptr<PKB::PKBStorageWriteStub> pkbStub =
        std::make_shared<PKB::PKBStorageWriteStub>();
    SP::SPManager spManager(pkbStub);
    std::string testFileName = "./TC1.txt";
    std::string testInput =
        "procedure main {\n"        //
        "  while (hello == 2) {\n"  // 1
        "    if (x == 1) then {\n"  // 2
        "      x = 1;\n"            // 3
        "    } else {\n"
        "       x = 2;\n"  // 4
        "    }\n"
        "    if (x == 1) then {\n"  // 5
        "      x = 1;\n"            // 6
        "    } else {\n"
        "       x = 2;\n"  // 7
        "    }\n"
        "  }\n"
        "}";

    std::ofstream testFile(testFileName);
    testFile << testInput;
    testFile.close();

    spManager.process(testFileName);
    std::unordered_map<int, std::unordered_set<int>> expectedNext{
        {1, {2}},    {2, {3, 4}}, {3, {5}}, {4, {5}},
        {5, {6, 7}}, {6, {1}},    {7, {1}}};

    REQUIRE(expectedNext == pkbStub->nextStorage);

    std::filesystem::remove(testFileName);
  }
}
