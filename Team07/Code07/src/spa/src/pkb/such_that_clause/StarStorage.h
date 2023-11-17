//
// Created by Ramapriyan Srivatsan PD on 6/9/23.
//
#pragma once
#include "StarStorageReadInterface.h"
#include "StarStorageWriteInterface.h"
#include "pkb/such_that_clause/SuchThatStorage.h"

namespace PKB {

template <typename T>
class StarStorage : public SuchThatStorage<T, T>,
                    public StarStorageReadInterface<T>,
                    public StarStorageWriteInterface<T> {
 protected:
  BiDirectionalMap<T, T> starBiDirectionalMap;

 public:
  std::unordered_set<T> getFirstArgStarRelationships(T arg) override;
  std::unordered_set<T> getSecondArgStarRelationships(T arg) override;
  bool getStarRelationshipExists(T argOne, T argTwo) override;
  void storeInformation(T argOne, T argTwo) override;
  bool starEmpty() override;
};
}  // namespace PKB
