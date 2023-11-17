#include "SubstringComputer.h"

#include <string>
#include <vector>

namespace QPS {

template <typename T>
bool SubstringComputer<T>::isSubstring(const T& pattern, const T& text) {
  assert(!pattern.empty());
  assert(!text.empty());

  if (pattern.empty() && text.empty())
    return false;
  if (pattern.empty() && !text.empty())
    return true;

  int n = static_cast<int>(text.size());
  int m = static_cast<int>(pattern.size());

  std::vector<int> b = kmpPreprocess(pattern);

  int i = 0;
  int j = 0;
  while (i < n) {
    while ((j >= 0) && (text[i] != pattern[j]))
      j = b[j];
    ++i;
    ++j;
    if (j == m) {
      return true;
    }
  }
  return false;
}

template <typename T>
std::vector<int> SubstringComputer<T>::kmpPreprocess(const T& pattern) {
  int m = static_cast<int>(pattern.size());

  std::vector<int> b(m + 1);

  int i = 0;
  int j = -1;
  b[0] = -1;

  while (i < m) {
    while ((j >= 0) && (pattern[i] != pattern[j]))
      j = b[j];
    ++i;
    ++j;
    assert(i < b.size());
    b[i] = j;
  }

  return b;
}

template class SubstringComputer<std::vector<std::string>>;
template class SubstringComputer<std::string>;

}  // namespace QPS
