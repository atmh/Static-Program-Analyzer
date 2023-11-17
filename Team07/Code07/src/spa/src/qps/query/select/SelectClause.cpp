#include "SelectClause.h"

#include <cassert>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

#include "qps/query/declaration/visitor/DeclarationSelector.h"

namespace QPS {

namespace {

std::vector<std::vector<int>> transpose(std::vector<std::vector<int>>& arr) {
  if (arr.empty())
    return {};

  int m = static_cast<int>(arr.size());
  int n = static_cast<int>(arr.front().size());

  std::vector<std::vector<int>> res(n, std::vector<int>(m));

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      res[j][i] = arr[i][j];
    }
  }

  return res;
}

}  // namespace

SelectClause::SelectClause()
    : declarations(), selectClauseType(SelectClauseType::BOOLEAN) {}

SelectClause::SelectClause(
    const std::vector<std::shared_ptr<Declaration>>& declarations)
    : declarations(declarations), selectClauseType(SelectClauseType::VALUE) {}

QueryResult SelectClause::select(
    const Table& table,
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage) const {
  static constexpr auto FALSE = "FALSE";
  static constexpr auto TRUE = "TRUE";
  switch (selectClauseType) {
    case SelectClauseType::VALUE:
      return QueryResult{table, declarations, pkb, dataStorage};
    case SelectClauseType::BOOLEAN:
      return table.empty() ? QueryResult{FALSE} : QueryResult{TRUE};
    default:
      assert(false);
      return {};
  }
}

Table SelectClause::project(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const QPS::Table& table,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    bool eagerProject, const std::vector<std::string>& additionalCols) const {
  if (table.empty()) {
    return EMPTY_TABLE;
  }

  std::unordered_set<std::string> visitedSynonyms;

  // get cols that exist
  std::vector<std::string> existingCols;
  std::vector<std::vector<int>> existingColValues;
  for (const auto& declaration : declarations) {
    auto col = table[declaration];
    if (col.empty())
      continue;
    if (visitedSynonyms.find(declaration->name()) != visitedSynonyms.end())
      continue;
    visitedSynonyms.insert(declaration->name());
    existingCols.emplace_back(declaration->name());
    existingColValues.emplace_back(col);
  }

  for (const auto& colName : additionalCols) {
    auto col = table[colName];
    if (col.empty())
      continue;
    if (visitedSynonyms.find(colName) != visitedSynonyms.end())
      continue;
    visitedSynonyms.insert(colName);
    existingCols.emplace_back(colName);
    existingColValues.emplace_back(col);
  }

  Table newTable{existingCols, transpose(existingColValues)};

  if (!eagerProject)
    return newTable;

  // get cols that do not exist
  for (const auto& declaration : declarations) {
    auto col = table[declaration];
    if (!col.empty())
      continue;
    if (visitedSynonyms.find(declaration->name()) != visitedSynonyms.end())
      continue;
    visitedSynonyms.insert(declaration->name());
    DeclarationSelector declarationSelector{pkb, dataStorage};
    declaration->accept(declarationSelector);
    auto result = declarationSelector.getResult();
    newTable =
        newTable *
        Table{{{declaration->name(), {result.begin(), result.end()}}}, false};
  }

  return newTable;
}

const std::vector<std::shared_ptr<Declaration>>& SelectClause::getDeclarations()
    const noexcept {
  return declarations;
}

bool SelectClause::validate() const {
  if (selectClauseType == SelectClauseType::BOOLEAN)
    return true;
  for (auto& decl : declarations) {
    if (decl == nullptr)
      return false;
  }
  return true;
}

}  // namespace QPS
