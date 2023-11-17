#include "SuchThatClauseEvaluator.h"

#include <algorithm>
#include <optional>

#include "qps/query/declaration/visitor/ArgumentConstructor.h"

namespace QPS {

namespace {

std::unordered_set<int> intersect(const std::unordered_set<int>& lhs,
                                  const std::unordered_set<int>& rhs) {
  std::unordered_set<int> res;

  const std::unordered_set<int>& smallerSet =
      lhs.size() < rhs.size() ? lhs : rhs;
  const std::unordered_set<int>& largerSet =
      lhs.size() < rhs.size() ? rhs : lhs;

  for (auto a : smallerSet) {
    if (largerSet.find(a) != largerSet.end()) {
      res.insert(a);
    }
  }

  return res;
}

std::unordered_set<int> filterDeclarations(
    const Declaration& decl,
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::unordered_set<int>& unfilteredResult,
    std::optional<std::unordered_set<int>>& declarations) {
  DeclarationSelector selector(pkb, dataStorage);
  decl.accept(selector);
  if (!declarations)
    declarations = selector.getResult();
  return intersect(unfilteredResult, declarations.value());
}

}  // namespace

SuchThatClauseEvaluator::SuchThatClauseEvaluator(const Argument& arg1,
                                                 const Argument& arg2)
    : arg1(arg1), arg2(arg2), evalFunc(getEvalFunc(arg1, arg2)) {}

/**
 * These switch statements are used in the constructor! Not violating G7.
 */
SuchThatClauseEvaluator::EvalFuncType SuchThatClauseEvaluator::getEvalFunc(
    const Argument& arg1, const Argument& arg2) {
  switch (arg1.getArgumentType()) {
    case Argument::ArgumentType::SYNONYM:
      return getSynonymEvalFunc(arg2);
    case Argument::ArgumentType::STRING:
    case Argument::ArgumentType::INTEGER:
      return getValueEvalFunc(arg2);
    case Argument::ArgumentType::WILDCARD:
      return getWildcardEvalFunc(arg2);
    default:
      assert(false);
      return {};
  }
}

/**
 * These switch statements are used in the constructor! Not violating G7.
 */
SuchThatClauseEvaluator::EvalFuncType
SuchThatClauseEvaluator::getSynonymEvalFunc(const QPS::Argument& arg2) {
  switch (arg2.getArgumentType()) {
    case Argument::ArgumentType::SYNONYM:
      return &SuchThatClauseEvaluator::evaluateSynonymSynonym;
    case Argument::ArgumentType::STRING:
    case Argument::ArgumentType::INTEGER:
      return &SuchThatClauseEvaluator::evaluateSynonymValue;
    case Argument::ArgumentType::WILDCARD:
      return &SuchThatClauseEvaluator::evaluateSynonymWildcard;
    default:
      assert(false);
      return {};
  }
}

/**
 * These switch statements are used in the constructor! Not violating G7.
 */
SuchThatClauseEvaluator::EvalFuncType SuchThatClauseEvaluator::getValueEvalFunc(
    const QPS::Argument& arg2) {
  switch (arg2.getArgumentType()) {
    case Argument::ArgumentType::SYNONYM:
      return &SuchThatClauseEvaluator::evaluateValueSynonym;
    case Argument::ArgumentType::STRING:
    case Argument::ArgumentType::INTEGER:
      return &SuchThatClauseEvaluator::evaluateValueValue;
    case Argument::ArgumentType::WILDCARD:
      return &SuchThatClauseEvaluator::evaluateValueWildcard;
    default:
      assert(false);
      return {};
  }
}

/**
 * These switch statements are used in the constructor! Not violating G7.
 */
SuchThatClauseEvaluator::EvalFuncType
SuchThatClauseEvaluator::getWildcardEvalFunc(const QPS::Argument& arg2) {
  switch (arg2.getArgumentType()) {
    case Argument::ArgumentType::SYNONYM:
      return &SuchThatClauseEvaluator::evaluateWildcardSynonym;
    case Argument::ArgumentType::STRING:
    case Argument::ArgumentType::INTEGER:
      return &SuchThatClauseEvaluator::evaluateWildcardValue;
    case Argument::ArgumentType::WILDCARD:
      return &SuchThatClauseEvaluator::evaluateWildcardWildcard;
    default:
      assert(false);
      return {};
  }
}

Table SuchThatClauseEvaluator::evaluate(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  assert(evalFunc && "Should be initialized in the constructor");
  // create a temporary evaluator cache if we do not want to cache across different evaluations
  return (this->*evalFunc)(pkb, dataStorage,
                           evaluatorCache != nullptr
                               ? evaluatorCache
                               : std::make_shared<EvaluatorCache>());
}

Table SuchThatClauseEvaluator::evaluateSynonymSynonym(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  std::shared_ptr<Declaration> decl1 = arg1;
  std::shared_ptr<Declaration> decl2 = arg2;
  std::vector<std::string> columns =
      (*decl1 == *decl2)
          ? std::vector<std::string>{decl1->name()}
          : std::vector<std::string>{decl1->name(), decl2->name()};
  int numCols = static_cast<int>(columns.size());
  if (!evaluatorCache->getFullSynonyms(typeid(*this), typeid(*decl1),
                                       typeid(*decl2), numCols)) {
    DeclarationSelector declarationSelector{pkb, dataStorage};
    decl1->accept(declarationSelector);
    auto& declarations = declarationSelector.getResult();

    std::shared_ptr<std::vector<std::vector<int>>> rows =
        std::make_shared<std::vector<std::vector<int>>>();

    std::optional<std::unordered_set<int>> declarationsCache{};
    for (auto d1 : declarations) {
      ArgumentConstructor argumentConstructor1{d1, dataStorage};
      decl1->accept(argumentConstructor1);
      auto& unfilteredResult = getFirstArgRelationships(
          pkb, dataStorage, evaluatorCache, argumentConstructor1);
      auto filteredResults = filterDeclarations(
          *decl2, pkb, dataStorage, unfilteredResult, declarationsCache);
      for (auto d2 : filteredResults) {
        if ((*decl1 == *decl2)) {
          if (d1 == d2) {
            rows->push_back({d1});
          }
        } else {
          rows->push_back({d1, d2});
        }
      }
    }

    evaluatorCache->cacheFullSynonyms(typeid(*this), typeid(*decl1),
                                      typeid(*decl2), numCols, rows);
  }

  auto rows = evaluatorCache->getFullSynonyms(typeid(*this), typeid(*decl1),
                                              typeid(*decl2), numCols);
  return {columns, rows, false};
}

Table SuchThatClauseEvaluator::evaluateSynonymValue(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  std::shared_ptr<Declaration> decl = arg1;
  auto& unfilteredResult =
      getSecondArgRelationships(pkb, dataStorage, evaluatorCache, arg2);
  std::optional<std::unordered_set<int>> declarations{};
  auto filteredResults = filterDeclarations(*decl, pkb, dataStorage,
                                            unfilteredResult, declarations);
  return Table{
      {{decl->name(), {filteredResults.begin(), filteredResults.end()}}}};
}

Table SuchThatClauseEvaluator::evaluateSynonymWildcard(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  std::shared_ptr<Declaration> decl = arg1;
  DeclarationSelector declarationSelector{pkb, dataStorage};
  decl->accept(declarationSelector);
  auto& declarations = declarationSelector.getResult();

  std::vector<int> results;
  std::copy_if(
      declarations.begin(), declarations.end(), std::back_inserter(results),
      [this, &pkb, &dataStorage, &decl, &evaluatorCache](int x) {
        ArgumentConstructor argumentConstructor{x, dataStorage};
        decl->accept(argumentConstructor);
        return !getFirstArgRelationships(pkb, dataStorage, evaluatorCache,
                                         argumentConstructor)
                    .empty();  // if it is possible to get some result from this
      });

  return Table{{{decl->name(), {results.begin(), results.end()}}}};
}

Table SuchThatClauseEvaluator::evaluateValueSynonym(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  std::shared_ptr<Declaration> decl = arg2;
  auto& unfilteredResult =
      getFirstArgRelationships(pkb, dataStorage, evaluatorCache, arg1);
  std::optional<std::unordered_set<int>> declarations{};
  auto filteredResults = filterDeclarations(*decl, pkb, dataStorage,
                                            unfilteredResult, declarations);
  return Table{
      {{decl->name(), {filteredResults.begin(), filteredResults.end()}}}};
}

Table SuchThatClauseEvaluator::evaluateValueValue(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  if (getRelationshipExists(pkb, dataStorage, evaluatorCache, arg1, arg2))
    return {};
  return EMPTY_TABLE;
}

Table SuchThatClauseEvaluator::evaluateValueWildcard(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  if (getFirstArgRelationships(pkb, dataStorage, evaluatorCache, arg1).empty())
    return EMPTY_TABLE;
  return {};
}

Table SuchThatClauseEvaluator::evaluateWildcardSynonym(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  std::shared_ptr<Declaration> decl = arg2;
  DeclarationSelector declarationSelector{pkb, dataStorage};
  decl->accept(declarationSelector);
  auto& declarations = declarationSelector.getResult();

  std::vector<int> results;
  std::copy_if(
      declarations.begin(), declarations.end(), std::back_inserter(results),
      [this, &pkb, &dataStorage, &decl, &evaluatorCache](int x) {
        ArgumentConstructor argumentConstructor{x, dataStorage};
        decl->accept(argumentConstructor);
        return !getSecondArgRelationships(pkb, dataStorage, evaluatorCache,
                                          argumentConstructor)
                    .empty();  // if it is possible to get some result from this
      });

  return Table{{{decl->name(), {results.begin(), results.end()}}}};
}

Table SuchThatClauseEvaluator::evaluateWildcardValue(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  if (getSecondArgRelationships(pkb, dataStorage, evaluatorCache, arg2).empty())
    return EMPTY_TABLE;
  return {};
}

Table SuchThatClauseEvaluator::evaluateWildcardWildcard(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  if (!hasRelationship(pkb, evaluatorCache))
    return EMPTY_TABLE;
  return {};
}

bool SuchThatClauseEvaluator::hasRelationship(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  assert(evaluatorCache &&
         "should be initialized here even if there was no cache");
  if (!evaluatorCache->getHasRelationship(typeid(*this)))
    evaluatorCache->cacheHasRelationship(typeid(*this), doHasRelationship(pkb));
  return *evaluatorCache->getHasRelationship(typeid(*this));
}

const std::unordered_set<int>&
SuchThatClauseEvaluator::getFirstArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache,
    const QPS::Argument& arg) {
  std::shared_ptr<Declaration> decl = arg2;
  std::optional<std::type_index> declType =
      decl ? std::optional<std::type_index>(typeid(*decl)) : std::nullopt;
  assert(evaluatorCache &&
         "should be initialized here even if there was no cache");
  if (!evaluatorCache->getArgOne(typeid(*this), declType, arg))
    evaluatorCache->cacheArgOne(
        typeid(*this), declType, arg,
        doGetFirstArgRelationships(pkb, dataStorage, arg));
  return *evaluatorCache->getArgOne(typeid(*this), declType, arg);
}

const std::unordered_set<int>&
SuchThatClauseEvaluator::getSecondArgRelationships(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache,
    const QPS::Argument& arg) {
  std::shared_ptr<Declaration> decl = arg1;
  std::optional<std::type_index> declType =
      decl ? std::optional<std::type_index>(typeid(*decl)) : std::nullopt;
  assert(evaluatorCache &&
         "should be initialized here even if there was no cache");
  if (!evaluatorCache->getArgTwo(typeid(*this), declType, arg))
    evaluatorCache->cacheArgTwo(
        typeid(*this), declType, arg,
        doGetSecondArgRelationships(pkb, dataStorage, arg));
  return *evaluatorCache->getArgTwo(typeid(*this), declType, arg);
}

SuchThatClauseEvaluator::~SuchThatClauseEvaluator() = default;

}  // namespace QPS
