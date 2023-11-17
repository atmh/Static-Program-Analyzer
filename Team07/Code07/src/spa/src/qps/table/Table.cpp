#include "Table.h"

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iterator>
#include <map>
#include <set>
#include <unordered_set>

namespace QPS {

namespace {

std::vector<std::vector<int>> deduplicateRows(
    const std::vector<std::vector<int>>& arr) {
  std::set<std::vector<int>> s;
  for (auto& a : arr)
    s.insert(a);
  std::vector<std::vector<int>> res;
  res.reserve(s.size());
  for (auto& a : s)
    res.push_back(a);
  return res;
}

std::vector<std::string> getColsFromTable(
    const std::unordered_map<std::string, std::vector<int>>& table) {
  std::vector<std::string> res;

  for (auto& [k, v] : table) {
    res.emplace_back(k);
  }

  sort(res.begin(), res.end());

  return res;
}

std::unordered_map<std::string, int> getColMap(
    const std::vector<std::string>& cols) {
  std::unordered_map<std::string, int> m;

  for (const auto& col : cols) {
    m[col] = static_cast<int>(m.size());
  }

  assert(cols.size() == m.size());

  return m;
}

std::vector<std::vector<int>> getRows(
    const std::vector<std::string>& columns,
    std::unordered_map<std::string, int>& col_id_map,
    const std::unordered_map<std::string, std::vector<int>>& table) {
  if (columns.empty())
    return {};

  std::vector<std::vector<int>> res;

  int row_len = static_cast<int>(table.begin()->second.size());

  for (int row = 0; row < row_len; ++row) {
    std::vector<int> row_entry(columns.size());

    for (auto& [col, v] : table) {
      int col_id = col_id_map[col];
      row_entry[col_id] = v[row];
      assert(v.size() == row_len);
    }

    res.emplace_back(row_entry);
  }

  sort(res.begin(), res.end());
  return res;
}

template <typename Container>
Container getIntersection(const Container& lhs, const Container& rhs) {
  Container res;

  for (const auto& a : rhs) {
    if (lhs.find(a) != lhs.end()) {
      res.insert(a);
    }
  }

  return res;
}

std::vector<std::vector<int>> getSetDifference(
    const std::vector<std::vector<int>>& lhs,
    const std::vector<std::vector<int>>& rhs) {
  std::set<std::vector<int>> rhsSet;
  std::vector<std::vector<int>> res;
  for (const auto& r : rhs)
    rhsSet.insert(r);

  for (const auto& l : lhs) {
    if (rhsSet.find(l) == rhsSet.end())
      res.push_back(l);
  }
  return res;
}

template <typename AssocContainer, typename RetContainer>
RetContainer getKeys(const AssocContainer& container) {
  RetContainer ret;

  for (auto& [k, v] : container) {
    ret.insert(k);
  }

  return ret;
}

std::vector<std::vector<int>> cross(const std::vector<std::vector<int>>& lhs,
                                    const std::vector<std::vector<int>>& rhs) {
  std::vector<std::vector<int>> res;

  int lhs_row_len = static_cast<int>(lhs.size());
  int rhs_row_len = static_cast<int>(rhs.size());

  res.reserve(lhs_row_len * rhs_row_len);

  for (int i = 0; i < lhs_row_len; ++i) {
    for (int j = 0; j < rhs_row_len; ++j) {
      std::vector<int> newRow;
      newRow.reserve(lhs[i].size() + rhs[j].size());
      newRow.insert(newRow.end(), lhs[i].begin(), lhs[i].end());
      newRow.insert(newRow.end(), rhs[j].begin(), rhs[j].end());
      res.emplace_back(newRow);
    }
  }

  return res;
}

std::unordered_set<int> getCommonSynonymIds(
    const std::unordered_set<std::string>& synonyms,
    const std::unordered_set<std::string>& common_synonyms,
    const std::unordered_map<std::string, int>& column_id_map) {
  std::unordered_set<int> common_col_id;
  for (const auto& synonym : synonyms) {
    if (common_synonyms.find(synonym) != common_synonyms.end()) {
      common_col_id.insert(column_id_map.find(synonym)->second);
    }
  }
  return common_col_id;
}

std::map<std::vector<int>, std::vector<std::vector<int>>> extractCommonCol(
    const std::vector<std::vector<int>>& rows,
    const std::unordered_set<int>& common_col_id) {
  std::map<std::vector<int>, std::vector<std::vector<int>>> common_to_rows;
  for (const auto& row : rows) {
    std::vector<int> common_col_vals;
    std::vector<int> diff_col_vals;

    for (int i = 0; i < row.size(); ++i) {
      if (common_col_id.find(i) == common_col_id.end())  // not common
      {
        diff_col_vals.emplace_back(row[i]);
      } else {
        common_col_vals.emplace_back(row[i]);
      }
    }

    common_to_rows[common_col_vals].emplace_back(diff_col_vals);
  }

  return common_to_rows;
}

std::vector<std::string> getNewCols(
    const std::vector<std::string>& lhsCols,
    const std::vector<std::string>& rhsCols,
    const std::unordered_set<std::string>& common_synonyms) {
  std::vector<std::string> new_columns;
  std::copy_if(lhsCols.begin(), lhsCols.end(), std::back_inserter(new_columns),
               [&common_synonyms](auto& col) {
                 return common_synonyms.find(col) == common_synonyms.end();
               });
  std::copy_if(rhsCols.begin(), rhsCols.end(), std::back_inserter(new_columns),
               [&common_synonyms](auto& col) {
                 return common_synonyms.find(col) == common_synonyms.end();
               });
  std::copy_if(lhsCols.begin(), lhsCols.end(), std::back_inserter(new_columns),
               [&common_synonyms](auto& col) {
                 return common_synonyms.find(col) != common_synonyms.end();
               });
  return new_columns;
}

std::shared_ptr<std::vector<std::vector<int>>> crossRows(
    const std::set<std::vector<int>>& common_rows,
    std::map<std::vector<int>, std::vector<std::vector<int>>>&
        lhs_common_to_rows,
    std::map<std::vector<int>, std::vector<std::vector<int>>>&
        rhs_common_to_rows) {
  auto new_rows = std::make_shared<std::vector<std::vector<int>>>();
  for (auto& common_row : common_rows) {
    std::vector<std::vector<int>> cross_product =
        cross(lhs_common_to_rows[common_row], rhs_common_to_rows[common_row]);
    for (auto& row : cross_product) {
      row.reserve(row.size() + common_row.size());
      row.insert(row.end(), common_row.begin(), common_row.end());
    }
    for (auto& row : cross_product)
      new_rows->emplace_back(std::move(row));
  }
  return new_rows;
}

}  // namespace

Table::Table(const std::unordered_map<std::string, std::vector<int>>& table,
             bool deduplicate)
    : columns_(getColsFromTable(table)),
      column_id_map_(getColMap(columns_)),
      rows_(std::make_shared<TableType>(
          deduplicate
              ? deduplicateRows(getRows(columns_, column_id_map_, table))
              : getRows(columns_, column_id_map_, table))) {}

Table::Table(const std::vector<std::string>& columns,
             const std::vector<std::vector<int>>& rows, bool deduplicate)
    : columns_(columns),
      column_id_map_(getColMap(columns)),
      rows_(std::make_shared<TableType>(deduplicate ? deduplicateRows(rows)
                                                    : rows)) {}

Table::Table(const std::vector<std::string>& columns,
             const std::unordered_map<std::string, int>& column_id_map,
             const TableType& rows, bool deduplicate)
    : columns_(columns),
      column_id_map_(column_id_map),
      rows_(std::make_shared<TableType>(deduplicate ? deduplicateRows(rows)
                                                    : rows)) {}

Table::Table(const std::vector<std::string>& columns,
             const std::unordered_map<std::string, int>& column_id_map,
             const std::shared_ptr<TableType>& rows, bool deduplicate)
    : columns_(columns),
      column_id_map_(column_id_map),
      rows_(deduplicate ? std::make_shared<TableType>(deduplicateRows(*rows))
                        : rows) {}

Table::Table(const std::vector<std::string>& columns,
             const std::shared_ptr<std::vector<std::vector<int>>>& rows,
             bool deduplicate)
    : columns_(columns),
      column_id_map_(getColMap(columns)),
      rows_(deduplicate ? std::make_shared<TableType>(deduplicateRows(*rows))
                        : rows) {}

Table::Table(const Table& other)
    : columns_(other.columns_),
      column_id_map_(other.column_id_map_),
      rows_(other.rows_ ? std::make_shared<TableType>(*other.rows_) : nullptr) {

}

Table& Table::operator=(Table other) {
  std::swap(columns_, other.columns_);
  std::swap(column_id_map_, other.column_id_map_);
  std::swap(rows_, other.rows_);
  return *this;
}

std::vector<int> Table::operator[](const std::string& colName) const {
  return getColValues(colName);
}

std::vector<int> Table::operator[](
    const std::shared_ptr<Declaration>& declaration) const {
  return getColValues(declaration->name());
}

bool operator==(const Table& lhs, const Table& rhs) noexcept {
  Table lhs_cpy = lhs;
  Table rhs_cpy = rhs;
  lhs_cpy.sort();
  rhs_cpy.sort();
  if (lhs.trueTable() && rhs.trueTable())
    return true;
  if (lhs.empty() && rhs.empty())
    return true;
  return lhs_cpy.columns_ == rhs_cpy.columns_ &&
         *lhs_cpy.rows_ == *rhs_cpy.rows_;
}

bool operator!=(const Table& lhs, const Table& rhs) noexcept {
  return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Table& table) {
  Table table_cpy = table;
  table_cpy.sort();
  constexpr int MAX_WIDTH = 5;
  if (table.empty())
    return os << "Empty Table";

  if (table.trueTable())
    return os << "True Table";

  int cols = static_cast<int>(table_cpy.columns_.size());

  // print headers
  for (const auto& col : table_cpy.columns_) {
    os << '|';
    os << std::setw(MAX_WIDTH) << col;
  }
  os << '|';
  os << '\n';

  // print line
  for (int i = 0; i < cols * (MAX_WIDTH + 1) + 1; ++i) {
    os << '-';
  }
  os << '\n';

  // print rows
  for (const auto& row : *table_cpy.rows_) {
    for (const auto v : row) {
      os << '|';
      os << std::setw(MAX_WIDTH) << v;
    }
    os << '|';
    os << '\n';
  }

  return os;
}

Table operator*(const Table& l, const Table& r) {
  if (l.trueTable())
    return r;
  if (r.trueTable())
    return l;
  if (l.empty() || r.empty())
    return EMPTY_TABLE;
  // do a copy and sort first
  Table lhs = l;
  Table rhs = r;
  lhs.sort();
  rhs.sort();

  std::unordered_set<std::string> lhs_synonyms = lhs.getCols();
  std::unordered_set<std::string> rhs_synonyms = rhs.getCols();
  std::unordered_set<std::string> common_synonyms =
      getIntersection(lhs_synonyms, rhs_synonyms);

  // no common synonym cases
  if (common_synonyms.empty()) {
    std::vector<std::string> new_columns;
    new_columns.insert(new_columns.end(), lhs.columns_.begin(),
                       lhs.columns_.end());
    new_columns.insert(new_columns.end(), rhs.columns_.begin(),
                       rhs.columns_.end());
    std::unordered_map<std::string, int> new_column_id_map =
        getColMap(new_columns);
    return Table{new_columns, new_column_id_map, cross(*lhs.rows_, *rhs.rows_),
                 false};
  }

  // extract common synonym cols
  std::unordered_set<int> lhs_common_col_id =
      getCommonSynonymIds(lhs_synonyms, common_synonyms, lhs.column_id_map_);
  std::unordered_set<int> rhs_common_col_id =
      getCommonSynonymIds(rhs_synonyms, common_synonyms, rhs.column_id_map_);
  std::map<std::vector<int>, std::vector<std::vector<int>>> lhs_common_to_rows =
      extractCommonCol(*lhs.rows_, lhs_common_col_id);
  std::map<std::vector<int>, std::vector<std::vector<int>>> rhs_common_to_rows =
      extractCommonCol(*rhs.rows_, rhs_common_col_id);

  // get common rows
  std::set<std::vector<int>> common_rows = getIntersection(
      getKeys<std::map<std::vector<int>, std::vector<std::vector<int>>>,
              std::set<std::vector<int>>>(lhs_common_to_rows),
      getKeys<std::map<std::vector<int>, std::vector<std::vector<int>>>,
              std::set<std::vector<int>>>(rhs_common_to_rows));
  std::shared_ptr<std::vector<std::vector<int>>> new_rows =
      crossRows(common_rows, lhs_common_to_rows, rhs_common_to_rows);
  std::vector<std::string> new_columns =
      getNewCols(lhs.columns_, rhs.columns_, common_synonyms);
  std::unordered_map<std::string, int> new_column_id_map =
      getColMap(new_columns);

  return Table{new_columns, new_column_id_map, new_rows, false};
}

Table operator-(const Table& l, const Table& r) {
  if (l.empty() || r.trueTable())
    return EMPTY_TABLE;
  if (r.empty())
    return l;
  assert(!l.trueTable() && "LHS should be explicitly populated");

  Table lhs = l;
  Table rhs = r;
  lhs.sort();
  rhs.sort();
  assert(lhs.columns_ == rhs.columns_);

  return {lhs.columns_, getSetDifference(*lhs.rows_, *rhs.rows_), false};
}

std::vector<int> Table::getColValues(const std::string& col) const {
  if (column_id_map_.find(col) == column_id_map_.end()) {
    return {};
  }

  int col_id = column_id_map_.find(col)->second;
  std::vector<int> res;

  for (const auto& row : *rows_) {
    res.emplace_back(row[col_id]);
  }

  return res;
}

const std::unordered_set<std::string> Table::getCols() const {
  return {columns_.begin(), columns_.end()};
}

void Table::sort() {
  std::unordered_map<std::string, std::vector<int>> table;

  for (const auto& [col, col_id] : column_id_map_) {
    std::vector<int> col_vals;
    for (const auto& row : *rows_) {
      col_vals.emplace_back(row[col_id]);
    }
    table[col] = col_vals;
  }

  *this = Table(table, false);  // use constructor logic to auto sort
}

bool Table::empty() const noexcept {
  return !columns_.empty() && rows_->empty();
}

bool Table::trueTable() const noexcept {
  return size() == std::numeric_limits<int>::max();
}

int Table::size() const noexcept {
  return columns_.empty() ? std::numeric_limits<int>::max()
                          : static_cast<int>(rows_->size());
}

int Table::colSize() const noexcept {
  return static_cast<int>(columns_.size());
}

}  // namespace QPS
