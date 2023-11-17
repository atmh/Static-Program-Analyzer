#pragma once

#include "qps/query/declaration/AssignDeclaration.h"
#include "qps/query/declaration/CallDeclaration.h"
#include "qps/query/declaration/ConstantDeclaration.h"
#include "qps/query/declaration/IfDeclaration.h"
#include "qps/query/declaration/PrintDeclaration.h"
#include "qps/query/declaration/ProcedureDeclaration.h"
#include "qps/query/declaration/ReadDeclaration.h"
#include "qps/query/declaration/StatementDeclaration.h"
#include "qps/query/declaration/VariableDeclaration.h"
#include "qps/query/declaration/WhileDeclaration.h"

namespace QPS {

class DeclarationVisitor {
 public:
  virtual void visit(const AssignDeclaration& assign) = 0;
  virtual void visit(const CallDeclaration& call) = 0;
  virtual void visit(const ConstantDeclaration& constant) = 0;
  virtual void visit(const IfDeclaration& ifDeclaration) = 0;
  virtual void visit(const PrintDeclaration& print) = 0;
  virtual void visit(const ProcedureDeclaration& procedure) = 0;
  virtual void visit(const ReadDeclaration& read) = 0;
  virtual void visit(const StatementDeclaration& stmt) = 0;
  virtual void visit(const VariableDeclaration& variable) = 0;
  virtual void visit(const WhileDeclaration& whileDeclaration) = 0;

  virtual ~DeclarationVisitor() = 0;
};

}  // namespace QPS
