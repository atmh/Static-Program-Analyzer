#pragma once

#include <cassert>
#include <vector>

namespace QPS {

// kmp algorithm from steven
// https://github.com/stevenhalim/cpbook-code/blob/master/ch6/string_matching.cpp
// does not accept empty pattern or text in substring search
template <typename T>
class SubstringComputer {
 public:
  bool isSubstring(const T& pattern, const T& text);

 private:
  std::vector<int> kmpPreprocess(const T& pattern);
};

}  // namespace QPS
