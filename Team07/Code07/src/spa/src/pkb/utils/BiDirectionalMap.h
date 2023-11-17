//
// Created by Ramapriyan Srivatsan PD on 29/8/23.
//
#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace PKB {
template <typename T, typename U>
class BiDirectionalMap {
 private:
  std::unordered_map<T, std::unordered_set<U>> map;
  std::unordered_map<U, std::unordered_set<T>> reverseMap;

 public:
  std::unordered_map<T, std::unordered_set<U>> getMap() { return map; }

  std::unordered_map<U, std::unordered_set<T>> getReverseMap() {
    return reverseMap;
  }

  bool empty() { return map.empty(); }

  std::unordered_set<U> getValues(T arg) {
    if (!hasKey(arg)) {
      return std::unordered_set<U>();
    }
    return map.at(arg);
  }

  std::unordered_set<T> getKeys(U arg) {
    if (!hasValue(arg)) {
      return std::unordered_set<T>();
    }
    return reverseMap.at(arg);
  }

  // changed cond to !=
  bool hasKey(T arg) { return map.find(arg) != map.end(); }

  bool hasValue(U arg) { return reverseMap.find(arg) != reverseMap.end(); }

  bool hasMapping(T argOne, U argTwo) {
    if (!hasKey(argOne)) {
      return false;
    }
    auto res = map.find(argOne);
    return res->second.count(argTwo) == 1;
  }

  void addMapping(T argOne, U argTwo) {
    map[argOne].insert(argTwo);
    reverseMap[argTwo].insert(argOne);
  }
};
}  // namespace PKB
