#pragma once

#include <cassert>
#include <limits>
#include <memory>
#include <ostream>
#include <unordered_map>
#include <vector>

#include "qps/query/declaration/Declaration.h"
#include "qps/table/NormalizedDataStorage.h"

namespace QPS {

class Table {
 public:
  using TableType = std::vector<std::vector<int>>;

  Table() = default;
  Table(const std::vector<std::string>& columns,
        const std::unordered_map<std::string, int>& column_id_map,
        const TableType& rows, bool deduplicate = true);
  Table(const std::vector<std::string>& columns,
        const std::unordered_map<std::string, int>& column_id_map,
        const std::shared_ptr<TableType>& rows, bool deduplicate = true);
  Table(const std::vector<std::string>& columns, const TableType& rows,
        bool deduplicate = true);
  Table(const std::vector<std::string>& columns,
        const std::shared_ptr<TableType>& rows, bool deduplicate = true);
  explicit Table(const std::unordered_map<std::string, std::vector<int>>& table,
                 bool deduplicate = true);
  Table(const Table& other);
  Table(Table&&) = default;
  Table& operator=(Table t);

  std::vector<int> operator[](const std::string& colName) const;
  std::vector<int> operator[](
      const std::shared_ptr<Declaration>& declaration) const;
  const std::unordered_set<std::string> getCols() const;

  /*
   * Joins 2 table and merges them into the left table, returning the left table
   */
  void sort();
  bool empty() const noexcept;
  bool trueTable() const noexcept;
  int size() const noexcept;
  int colSize() const noexcept;

 private:
  std::vector<int> getColValues(const std::string& col) const;

 public:
  friend bool operator==(const Table& lhs, const Table& rhs) noexcept;
  friend bool operator!=(const Table& lhs, const Table& rhs) noexcept;
  friend std::ostream& operator<<(std::ostream& os, const Table& table);
  friend Table operator*(const Table& lhs, const Table& rhs);
  // only works if both table has the same columns, otherwise undefined behavior
  friend Table operator-(const Table& lhs, const Table& rhs);

 private:
  std::vector<std::string> columns_;
  std::unordered_map<std::string, int> column_id_map_;
  std::shared_ptr<TableType> rows_;
};

const static inline Table EMPTY_TABLE{
    {{"", {}}}};  // read only sentinel, not global state

}  // namespace QPS
