//
// Created by Ramapriyan Srivatsan PD on 21/9/23.
//

#include "StarStorage.h"

#include <iostream>

namespace PKB {
template <typename T>
std::unordered_set<T> StarStorage<T>::getFirstArgStarRelationships(T argOne) {
  return starBiDirectionalMap.getValues(argOne);
}

template <typename T>
std::unordered_set<T> StarStorage<T>::getSecondArgStarRelationships(T argTwo) {
  return starBiDirectionalMap.getKeys(argTwo);
}

template <typename T>
bool StarStorage<T>::getStarRelationshipExists(T argOne, T argTwo) {
  return starBiDirectionalMap.hasMapping(argOne, argTwo);
}

template <typename T>
void StarStorage<T>::storeInformation(T argOne, T argTwo) {
  this->biDirectionalMap.addMapping(argOne, argTwo);

  if (getStarRelationshipExists(argOne, argTwo)) {
    return;
  }

  for (const T& elem : getSecondArgStarRelationships(argOne)) {
    starBiDirectionalMap.addMapping(elem, argTwo);
  }
  for (const T& elem : getFirstArgStarRelationships(argTwo)) {
    starBiDirectionalMap.addMapping(argOne, elem);
  }
  for (const T& firstArg : getSecondArgStarRelationships(argOne)) {
    for (const T& secondArg : getFirstArgStarRelationships(argTwo)) {
      starBiDirectionalMap.addMapping(firstArg, secondArg);
    }
  }
  starBiDirectionalMap.addMapping(argOne, argTwo);
};

template <typename T>
bool StarStorage<T>::starEmpty() {
  return starBiDirectionalMap.empty();
}

template class StarStorage<int>;
template class StarStorage<std::string>;
}  // namespace PKB
