#include "QPSParser.h"

#include <cctype>
#include <functional>
#include <memory>
#include <unordered_map>

#include "common/algorithm/ShuntingYard.h"
#include "qps/exception/Messages.h"
#include "qps/exception/QPSParserException.h"
#include "qps/query/Query.h"
#include "qps/query/clauses/NotClause.h"
#include "qps/query/clauses/PatternClause.h"
#include "qps/query/clauses/SuchThatClause.h"
#include "qps/query/clauses/WithClause.h"
#include "qps/query/declaration/DeclarationCreator.h"
#include "qps/query/declaration/DeclarationFactory.h"

namespace QPS {

// TODO: See if using unique_ptr is possible
const std::unordered_map<std::string, std::shared_ptr<DeclarationFactory>>
    declarationMap{
        {"assign", std::make_shared<DeclarationCreator<AssignDeclaration>>()},
        {"call", std::make_shared<DeclarationCreator<CallDeclaration>>()},
        {"constant",
         std::make_shared<DeclarationCreator<ConstantDeclaration>>()},
        {"if", std::make_shared<DeclarationCreator<IfDeclaration>>()},
        {"print", std::make_shared<DeclarationCreator<PrintDeclaration>>()},
        {"procedure",
         std::make_shared<DeclarationCreator<ProcedureDeclaration>>()},
        {"read", std::make_shared<DeclarationCreator<ReadDeclaration>>()},
        {"stmt", std::make_shared<DeclarationCreator<StatementDeclaration>>()},
        {"variable",
         std::make_shared<DeclarationCreator<VariableDeclaration>>()},
        {"while", std::make_shared<DeclarationCreator<WhileDeclaration>>()},
    };

const std::unordered_map<std::string, std::function<std::shared_ptr<Clause>(
                                          const Argument&, const Argument&)>>
    entities{
        {"Follows",
         [](const Argument& arg1, const Argument& arg2) {
           return std::make_shared<SuchThatClause<FollowsRelationship>>(arg1,
                                                                        arg2);
         }},
        {"Follows*",
         [](const Argument& arg1, const Argument& arg2) {
           return std::make_shared<SuchThatClause<FollowsStarRelationship>>(
               arg1, arg2);
         }},
        {"Parent",
         [](const Argument& arg1, const Argument& arg2) {
           return std::make_shared<SuchThatClause<ParentRelationship>>(arg1,
                                                                       arg2);
         }},
        {"Parent*",
         [](const Argument& arg1, const Argument& arg2) {
           return std::make_shared<SuchThatClause<ParentStarRelationship>>(
               arg1, arg2);
         }},
        {"Uses",
         [](const Argument& arg1, const Argument& arg2) {
           return std::make_shared<SuchThatClause<UsesRelationship>>(arg1,
                                                                     arg2);
         }},
        {"Modifies",
         [](const Argument& arg1, const Argument& arg2) {
           return std::make_shared<SuchThatClause<ModifiesRelationship>>(arg1,
                                                                         arg2);
         }},
        {"Calls",
         [](const Argument& arg1, const Argument& arg2) {
           return std::make_shared<SuchThatClause<CallsRelationship>>(arg1,
                                                                      arg2);
         }},
        {"Calls*",
         [](const Argument& arg1, const Argument& arg2) {
           return std::make_shared<SuchThatClause<CallsStarRelationship>>(arg1,
                                                                          arg2);
         }},
        {"Next",
         [](const Argument& arg1, const Argument& arg2) {
           return std::make_shared<SuchThatClause<NextRelationship>>(arg1,
                                                                     arg2);
         }},
        {"Next*",
         [](const Argument& arg1, const Argument& arg2) {
           return std::make_shared<SuchThatClause<NextStarRelationship>>(arg1,
                                                                         arg2);
         }},
        {"Calls",
         [](const Argument& arg1, const Argument& arg2) {
           return std::make_shared<SuchThatClause<CallsRelationship>>(arg1,
                                                                      arg2);
         }},
        {"Calls*",
         [](const Argument& arg1, const Argument& arg2) {
           return std::make_shared<SuchThatClause<CallsStarRelationship>>(arg1,
                                                                          arg2);
         }},
        {"Next",
         [](const Argument& arg1, const Argument& arg2) {
           return std::make_shared<SuchThatClause<NextRelationship>>(arg1,
                                                                     arg2);
         }},
        {"Next*",
         [](const Argument& arg1, const Argument& arg2) {
           return std::make_shared<SuchThatClause<NextStarRelationship>>(arg1,
                                                                         arg2);
         }},
        {"Affects", [](const Argument& arg1, const Argument& arg2) {
           return std::make_shared<SuchThatClause<AffectsRelationship>>(arg1,
                                                                        arg2);
         }}};

const std::unordered_set<std::string> attrKeywords{"procName", "varName",
                                                   "value", "stmt#"};
const std::unordered_set<std::string> entRefEntRefEntities{"Calls", "Calls*"};
const std::unordered_set<std::string> nonExprEntRefEntities{"Modifies", "Uses"};

constexpr auto OPEN_TUPLE = "<";
constexpr auto CLOSE_TUPLE = ">";
constexpr auto OPEN_BRACKET = "(";
constexpr auto CLOSE_BRACKET = ")";
constexpr auto ATTR_SEP = ".";
constexpr auto DECL_SEP = ",";
constexpr auto TUPLE_SEP = ",";
constexpr auto ARGUMENT_SEP = ",";
constexpr auto BOOLEAN_SELECT = "BOOLEAN";
constexpr auto NEGATION = "not";
constexpr auto SELECT_CLAUSE_START = "Select";
constexpr auto SUCH_CLAUSE_START = "such";
constexpr auto PATTERN_CLAUSE_START = "pattern";
constexpr auto WITH_CLAUSE_START = "with";
constexpr auto CLAUSE_CONJUNCTION = "and";
constexpr auto THAT = "that";
constexpr auto WILDCARD = "_";
constexpr auto EQUAL_SIGN = "=";
constexpr auto SEMICOLON = ";";
constexpr auto QUOTATION_MARKS = "\"";

QPSParser::QPSParser(std::vector<Common::Token> tokens)
    : Common::Parser(std::move(tokens)) {}

void QPSParser::parse() {
  parseDeclarations();
  parseSelect();

  while (hasNext()) {
    if (isCurrentValue(SUCH_CLAUSE_START)) {
      parseToken(SUCH_CLAUSE_START);
      parseToken(THAT);
      for (parseSuchThatClause();
           hasNext() && isCurrentValue(CLAUSE_CONJUNCTION);) {
        parseToken(CLAUSE_CONJUNCTION);
        parseSuchThatClause();
      }
    } else if (isCurrentValue(PATTERN_CLAUSE_START)) {
      parseToken(PATTERN_CLAUSE_START);
      for (parsePatternClause();
           hasNext() && isCurrentValue(CLAUSE_CONJUNCTION);) {
        parseToken(CLAUSE_CONJUNCTION);
        parsePatternClause();
      }
    } else if (isCurrentValue(WITH_CLAUSE_START)) {
      parseToken(WITH_CLAUSE_START);
      for (parseWithClause();
           hasNext() && isCurrentValue(CLAUSE_CONJUNCTION);) {
        parseToken(CLAUSE_CONJUNCTION);
        parseWithClause();
      }
    } else
      throw QPSParserException("Not Supported");
  }
}

Query QPSParser::getQuery() {
  return parsedQuery;
}

std::vector<std::string> QPSParser::getDeclaredNames() {
  return declaredNames;
}

bool QPSParser::isCurrentTokenValidNameWithoutSpecialChar() {
  // Invariant of token: The special char must appear as last char
  return isCurrentType(Common::TokenType::name) &&
         std::isalnum(peek().getValue().back());
}

void QPSParser::parseDeclarations() {
  while (hasNext()) {
    const std::string s = peek().getValue();
    auto pt = declarationMap.find(s);
    if (pt == declarationMap.end())
      return;
    get();
    parseDeclaration(pt->second);
  }
}

void QPSParser::parseSelect() {
  parseToken(SELECT_CLAUSE_START);

  if (isCurrentValue(OPEN_TUPLE)) {
    parsedQuery = Query(constructTupleSelectClause());
    return;
  } else if (!isCurrentTokenValidNameWithoutSpecialChar())
    throw QPSParserException(INVALID_SELECT_CLAUSE);

  const std::string name = get().getValue();
  const auto pt = nameToFactory.find(name);

  if (pt != nameToFactory.end()) {
    if (hasNext() && isCurrentValue(ATTR_SEP)) {
      get();
      const std::string attr = parseToken(Common::TokenType::name).getValue();
      if (attrKeywords.find(attr) == attrKeywords.end())
        throw QPSParserException(INVALID_ATTR_NAME);
      parsedQuery =
          Query(SelectClause({pt->second->createDeclaration(name, attr)}));
    } else {
      parsedQuery = Query(SelectClause({pt->second->createDeclaration(name)}));
    }
  } else if (name == BOOLEAN_SELECT)
    parsedQuery = Query(SelectClause());
  else
    parsedQuery = Query(SelectClause({nullptr}));
}

void QPSParser::parseSuchThatClause() {
  bool negate = false;
  if (hasNext() && isCurrentValue(NEGATION)) {
    get();
    negate = true;
  }
  if (!hasNext())
    throw QPSParserException(INVALID_SUCH_THAT_CLAUSE);

  const std::string entityString = get().getValue();
  const auto pt = entities.find(entityString);
  if (pt == entities.end())
    throw QPSParserException(INVALID_SUCH_THAT_CLAUSE);

  parseToken(OPEN_BRACKET);
  const auto [arg1, arg2] =
      constructSuchThatRelationshipArguments(entityString);
  parseToken(CLOSE_BRACKET);
  parsedQuery.addClause(
      negate ? std::make_shared<NotClause>(pt->second(arg1, arg2))
             : pt->second(arg1, arg2));
}

void QPSParser::parsePatternClause() {
  bool negate = false;
  if (hasNext() && isCurrentValue(NEGATION)) {
    get();
    negate = true;
  }

  if (!hasNext())
    throw QPSParserException(INVALID_PATTERN_CLAUSE);

  const std::string name = get().getValue();
  const auto pt = nameToFactory.find(name);
  bool ok = pt != nameToFactory.end();

  parseToken(OPEN_BRACKET);
  std::vector<Argument> arguments{constructEntRefArg()};

  parseToken(ARGUMENT_SEP);
  arguments.push_back(constructExpressionArg());

  if (!isCurrentValue(CLOSE_BRACKET)) {
    parseToken(ARGUMENT_SEP);
    parseToken(WILDCARD);
    arguments.emplace_back();
  }
  parseToken(CLOSE_BRACKET);

  if (!ok) {
    parsedQuery.addClause(nullptr);
    return;
  }

  std::shared_ptr<Clause> clausePtr;

  if (arguments.size() == 3) {
    if (arguments[1].getArgumentType() != Argument::ArgumentType::WILDCARD ||
        arguments[2].getArgumentType() != Argument::ArgumentType::WILDCARD)
      throw QPSParserException(INVALID_PATTERN_CLAUSE);
    else
      clausePtr = std::make_shared<PatternClause<If>>(
          pt->second->createDeclaration(name), arguments[0]);
  } else if (arguments[1].getArgumentType() !=
             Argument::ArgumentType::WILDCARD) {
    clausePtr = std::make_shared<PatternClause<Assign>>(
        pt->second->createDeclaration(name), arguments[0], arguments[1]);
  } else if (typeid(*pt->second) ==
             typeid(DeclarationCreator<WhileDeclaration>)) {
    clausePtr = std::make_shared<PatternClause<While>>(
        pt->second->createDeclaration(name), arguments[0]);
  } else
    clausePtr = std::make_shared<PatternClause<Assign>>(
        pt->second->createDeclaration(name), arguments[0], arguments[1]);

  if (negate)
    parsedQuery.addClause(std::make_shared<NotClause>(clausePtr));
  else
    parsedQuery.addClause(clausePtr);
}

void QPSParser::parseWithClause() {
  bool negate = false;
  if (hasNext() && isCurrentValue(NEGATION)) {
    get();
    negate = true;
  }
  if (!hasNext())
    throw QPSParserException(INVALID_SUCH_THAT_CLAUSE);

  Argument arg1 = constructRefArg();
  parseToken(EQUAL_SIGN);
  Argument arg2 = constructRefArg();

  std::shared_ptr<WithClause> clausePtr =
      std::make_shared<WithClause>(arg1, arg2);
  if (negate)
    parsedQuery.addClause(std::make_shared<NotClause>(clausePtr));
  else
    parsedQuery.addClause(clausePtr);
}

void QPSParser::parseDeclaration(
    const std::shared_ptr<DeclarationFactory>& factory) {
  for (bool found = false; hasNext() || !found; parseToken(DECL_SEP)) {
    if (!isCurrentTokenValidNameWithoutSpecialChar())
      throw QPSParserException(INVALID_DECLARATION);
    const std::string name = get().getValue();
    found = true;
    nameToFactory[name] = factory;
    declaredNames.push_back(name);

    if (isCurrentValue(SEMICOLON)) {
      get();
      return;
    }
  }
}

std::pair<Argument, Argument> QPSParser::constructSuchThatRelationshipArguments(
    const std::string& relationshipEntity) {
  Argument arg1, arg2;
  if (entRefEntRefEntities.find(relationshipEntity) !=
      entRefEntRefEntities.end()) {
    arg1 = constructEntRefArg();
    parseToken(ARGUMENT_SEP);
    arg2 = constructEntRefArg();
  } else if (nonExprEntRefEntities.find(relationshipEntity) !=
             nonExprEntRefEntities.end()) {
    arg1 = constructNonExprArg();
    parseToken(ARGUMENT_SEP);
    arg2 = constructEntRefArg();
  } else {
    arg1 = constructStmtRefArg();
    parseToken(ARGUMENT_SEP);
    arg2 = constructStmtRefArg();
  }
  return {arg1, arg2};
}

Argument QPSParser::constructExpressionArg() {
  if (!isCurrentValue(WILDCARD) && !isCurrentValue(QUOTATION_MARKS))
    throw QPSParserException(INVALID_EXPRESSION);

  bool fullMatch = !isCurrentValue(WILDCARD);
  if (!fullMatch)
    parseToken(WILDCARD);
  if (!isCurrentValue(QUOTATION_MARKS))
    return {};
  parseToken(QUOTATION_MARKS);
  std::vector<Common::Token> exprTokens;
  while (!isCurrentValue(QUOTATION_MARKS)) {
    if (isCurrentType(Common::TokenType::name) &&
        !isCurrentTokenValidNameWithoutSpecialChar()) {
      const std::string name = get().getValue();
      exprTokens.emplace_back(name.substr(0, name.size() - 1),
                              Common::TokenType::name);
      exprTokens.emplace_back(std::string(1, name.back()),
                              Common::TokenType::special);
    } else
      exprTokens.push_back(get());
  }
  parseToken(QUOTATION_MARKS);
  if (!fullMatch)
    parseToken(WILDCARD);

  try {
    const auto& tree = Common::ShuntingYard::evalMath(exprTokens);
    return {tree, fullMatch};
  } catch (const Common::ShuntingYardException&) {
    throw QPSParserException(INVALID_EXPRESSION);
  }
}

Argument QPSParser::constructStmtRefArg() {
  if (isCurrentValue(WILDCARD)) {
    get();
    return {};
  } else if (isCurrentType(Common::TokenType::integer)) {
    return {stoi(get().getValue())};
  } else if (!isCurrentTokenValidNameWithoutSpecialChar())
    throw QPSParserException(INVALID_STMT_REF);

  // The previous if case guarantee it is not out of bounds
  const std::string name = get().getValue();
  const auto pt = nameToFactory.find(name);
  if (pt == nameToFactory.end())
    return {static_cast<std::shared_ptr<Declaration>>(nullptr)};
  return pt->second->createDeclaration(name);
}

Argument QPSParser::constructEntRefArg() {
  if (isCurrentValue(WILDCARD)) {
    get();
    return {};
  } else if (isCurrentValue(QUOTATION_MARKS)) {
    Argument res;
    parseToken(QUOTATION_MARKS);
    if (isCurrentTokenValidNameWithoutSpecialChar())
      res = {get().getValue()};
    else
      throw QPSParserException(INVALID_ENT_REF);
    parseToken(QUOTATION_MARKS);
    return res;
  } else if (!isCurrentTokenValidNameWithoutSpecialChar())
    throw QPSParserException(INVALID_ENT_REF);

  // The previous if case guarantee it is not out of bounds
  const std::string name = get().getValue();
  const auto pt = nameToFactory.find(name);
  if (pt == nameToFactory.end())
    return {static_cast<std::shared_ptr<Declaration>>(nullptr)};
  return pt->second->createDeclaration(name);
}

Argument QPSParser::constructRefArg() {
  if (isCurrentValue(QUOTATION_MARKS)) {
    parseToken(QUOTATION_MARKS);
    if (!isCurrentTokenValidNameWithoutSpecialChar())
      throw QPSParserException(INVALID_REF);
    const std::string name = get().getValue();
    parseToken(QUOTATION_MARKS);
    return {name};
  } else if (isCurrentType(Common::TokenType::integer)) {
    return {stoi(get().getValue())};
  } else if (!isCurrentTokenValidNameWithoutSpecialChar())
    throw QPSParserException(INVALID_REF);

  // The previous if case guarantee it is not out of bounds
  const std::string name = get().getValue();
  parseToken(ATTR_SEP);
  const std::string attr = parseToken(Common::TokenType::name).getValue();

  const auto pt = nameToFactory.find(name);
  if (pt == nameToFactory.end())
    return {static_cast<std::shared_ptr<Declaration>>(nullptr)};
  if (attrKeywords.find(attr) == attrKeywords.end())
    throw QPSParserException(INVALID_ATTR_NAME);

  return pt->second->createDeclaration(name, attr);
}

Argument QPSParser::constructNonExprArg() {
  if (isCurrentValue(QUOTATION_MARKS))
    return constructEntRefArg();
  return constructStmtRefArg();
}

SelectClause QPSParser::constructTupleSelectClause() {
  parseToken(OPEN_TUPLE);
  std::vector<std::shared_ptr<Declaration>> multiSelect;

  for (bool first = true; first || isCurrentValue(TUPLE_SEP); first = false) {
    if (!first)
      parseToken(TUPLE_SEP);
    if (!isCurrentTokenValidNameWithoutSpecialChar())
      throw QPSParserException(INVALID_SELECT_CLAUSE);

    const std::string name = get().getValue();
    const auto pt = nameToFactory.find(name);

    if (pt != nameToFactory.end()) {
      if (hasNext() && isCurrentValue(ATTR_SEP)) {
        get();
        const std::string attr = parseToken(Common::TokenType::name).getValue();
        if (attrKeywords.find(attr) == attrKeywords.end())
          throw QPSParserException(INVALID_ATTR_NAME);
        multiSelect.push_back(pt->second->createDeclaration(name, attr));
      } else {
        multiSelect.push_back(pt->second->createDeclaration(name));
      }
    } else
      multiSelect.push_back(nullptr);
  }

  parseToken(CLOSE_TUPLE);
  return SelectClause(multiSelect);
}

}  // namespace QPS
