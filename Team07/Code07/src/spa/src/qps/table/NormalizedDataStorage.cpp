#include "NormalizedDataStorage.h"

#include <cassert>

namespace QPS {

int NormalizedDataStorage::encodeInt(int i) {
  return i;
}

std::unordered_set<int> NormalizedDataStorage::encodeInts(
    const std::unordered_set<int>& stmts) {
  return stmts;
}

std::string NormalizedDataStorage::decodeInt(int int_id) const {
  return std::to_string(int_id);
}

int NormalizedDataStorage::encodeString(const std::string& s) {
  if (string_to_id_.find(s) == string_to_id_.end()) {
    int id = static_cast<int>(string_to_id_.size());
    string_to_id_[s] = id;
    id_to_string_[id] = s;
  }
  return string_to_id_[s];
}

std::unordered_set<int> NormalizedDataStorage::encodeStrings(
    const std::unordered_set<std::string>& variables) {
  std::unordered_set<int> res;

  for (const auto& v : variables) {
    if (string_to_id_.find(v) == string_to_id_.end()) {
      int id = static_cast<int>(string_to_id_.size());
      string_to_id_[v] = id;
      id_to_string_[id] = v;
    }
    res.insert(string_to_id_[v]);
  }

  return res;
}

std::string NormalizedDataStorage::decodeString(int string_id) const {
  auto it = id_to_string_.find(string_id);
  assert(it != id_to_string_.end() && "variable id not found in normalizer");
  return it->second;
}

}  // namespace QPS
