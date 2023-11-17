#pragma once

#include <memory>
#include <set>
#include <type_traits>
#include <typeindex>

#include "qps/query/clauses/Argument.h"
#include "qps/query/clauses/Clause.h"

namespace QPS {

class FollowsRelationship;
class FollowsStarRelationship;
class ParentRelationship;
class ParentStarRelationship;
class UsesRelationship;
class ModifiesRelationship;
class CallsRelationship;
class CallsStarRelationship;
class NextRelationship;
class NextStarRelationship;
class AffectsRelationship;

template <typename Relationship>
class SuchThatClause : public Clause {
 public:
  SuchThatClause(const Argument& arg1, const Argument& arg2)
      : arg1(arg1), arg2(arg2) {}

  virtual std::shared_ptr<Evaluator> createEvaluator() const override;

  virtual bool validate() const override;

  virtual ~SuchThatClause() = default;

  virtual std::vector<std::shared_ptr<Declaration>> synonyms() const override;

 private:
  const static std::set<std::type_index> allowedArg1Declarations;
  const static std::set<std::type_index> allowedArg2Declarations;
  Argument arg1;
  Argument arg2;

  bool validateArgDeclarations() const;
};
}  // namespace QPS
