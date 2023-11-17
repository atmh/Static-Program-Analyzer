#pragma once

#include <list>
#include <memory>
#include <string>

#include "common/exception/SemanticException.h"
#include "common/exception/SyntaxException.h"
#include "pkb/PKBStorageReadInterface.h"
#include "qps/evaluator/EvaluatorFacade.h"
#include "qps/parser/QPSParser.h"
#include "qps/query/Query.h"
#include "qps/tokenizer/QPSTokenizer.h"
#include "qps/validator/Validator.h"

namespace QPS {
class QPS {
 public:
  explicit QPS(const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb);
  std::list<std::string> process(const std::string& queryString);

 private:
  EvaluatorFacade evaluator;
  std::shared_ptr<PKB::PKBStorageReadInterface>
      pkb;  // dependency injection for testing
};

}  // namespace QPS
