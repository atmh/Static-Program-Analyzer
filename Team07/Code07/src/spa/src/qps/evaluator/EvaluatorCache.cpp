#include "EvaluatorCache.h"

#include <optional>
#include "qps/evaluator/such_that_clause_evaluator/ModifiesClauseEvaluator.h"
#include "qps/evaluator/such_that_clause_evaluator/UsesClauseEvaluator.h"
#include "qps/query/clauses/Argument.h"

namespace QPS {

namespace {

std::optional<std::type_index> getTypeIndexKey(
    const std::optional<std::type_index>& arg_type,
    const std::type_index& evaluator_type) {
  if (evaluator_type == typeid(ModifiesClauseEvaluator) ||
      evaluator_type == typeid(UsesClauseEvaluator))
    return arg_type;
  return std::nullopt;
}

}  // namespace

size_t EvaluatorCache::CacheKeyHash::operator()(
    const QPS::EvaluatorCache::CacheKeyType& cacheKey) const noexcept {
  auto& [type_info, arg] = cacheKey;
  return Argument::ArgHash()(arg) ^ (type_info ? type_info->hash_code() : 0);
}

void EvaluatorCache::cacheHasRelationship(const std::type_index& type,
                                          bool hasRelationship) {
  hasRelationshipCache[type] = hasRelationship;
}

void EvaluatorCache::cacheArgOne(
    const std::type_index& type,
    const std::optional<std::type_index>& argTwoType, const Argument& argOne,
    const std::unordered_set<int>& res) {
  argOneCache[type][{getTypeIndexKey(argTwoType, type), argOne}] = res;
}

void EvaluatorCache::cacheArgTwo(
    const std::type_index& type,
    const std::optional<std::type_index>& argOneType, const Argument& argTwo,
    const std::unordered_set<int>& res) {
  argTwoCache[type][{getTypeIndexKey(argOneType, type), argTwo}] = res;
}

void EvaluatorCache::cacheFullSynonyms(
    const std::type_index& type, const std::type_index& declType1,
    const std::type_index& declType2, int numCols,
    const std::shared_ptr<Table::TableType>& table) {
  fullSynonymsCache[type][{declType1, declType2, numCols}] = table;
}

std::unordered_set<int>* EvaluatorCache::getArgOne(
    const std::type_index& type,
    const std::optional<std::type_index>& argTwoType, const Argument& argOne) {
  if (argOneCache[type].find({getTypeIndexKey(argTwoType, type), argOne}) ==
      argOneCache[type].end())
    return nullptr;
  return &argOneCache[type][{getTypeIndexKey(argTwoType, type), argOne}];
}

std::unordered_set<int>* EvaluatorCache::getArgTwo(
    const std::type_index& type,
    const std::optional<std::type_index>& argOneType, const Argument& argTwo) {
  if (argTwoCache[type].find({getTypeIndexKey(argOneType, type), argTwo}) ==
      argTwoCache[type].end())
    return nullptr;
  return &argTwoCache[type][{getTypeIndexKey(argOneType, type), argTwo}];
}

bool* EvaluatorCache::getHasRelationship(const std::type_index& type) {
  if (hasRelationshipCache.find(type) == hasRelationshipCache.end())
    return nullptr;
  return &hasRelationshipCache[type];
}

std::shared_ptr<Table::TableType> EvaluatorCache::getFullSynonyms(
    const std::type_index& type, const std::type_index& declType1,
    const std::type_index& declType2, int numCols) {
  if (fullSynonymsCache[type].find({declType1, declType2, numCols}) ==
      fullSynonymsCache[type].end())
    return nullptr;
  return fullSynonymsCache[type][{declType1, declType2, numCols}];
}

}  // namespace QPS
