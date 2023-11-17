#include "catch.hpp"
#include "sp/design_extractor/ExtractorFactory.h"
#include "stubs/pkb/PKBStorageWriteAPI.h"

using namespace SP;

bool contains(std::vector<std::shared_ptr<DesignExtractor>> extractors,
              DesignExtractor& extractor) {
  for (const auto& e : extractors) {
    if (e && typeid(*e) == typeid(extractor)) {
      return true;
    }
  }
  return false;
};

class DummyExtractor : public DesignExtractor {
 public:
  DummyExtractor() : DesignExtractor() {}
  void sendDataToAdapter() override { return; }
};

TEST_CASE("Get All Extractors") {
  std::shared_ptr<PKB::PKBStorageWriteInterface> pkb =
      std::make_shared<PKB::PKBStorageWriteStub>();
  ExtractorFactory factory{pkb};
  std::vector<std::shared_ptr<DesignExtractor>> extractors =
      factory.getAllExtractors();
  std::shared_ptr<DesignExtractor> follows =
      factory.createExtractor(ExtractorFactory::ExtractorType::FOLLOWS);
  std::shared_ptr<DesignExtractor> parent =
      factory.createExtractor(ExtractorFactory::ExtractorType::PARENT);
  std::shared_ptr<DesignExtractor> entity =
      factory.createExtractor(ExtractorFactory::ExtractorType::ENTITY);
  std::shared_ptr<DesignExtractor> modifies =
      factory.createExtractor(ExtractorFactory::ExtractorType::MODIFIES);
  std::shared_ptr<DesignExtractor> uses =
      factory.createExtractor(ExtractorFactory::ExtractorType::USES);
  std::shared_ptr<DesignExtractor> call =
      factory.createExtractor(ExtractorFactory::ExtractorType::CALL);
  std::shared_ptr<DesignExtractor> next =
      factory.createExtractor(ExtractorFactory::ExtractorType::NEXT);

  std::shared_ptr<DesignExtractor> dummy = std::make_shared<DummyExtractor>();

  SECTION("Check the number of extractors") {
    REQUIRE(extractors.size() == factory.numExtractorTypes);
  }

  SECTION("Verify presence of Entity Extractor") {
    REQUIRE(contains(extractors, *entity));
  }

  SECTION("Verify presence of Parent Extractor") {
    REQUIRE(contains(extractors, *parent));
  }

  SECTION("Verify presence of Follows Extractor") {
    REQUIRE(contains(extractors, *follows));
  }

  SECTION("Verify presence of Modifies Extractor") {
    REQUIRE(contains(extractors, *modifies));
  }

  SECTION("Verify presence of Uses Extractor") {
    REQUIRE(contains(extractors, *uses));
  }

  SECTION("Verify presence of Call Extractor") {
    REQUIRE(contains(extractors, *call));
  }

  SECTION("Verify presence of Next Extractor") {
    REQUIRE(contains(extractors, *next));
  }

  SECTION("Verify absence of Dummy Extractor") {
    REQUIRE(!contains(extractors, *dummy));
  }
}

TEST_CASE("Test extractor creator") {
  std::shared_ptr<PKB::PKBStorageWriteInterface> pkb =
      std::make_shared<PKB::PKBStorageWriteStub>();
  ExtractorFactory factory{pkb};
  std::shared_ptr<DesignExtractor> follows =
      factory.createExtractor(ExtractorFactory::ExtractorType::FOLLOWS);
  std::shared_ptr<DesignExtractor> parent =
      factory.createExtractor(ExtractorFactory::ExtractorType::PARENT);
  std::shared_ptr<DesignExtractor> entity =
      factory.createExtractor(ExtractorFactory::ExtractorType::ENTITY);
  std::shared_ptr<DesignExtractor> modifies =
      factory.createExtractor(ExtractorFactory::ExtractorType::MODIFIES);
  std::shared_ptr<DesignExtractor> uses =
      factory.createExtractor(ExtractorFactory::ExtractorType::USES);
  std::shared_ptr<DesignExtractor> call =
      factory.createExtractor(ExtractorFactory::ExtractorType::CALL);
  std::shared_ptr<DesignExtractor> next =
      factory.createExtractor(ExtractorFactory::ExtractorType::NEXT);

  std::shared_ptr<DesignExtractor> dummy = std::make_shared<DummyExtractor>();

  SECTION("Verify creation of Entity Extractor") {
    REQUIRE(typeid(*entity) == typeid(EntityExtractor));
  }

  SECTION("Verify creation of Parent Extractor") {
    REQUIRE(typeid(*parent) == typeid(ParentExtractor));
  }

  SECTION("Verify creation of Follows Extractor") {
    REQUIRE(typeid(*follows) == typeid(FollowsExtractor));
  }

  SECTION("Verify creation of Modifies Extractor") {
    REQUIRE(typeid(*modifies) == typeid(ModifiesExtractor));
  }

  SECTION("Verify creation of Uses Extractor") {
    REQUIRE(typeid(*uses) == typeid(UseExtractor));
  }

  SECTION("Verify creation of Call Extractor") {
    REQUIRE(typeid(*call) == typeid(CallExtractor));
  }

  SECTION("Verify creation of Next Extractor") {
    REQUIRE(typeid(*next) == typeid(NextExtractor));
  }
}
