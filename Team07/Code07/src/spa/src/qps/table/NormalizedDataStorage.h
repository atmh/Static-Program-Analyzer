#pragma once

#include <cassert>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace QPS {

class NormalizedDataStorage {
 public:
  int encodeInt(int i);
  std::unordered_set<int> encodeInts(const std::unordered_set<int>& ints);
  std::string decodeInt(int int_id) const;
  int encodeString(const std::string& s);
  std::unordered_set<int> encodeStrings(
      const std::unordered_set<std::string>& strings);
  std::string decodeString(int string_id) const;

 private:
  std::unordered_map<std::string, int> string_to_id_;
  std::unordered_map<int, std::string> id_to_string_;
};

}  // namespace QPS
