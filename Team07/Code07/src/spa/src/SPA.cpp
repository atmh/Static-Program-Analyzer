#include "SPA.h"

#include <memory>

#include "pkb/PKBStorageReadInterface.h"
#include "qps/QPS.h"

namespace SPA {

void SPA::process(const std::string& filename) {
  // pkb pointer needs to be passed to sp manager for dependency injection.
  // require pointer because polymorphic
  SP::SPManager sp{pkbStorageAPI->getWriteStorage()};
  sp.process(filename);
}

void SPA::evaluate(std::string query, std::list<std::string>& results) {
  QPS::QPS qps{pkbStorageAPI->getReadStorage()};
  results = qps.process(query);
}

}  // namespace SPA
