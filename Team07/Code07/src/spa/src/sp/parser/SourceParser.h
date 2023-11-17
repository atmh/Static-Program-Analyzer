#pragma once

#include "common/algorithm/ShuntingYard.h"
#include "common/parser/Parser.h"
#include "sp/exception/Messages.h"
#include "sp/exception/SourceParserException.h"
#include "sp/node/ProcedureNode.h"
#include "sp/node/ProgramNode.h"
#include "sp/node/StmtLstNode.h"
#include "sp/node/stmt_nodes/AssignNode.h"
#include "sp/node/stmt_nodes/CallNode.h"
#include "sp/node/stmt_nodes/IfNode.h"
#include "sp/node/stmt_nodes/PrintNode.h"
#include "sp/node/stmt_nodes/ReadNode.h"
#include "sp/node/stmt_nodes/WhileNode.h"

namespace SP {

class SourceParser : public Common::Parser {
 private:
  int stmtNo = 1;
  std::shared_ptr<ProgramNode> root;

  int getStmtNo();
  std::string parseNameStmtEnd();
  std::shared_ptr<ProgramNode> parseProgram();
  std::shared_ptr<ProcedureNode> parseProcedure();
  std::shared_ptr<StmtLstNode> parseStmtLst();
  std::shared_ptr<StmtNode> parseStmt();
  std::shared_ptr<ReadNode> parseRead();
  std::shared_ptr<PrintNode> parsePrint();
  std::shared_ptr<CallNode> parseCall();
  std::shared_ptr<WhileNode> parseWhile();
  std::shared_ptr<IfNode> parseIf();
  std::shared_ptr<AssignNode> parseAssign(std::string name);

 public:
  SourceParser(std::vector<Common::Token> tokens);

  std::shared_ptr<ProgramNode> getRoot();
  void parse() override;
};

}  // namespace SP
