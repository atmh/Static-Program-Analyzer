#include <string>
#include <utility>
#include <vector>

#include "catch.hpp"
#include "qps/algorithm/SubstringComputer.h"

TEST_CASE("String substring") {
  std::vector<std::tuple<std::string, std::string, bool>> tests{
      {"abcd", "abcabcabc", false},
      {"abcd", "abcdabcabc", true},
      {"abcd", "abcabcdabc", true},
      {"abcd", "abcabcabcd", true},
      {"aa", "aaa", true},
      {"a", "a", true},
      {"a", "ab", true},
      {"b", "ab", true},
      {"ab", "a", false},
      {"ab", "ba", false},
      {"A", "ab", false},
      {"B", "ab", false},
      {"peek a boo", "you speek a bootiful language", true},
      {"anas", "bananananaspaj", true},
  };

  for (auto& [pattern, text, expected] : tests) {
    QPS::SubstringComputer<std::string> substringComputer;
    REQUIRE(substringComputer.isSubstring(pattern, text) == expected);
  }
}

TEST_CASE("Vector of string sub string") {
  std::vector<
      std::tuple<std::vector<std::string>, std::vector<std::string>, bool>>
      tests{
          {{"a", "b", "+"}, {"a", "b", "+"}, true},
          {{"a", "b", "+"}, {"a", "b", "+", "c", "+"}, true},
          {{"a", "b", "+", "c", "+"}, {"a", "b", "+"}, false},
          {{"b", "c", "+"}, {"a", "b", "+", "c", "+"}, false},
          {{"b", "a", "+"}, {"a", "b", "+", "c", "+"}, false},
      };

  for (auto& [pattern, text, expected] : tests) {
    QPS::SubstringComputer<std::vector<std::string>> substringComputer;
    REQUIRE(substringComputer.isSubstring(pattern, text) == expected);
  }
}
