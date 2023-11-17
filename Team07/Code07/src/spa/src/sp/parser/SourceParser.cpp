#include "SourceParser.h"

namespace SP {

constexpr auto PROCEDURE = "procedure";
constexpr auto READ = "read";
constexpr auto PRINT = "print";
constexpr auto CALL = "call";
constexpr auto WHILE = "while";
constexpr auto IF = "if";
constexpr auto ASSIGN = "=";
constexpr auto THEN = "then";
constexpr auto ELSE = "else";
constexpr auto STMTLST_START = "{";
constexpr auto STMTLST_END = "}";
constexpr auto OPEN_BRACKET = "(";
constexpr auto CLOSED_BRACKET = ")";
constexpr auto STMT_END = ";";

SourceParser::SourceParser(std::vector<Common::Token> tokens)
    : Parser(std::move(tokens)) {}

std::shared_ptr<ProgramNode> SourceParser::getRoot() {
  return this->root;
}

int SourceParser::getStmtNo() {
  return stmtNo++;
}

void SourceParser::parse() {
  root = parseProgram();
}

std::shared_ptr<ProgramNode> SourceParser::parseProgram() {
  std::vector<std::shared_ptr<Node>> procedureNodes;

  while (hasNext()) {
    auto procedureNode = parseProcedure();
    procedureNodes.emplace_back(procedureNode);
  }

  if (procedureNodes.empty()) {  // empty input
    throw SourceParserException(PARSER_NO_INPUT);
  }

  return std::make_shared<ProgramNode>(procedureNodes);
}

std::shared_ptr<ProcedureNode> SourceParser::parseProcedure() {
  std::vector<std::shared_ptr<Node>> stmtLstNode;

  parseToken(PROCEDURE);
  std::string procedureName = parseToken(Common::TokenType::name).getValue();

  stmtLstNode.emplace_back(parseStmtLst());

  return std::make_shared<ProcedureNode>(procedureName, stmtLstNode);
}

std::shared_ptr<StmtLstNode> SourceParser::parseStmtLst() {
  std::vector<std::shared_ptr<Node>> stmtNodes;

  parseToken(STMTLST_START);

  while (!isCurrentValue(STMTLST_END)) {  // in statement list body
    stmtNodes.emplace_back(parseStmt());
  }

  if (stmtNodes.empty()) {  // must have at least 1 statement
    throw SourceParserException(PARSER_NO_STMT);
  }

  parseToken(STMTLST_END);
  return std::make_shared<StmtLstNode>(stmtNodes);
}

std::shared_ptr<StmtNode> SourceParser::parseStmt() {
  if (!isCurrentType(
          Common::TokenType::name)) {  // must start with a name token
    throw SourceParserException(PARSER_INVALID_STMT_START);
  }

  std::string name = parseToken(Common::TokenType::name).getValue();

  if (isCurrentValue(ASSIGN)) {
    return parseAssign(name);
  } else if (name == READ) {
    return parseRead();
  } else if (name == PRINT) {
    return parsePrint();
  } else if (name == CALL) {
    return parseCall();
  } else if (name == WHILE) {
    return parseWhile();
  } else if (name == IF) {
    return parseIf();
  } else {
    throw SourceParserException(PARSER_INVALID_STMT_ENTITY);  // invalid entity
  }
}

std::string SourceParser::parseNameStmtEnd() {
  std::string name = parseToken(Common::TokenType::name).getValue();
  parseToken(STMT_END);
  return name;
};

std::shared_ptr<ReadNode> SourceParser::parseRead() {
  return std::make_shared<ReadNode>(getStmtNo(), parseNameStmtEnd());
}

std::shared_ptr<PrintNode> SourceParser::parsePrint() {
  return std::make_shared<PrintNode>(getStmtNo(), parseNameStmtEnd());
}

std::shared_ptr<CallNode> SourceParser::parseCall() {
  return std::make_shared<CallNode>(getStmtNo(), parseNameStmtEnd());
}

std::shared_ptr<WhileNode> SourceParser::parseWhile() {
  parseToken(OPEN_BRACKET);

  // get condtional expression
  std::vector<Common::Token> exprs;
  while (!isCurrentValue(STMTLST_START)) {
    exprs.emplace_back(get());
  }

  if (exprs.empty() || exprs[exprs.size() - 1].getValue() != CLOSED_BRACKET) {
    // must have at least 1 expression and end with a closed bracket
    throw SourceParserException(PARSER_INVALID_CONDITIONAL);
  }
  exprs.pop_back();  // remove closed bracket of condtional expression

  std::shared_ptr<std::unordered_set<std::string>> var =
      std::make_shared<std::unordered_set<std::string>>();
  std::shared_ptr<std::unordered_set<std::string>> con =
      std::make_shared<std::unordered_set<std::string>>();
  Common::ShuntingYard::evalCond(exprs, var, con);

  int stmtNo = getStmtNo();
  std::shared_ptr<StmtLstNode> stmtLstNode = parseStmtLst();

  return std::make_shared<WhileNode>(stmtNo, *var, *con, stmtLstNode);
}

std::shared_ptr<IfNode> SourceParser::parseIf() {
  parseToken(OPEN_BRACKET);

  // get condtional expression
  std::vector<Common::Token> exprs;
  while (!isCurrentValue(STMTLST_START)) {
    exprs.emplace_back(get());
  }

  if (exprs.size() < 2 || exprs[exprs.size() - 1].getValue() != THEN ||
      exprs[exprs.size() - 2].getValue() != CLOSED_BRACKET) {
    throw SourceParserException(PARSER_INVALID_CONDITIONAL);
  }
  exprs.pop_back();
  exprs.pop_back();

  std::shared_ptr<std::unordered_set<std::string>> var =
      std::make_shared<std::unordered_set<std::string>>();
  std::shared_ptr<std::unordered_set<std::string>> con =
      std::make_shared<std::unordered_set<std::string>>();
  Common::ShuntingYard::evalCond(exprs, var, con);

  int stmtNo = getStmtNo();

  std::shared_ptr<StmtLstNode> thenStmtLstNode = parseStmtLst();

  parseToken(ELSE);
  std::shared_ptr<StmtLstNode> elseStmtLstNode = parseStmtLst();

  return std::make_shared<IfNode>(stmtNo, *var, *con, thenStmtLstNode,
                                  elseStmtLstNode);
}

std::shared_ptr<AssignNode> SourceParser::parseAssign(std::string name) {
  std::vector<Common::Token> exprs;

  // get RHS of assign
  parseToken(ASSIGN);
  while (!isCurrentValue(STMT_END)) {
    exprs.emplace_back(get());
  }
  parseToken(STMT_END);

  if (exprs.empty()) {  // must have at least 1 expression
    throw SourceParserException(PARSER_NO_ASSIGN_RHS);
  }

  std::shared_ptr<std::unordered_set<std::string>> var =
      std::make_shared<std::unordered_set<std::string>>();
  std::shared_ptr<std::unordered_set<std::string>> con =
      std::make_shared<std::unordered_set<std::string>>();
  std::vector<std::string> postfix =
      Common::ShuntingYard::evalMath(exprs, var, con);

  return std::make_shared<AssignNode>(getStmtNo(), name, *var, *con, postfix);
}

}  // namespace SP
