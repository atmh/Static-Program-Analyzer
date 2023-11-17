//
// Created by Ramapriyan Srivatsan PD on 21/9/23.
//
#include "SuchThatStorage.h"

namespace PKB {

template <typename T, typename U>
bool SuchThatStorage<T, U>::getRelationshipExists(T argOne, U argTwo) {
  return biDirectionalMap.hasMapping(argOne, argTwo);
}

template <typename T, typename U>
std::unordered_set<U> SuchThatStorage<T, U>::getFirstArgRelationships(
    T argOne) {
  return biDirectionalMap.getValues(argOne);
}

template <typename T, typename U>
std::unordered_set<T> SuchThatStorage<T, U>::getSecondArgRelationships(
    U argTwo) {
  return biDirectionalMap.getKeys(argTwo);
}

template <typename T, typename U>
bool SuchThatStorage<T, U>::empty() {
  return biDirectionalMap.empty();
}

template <typename T, typename U>
void SuchThatStorage<T, U>::storeInformation(T argOne, U argTwo) {
  biDirectionalMap.addMapping(argOne, argTwo);
}

template class SuchThatStorage<int, int>;
template class SuchThatStorage<int, std::string>;
template class SuchThatStorage<std::string, std::string>;
}  // namespace PKB