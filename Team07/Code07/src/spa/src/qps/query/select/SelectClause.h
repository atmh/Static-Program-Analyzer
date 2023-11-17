#pragma once
#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "qps/query/QueryResult.h"
#include "qps/query/Validateable.h"
#include "qps/query/declaration/Declaration.h"
#include "qps/table/NormalizedDataStorage.h"
#include "qps/table/Table.h"

namespace QPS {

class SelectClause : public Validateable {
 public:
  SelectClause();

  explicit SelectClause(
      const std::vector<std::shared_ptr<Declaration>>& declarations);

  // handle boolean selection logic here
  QueryResult select(
      const Table& table,
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage) const;

  // project table values
  Table project(const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
                const Table& table,
                const std::shared_ptr<NormalizedDataStorage>& dataStorage,
                bool eagerProject = true,
                const std::vector<std::string>& additionalCols = {}) const;

  const std::vector<std::shared_ptr<Declaration>>& getDeclarations()
      const noexcept;
  virtual bool validate() const override;

 private:
  enum class SelectClauseType {
    BOOLEAN,
    VALUE,
  };

 private:
  std::vector<std::shared_ptr<Declaration>>
      declarations;  // declaration to select
  SelectClauseType selectClauseType;
};

}  // namespace QPS
