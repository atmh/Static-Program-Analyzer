#include "catch.hpp"
#include "sp/design_extractor/ExtractorFactory.h"
#include "sp/design_extractor/ExtractorManager.h"
#include "stubs/pkb/PKBStorageWriteAPI.h"

using namespace SP;

class ExtractorFactoryStub : public ExtractorFactory {
 public:
  ExtractorFactoryStub(
      const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
      : ExtractorFactory(pkb) {}
};

TEST_CASE("Test Extractor Manager") {
  SECTION("Nullptr ProgramNode") {
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkb =
        std::make_shared<PKB::PKBStorageWriteStub>();

    ExtractorFactoryStub factory{pkb};
    ExtractorManager manager{factory};

    REQUIRE_NOTHROW(manager.extract(nullptr));
  }
}
