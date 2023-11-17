#pragma once

#include <map>
#include <optional>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include "qps/query/clauses/Argument.h"
#include "qps/table/Table.h"

namespace QPS {

class EvaluatorCache {
 public:
  EvaluatorCache() = default;
  void cacheHasRelationship(const std::type_index& type, bool hasRelationship);
  void cacheArgOne(const std::type_index& type,
                   const std::optional<std::type_index>& argTwoType,
                   const Argument& argOne, const std::unordered_set<int>& res);
  void cacheArgTwo(const std::type_index& type,
                   const std::optional<std::type_index>& argOneType,
                   const Argument& argTwo, const std::unordered_set<int>& res);
  void cacheFullSynonyms(const std::type_index& type,
                         const std::type_index& declType1,
                         const std::type_index& declType2, int numCols,
                         const std::shared_ptr<Table::TableType>& table);

  bool* getHasRelationship(const std::type_index& type);
  std::unordered_set<int>* getArgOne(
      const std::type_index& type,
      const std::optional<std::type_index>& argTwoType, const Argument& argOne);
  std::unordered_set<int>* getArgTwo(
      const std::type_index& type,
      const std::optional<std::type_index>& argOneType, const Argument& argTwo);
  std::shared_ptr<Table::TableType> getFullSynonyms(
      const std::type_index& type, const std::type_index& declType1,
      const std::type_index& declType2, int numCols);

 private:
  using CacheKeyType = std::tuple<std::optional<std::type_index>, Argument>;
  using FullCacheKeyType = std::tuple<std::optional<std::type_index>,
                                      std::optional<std::type_index>, int>;

  struct CacheKeyHash {
    size_t operator()(const CacheKeyType& cacheKey) const noexcept;
  };

  std::unordered_map<std::type_index, bool> hasRelationshipCache;
  std::unordered_map<
      std::type_index,
      std::unordered_map<CacheKeyType, std::unordered_set<int>, CacheKeyHash>>
      argOneCache;  // give it arg one
  std::unordered_map<
      std::type_index,
      std::unordered_map<CacheKeyType, std::unordered_set<int>, CacheKeyHash>>
      argTwoCache;  // give it arg two
  std::unordered_map<
      std::type_index,
      std::map<FullCacheKeyType, std::shared_ptr<Table::TableType>>>
      fullSynonymsCache;
};

}  // namespace QPS
