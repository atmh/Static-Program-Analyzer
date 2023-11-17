#pragma once

#include "Argument.h"
#include "qps/evaluator/EvaluatorFactory.h"
#include "qps/query/Validateable.h"

namespace QPS {

class Clause : public EvaluatorFactory, public Validateable {
 public:
  virtual ~Clause() = 0;
  Table evaluate(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache = nullptr);
  bool validateStmtRef(const Argument& arg) const;
  bool validateEntRef(const Argument& arg) const;
  bool validateExpr(const Argument& arg) const;
  size_t estimatedCost(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache);
  virtual std::vector<std::shared_ptr<Declaration>> synonyms() const = 0;

 private:
  virtual size_t doEstimatedCost(
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage,
      const std::shared_ptr<EvaluatorCache>& evaluatorCache);

 private:
  size_t cost{std::numeric_limits<size_t>::max()};
};

inline Clause::~Clause() = default;

}  // namespace QPS
