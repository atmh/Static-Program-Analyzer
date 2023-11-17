#include "QueryResult.h"

#include <string>
#include <unordered_set>

namespace QPS {

namespace {

std::list<std::string> removeDuplicates(const std::list<std::string>& s) {
  std::unordered_set<std::string> uniqueSet{s.begin(), s.end()};

  return {uniqueSet.begin(), uniqueSet.end()};
}

}  // namespace

QueryResult::QueryResult(const std::string& output)
    : table(), declarations(), pkb(), dataStorage(), output(output) {}

QueryResult::QueryResult(
    const Table& table,
    const std::vector<std::shared_ptr<Declaration>>& declarations,
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage)
    : table(table),
      pkb(pkb),
      declarations(declarations),
      dataStorage(dataStorage),
      output() {}

QueryResult::operator std::list<std::string>() const {
  if (!output.empty()) {
    assert(output == "FALSE" || output == "TRUE");
    return {output};
  }

  std::list<std::string> res;
  std::vector<std::vector<int>> cols;
  for (auto d : declarations)
    cols.emplace_back(table[d]);

  assert(!table.trueTable() && "Projection logic error");

  for (size_t j = 0; j < table.size(); ++j) {
    std::string curr;
    bool first = true;
    for (size_t i = 0; i < declarations.size(); ++i) {
      if (!first)
        curr += ' ';
      first = false;
      auto declaration = declarations[i];
      auto serializer_lambda = [this, &declaration](const int x) {
        DeclarationStringSerializer string_serializer{pkb, dataStorage, x};
        declaration->accept(string_serializer);
        return string_serializer.getResult();
      };
      curr += serializer_lambda(cols[i][j]);
    }
    res.push_back(curr);
  }
  return removeDuplicates(res);
}

}  // namespace QPS
