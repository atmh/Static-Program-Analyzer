#pragma once
#include <memory>
#include <string>
#include <vector>

#include "sp/design_extractor/DesignExtractor.h"
#include "sp/design_extractor/extractors/CallExtractor.h"
#include "sp/design_extractor/extractors/EntityExtractor.h"
#include "sp/design_extractor/extractors/FollowsExtractor.h"
#include "sp/design_extractor/extractors/ModifiesExtractor.h"
#include "sp/design_extractor/extractors/NextExtractor.h"
#include "sp/design_extractor/extractors/ParentExtractor.h"
#include "sp/design_extractor/extractors/UseExtractor.h"

namespace SP {
class ExtractorFactory {
 public:
  int numExtractorTypes = 7;
  enum class ExtractorType {
    CALL = 0,
    ENTITY = 1,
    PARENT = 2,
    MODIFIES = 3,
    USES = 4,
    FOLLOWS = 5,
    NEXT = 6
  };

  ExtractorFactory(const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb);
  std::vector<std::shared_ptr<DesignExtractor>> getAllExtractors();
  std::shared_ptr<DesignExtractor> createExtractor(ExtractorType name);

 private:
  std::shared_ptr<PKB::PKBStorageWriteInterface> pkb;
};
}  // namespace SP
