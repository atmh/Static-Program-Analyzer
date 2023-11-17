#include "Validator.h"

#include <string>
#include <unordered_set>

#include "qps/exception/Messages.h"
#include "qps/exception/QPSValidatorException.h"

namespace QPS {
Validator::Validator(const QPS::Query& q,
                     std::vector<std::string> declaredNames)
    : q(q), declaredNames(std::move(declaredNames)) {}

bool Validator::validate() {
  if (std::unordered_set<std::string>(declaredNames.begin(),
                                      declaredNames.end())
          .size() != declaredNames.size()) {
    throw QPSValidatorException(REPEATED_DECLARATION);
  }

  if (!q.validate())
    throw QPSValidatorException(INVALID_CLAUSE);

  return true;
}

}  // namespace QPS