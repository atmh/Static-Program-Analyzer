#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "common/parser/Parser.h"
#include "common/token/Token.h"
#include "qps/query/Query.h"
#include "qps/query/clauses/Argument.h"
#include "qps/query/declaration/DeclarationFactory.h"

namespace QPS {

class QPSParser : Common::Parser {
 public:
  explicit QPSParser(std::vector<Common::Token> tokens);
  void parse() override;
  Query getQuery();
  std::vector<std::string> getDeclaredNames();

 private:
  std::vector<std::string> declaredNames;
  std::unordered_map<std::string, std::shared_ptr<DeclarationFactory>>
      nameToFactory;
  Query parsedQuery;

  void parseSelect();
  void parseDeclarations();
  void parseSuchThatClause();
  void parsePatternClause();
  void parseWithClause();

  void parseDeclaration(const std::shared_ptr<DeclarationFactory>& factory);

  std::pair<Argument, Argument> constructSuchThatRelationshipArguments(
      const std::string&);
  Argument constructStmtRefArg();
  Argument constructEntRefArg();
  Argument constructRefArg();
  Argument constructNonExprArg();
  Argument constructExpressionArg();
  SelectClause constructTupleSelectClause();

  bool isCurrentTokenValidNameWithoutSpecialChar();
};

}  // namespace QPS
