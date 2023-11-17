#include "QPS.h"

namespace QPS {

QPS::QPS(const std::shared_ptr<PKB::PKBStorageReadInterface>& pkb) : pkb(pkb) {}

std::list<std::string> QPS::process(const std::string& queryString) {
  try {
    QPSParser parser = QPSParser(QPSTokenizer(queryString).tokenize());
    parser.parse();
    Query query = parser.getQuery();
    Validator validator(query, parser.getDeclaredNames());
    validator.validate();
    return evaluator.evaluate(pkb, query);
  } catch (const Common::SyntaxException& e) {
    return {"SyntaxError"};
  } catch (const Common::SemanticException& e) {
    return {"SemanticError"};
  }
}

}  // namespace QPS
