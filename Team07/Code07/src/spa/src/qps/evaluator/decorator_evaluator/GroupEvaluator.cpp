#include "GroupEvaluator.h"

namespace QPS {

namespace {

std::unordered_map<std::string, int> getSynonymFreq(
    const std::vector<std::shared_ptr<Clause>>& clauses) {
  std::unordered_map<std::string, int> freq;

  for (const auto& c : clauses) {
    std::unordered_set<std::string> s;
    for (const auto& synonym : c->synonyms()) {
      s.insert(synonym->name());
    }
    for (const auto& name : s) {
      freq[name]++;
    }
  }

  return freq;
}

void optimizeTable(Table& table,
                   std::unordered_map<std::string, int>& synonymFreq,
                   const SelectClause& selectClause,
                   std::unordered_set<std::string>& accumulatedSynonyms,
                   const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
                   const std::shared_ptr<NormalizedDataStorage>& dataStorage) {
  if (table.empty() || table.trueTable())
    return;
  std::unordered_set<std::string> colSet = table.getCols();
  auto projectedSet = selectClause.getDeclarations();

  std::vector<std::string> requiredCols;
  std::vector<std::string> currCols = {colSet.begin(), colSet.end()};
  std::unordered_set<std::string> finalProjectedCols;
  for (const auto& d : projectedSet)
    finalProjectedCols.insert(d->name());

  for (const auto& col : currCols) {
    assert(synonymFreq[col] != 0 &&
           "If freq is 0, it should not even be part of the table's column!");
    if (synonymFreq[col] == 1 &&
        finalProjectedCols.find(col) ==
            finalProjectedCols.end())  // this col will never be used ever again
    {
      synonymFreq[col]--;
      accumulatedSynonyms.erase(accumulatedSynonyms.find(col));
      continue;
    }
    requiredCols.push_back(col);
  }

  if (requiredCols == currCols)  // we need all the cols we have right now
    return;

  table = selectClause.project(pkb, table, dataStorage, false, requiredCols);
}

std::vector<std::string> getCommonCols(
    const std::unordered_set<std::string>& accumulatedSynonyms,
    const std::shared_ptr<Clause>& clause) {
  auto currClauseSynonyms = clause->synonyms();
  std::unordered_set<std::string> currSynonyms;
  for (const auto& s : currClauseSynonyms)
    currSynonyms.insert(s->name());

  std::vector<std::string> result;
  for (const auto& s : currSynonyms) {
    if (accumulatedSynonyms.find(s) != accumulatedSynonyms.end())
      result.push_back(s);
  }
  return result;
}

}  // namespace

GroupEvaluator::GroupEvaluator(
    const SelectClause& selectClause,
    const std::vector<std::shared_ptr<Clause>>& clauses)
    : selectClause(selectClause), clauses(clauses) {}

Table GroupEvaluator::evaluate(
    const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb,
    const std::shared_ptr<NormalizedDataStorage>& dataStorage,
    const std::shared_ptr<EvaluatorCache>& evaluatorCache) {
  auto synonyms = selectClause.getDeclarations();
  std::unordered_set<std::string> synonymsSet;
  for (const auto& s : synonyms)
    synonymsSet.insert(s->name());

  std::unordered_set<std::string> accumulatedSynonyms;
  std::unordered_map<std::string, int> synonymFreq = getSynonymFreq(clauses);
  std::unordered_set<std::string> currSynonymsInResultTable;

  Table table;
  for (const auto& clause : clauses) {
    std::vector<std::string> commonCols =
        getCommonCols(accumulatedSynonyms, clause);
    for (const auto& s : clause->synonyms())
      accumulatedSynonyms.insert(s->name());

    Table curr = clause->evaluate(pkb, dataStorage, evaluatorCache);

    if (curr.trueTable())
      continue;  // prevent a copy

    optimizeTable(table, synonymFreq, selectClause, accumulatedSynonyms, pkb,
                  dataStorage);
    optimizeTable(curr, synonymFreq, selectClause, accumulatedSynonyms, pkb,
                  dataStorage);

    table = table * curr;

    for (const auto& col : commonCols)
      synonymFreq[col]--;

    if (table.empty())
      break;
  }
  // maybe after last join, we can drop some synonyms
  optimizeTable(table, synonymFreq, selectClause, accumulatedSynonyms, pkb,
                dataStorage);
  return table;
}

}  // namespace QPS
