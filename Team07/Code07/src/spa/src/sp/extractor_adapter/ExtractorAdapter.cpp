#include "sp/extractor_adapter/ExtractorAdapter.h"

namespace SP {
ExtractorAdapter::ExtractorAdapter(
    const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
    : pkb(pkb) {}
}  // namespace SP
