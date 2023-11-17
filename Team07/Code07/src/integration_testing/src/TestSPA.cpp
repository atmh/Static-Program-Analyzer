#include <filesystem>
#include <iostream>

#include "SPA.h"
#include "catch.hpp"

TEST_CASE("Test SPA") {
  SPA::SPA spa{};
  std::string testFileName = "./TC1.txt";
  std::string testInput =
      "procedure Barbie {\n"
      "   print sasha;\n"
      " gloria = b * 8;\n"
      "    c = 2;\n"
      "   a = 4 - gloria;\n"
      "    call Ken;\n"
      "    while (sasha < c) {\n"
      "        sasha = b + c * a;\n"
      "       if (sasha > 1) then {\n"
      "            read a;\n"
      "           gloria = gloria + b + c; }\n"
      "         else {\n"
      "           b = a % b + c * a;\n"
      "          call Ruth; }\n"
      "       b = a - b; }\n"
      "  read sasha;\n"
      "   gloria = b / c * a; }\n"
      "\n"
      "\n"
      "procedure Ken {\n"
      "  if (gloria > sasha) then {\n"
      "\t     sasha = a - 4;\n"
      "      call Ruth; }\n"
      "   else {\n"
      "\t     gloria = 2; }             }\n"
      "\n"
      "\n"
      "procedure Ruth {\n"
      "  while (16 != (b + c))                {\n"
      "       read c; }               }";

  std::string query =
      "variable v, v2; assign a, a2; print pn, pn2; stmt s, s2; call c, c2; "
      "procedure p, p2; if if, if2; while w, w2;\n"
      "Select p such that Uses(p, _)";
  std::list<std::string> results;
  std::ofstream testFile(testFileName);
  testFile << testInput;
  testFile.close();

  spa.process(testFileName);
  spa.evaluate(query, results);

  REQUIRE(std::unordered_set<std::string>{results.begin(), results.end()} ==
          std::unordered_set<std::string>{"Ken", "Ruth", "Barbie"});
  std::filesystem::remove(testFileName);
}
