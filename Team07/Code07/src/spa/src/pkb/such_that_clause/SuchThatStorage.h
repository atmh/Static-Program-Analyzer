//
// Created by Ramapriyan Srivatsan PD on 1/9/23.
//
#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "SuchThatReadInterface.h"
#include "SuchThatWriteInterface.h"
#include "pkb/utils/BiDirectionalMap.h"

namespace PKB {
template <typename T, typename U>
class SuchThatStorage : public SuchThatReadInterface<T, U>,
                        public SuchThatWriteInterface<T, U> {
 protected:
  BiDirectionalMap<T, U> biDirectionalMap;

 public:
  bool getRelationshipExists(T argOne, U argTwo) override;
  std::unordered_set<U> getFirstArgRelationships(T argOne) override;
  std::unordered_set<T> getSecondArgRelationships(U argTwo) override;
  bool empty() override;
  void storeInformation(T argOne, U argTwo) override;
};
}  // namespace PKB