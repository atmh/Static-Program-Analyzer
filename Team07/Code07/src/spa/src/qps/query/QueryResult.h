#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include "qps/query/declaration/Declaration.h"
#include "qps/query/declaration/visitor/DeclarationStringSerializer.h"
#include "qps/table/NormalizedDataStorage.h"
#include "qps/table/Table.h"

namespace QPS {

class QueryResult {
 public:
  QueryResult() = default;

  explicit QueryResult(const std::string& output);
  explicit QueryResult(
      const Table& table,
      const std::vector<std::shared_ptr<Declaration>>& declarations,
      const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
      const std::shared_ptr<NormalizedDataStorage>& dataStorage);

  operator std::list<std::string>() const;

 private:
  Table table;
  std::vector<std::shared_ptr<Declaration>> declarations;
  std::shared_ptr<PKB::PKBStorageReadInterface> pkb;
  std::shared_ptr<NormalizedDataStorage> dataStorage;
  std::string output;
};

}  // namespace QPS
