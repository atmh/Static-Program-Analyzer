//
// Created by Ramapriyan Srivatsan PD on 21/9/23.
//
#include "NoClauseStorage.h"

#include "pkb/utils/entity_structs/CallEntity.h"
#include "pkb/utils/entity_structs/PrintEntity.h"
#include "pkb/utils/entity_structs/ReadEntity.h"
#include "string"

namespace PKB {

template <typename T>
void NoClauseStorage<T>::storeEntity(T entity) {
  entities.insert(entity);
}

template <typename T>
bool NoClauseStorage<T>::contains(T entity) {
  return entities.count(entity) == 1;
}

template <typename T>
bool NoClauseStorage<T>::empty() {
  return entities.empty();
}

template <typename T>
const std::unordered_set<T>& NoClauseStorage<T>::getAllEntities() const {
  return entities;
}

template class NoClauseStorage<int>;
template class NoClauseStorage<std::string>;
template class NoClauseStorage<PKB::CallEntity>;
template class NoClauseStorage<PKB::PrintEntity>;
template class NoClauseStorage<PKB::ReadEntity>;
}  // namespace PKB
