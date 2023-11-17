#include "sp/design_extractor/ExtractorFactory.h"

#include "sp/extractor_adapter/adapters/CallAdapter.h"
#include "sp/extractor_adapter/adapters/EntityAdapterProxy.h"
#include "sp/extractor_adapter/adapters/FollowsAdapter.h"
#include "sp/extractor_adapter/adapters/NextAdapter.h"
#include "sp/extractor_adapter/adapters/ParentAdapter.h"

namespace SP {
ExtractorFactory::ExtractorFactory(
    const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
    : pkb(pkb) {}

std::shared_ptr<DesignExtractor> ExtractorFactory::createExtractor(
    ExtractorType name) {
  switch (name) {
    case ExtractorType::FOLLOWS:
      return std::make_shared<FollowsExtractor>(FollowsAdapter{pkb});
    case ExtractorType::PARENT:
      return std::make_shared<ParentExtractor>(ParentAdapter{pkb});
    case ExtractorType::MODIFIES:
      return std::make_shared<ModifiesExtractor>(ModifiesAdapter{pkb});
    case ExtractorType::USES:
      return std::make_shared<UseExtractor>(UseAdapter{pkb});
    case ExtractorType::CALL:
      return std::make_shared<CallExtractor>(CallAdapter{pkb});
    case ExtractorType::NEXT:
      return std::make_shared<NextExtractor>(NextAdapter{pkb});
    default:
      return std::make_shared<EntityExtractor>(EntityAdapterProxy{pkb});
  }
}

std::vector<std::shared_ptr<DesignExtractor>>
ExtractorFactory::getAllExtractors() {
  std::vector<std::shared_ptr<DesignExtractor>> extractors;

  // Loop through the enum values
  for (int i = static_cast<int>(ExtractorType::CALL); i < numExtractorTypes;
       ++i) {
    ExtractorType type = static_cast<ExtractorType>(i);
    std::shared_ptr<DesignExtractor> e = createExtractor(type);
    extractors.push_back(e);
  }

  return extractors;
}
}  // namespace SP
