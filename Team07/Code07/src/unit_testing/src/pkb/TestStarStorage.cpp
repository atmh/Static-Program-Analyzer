//
// Created by Ramapriyan Srivatsan PD on 8/9/23.
//
#include "catch.hpp"
#include "pkb/such_that_clause//StarStorage.h"
#include "unordered_set"

using namespace PKB;

// Test store information and getRelationships/getStarRelationships
TEST_CASE("Star Storage tests") {
  StarStorage<int> starStorage;

  SECTION("Test empty") {
    REQUIRE(starStorage.starEmpty());
    starStorage.storeInformation(1, 2);
    REQUIRE_FALSE(starStorage.starEmpty());
  }

  SECTION("StarStorage store information normal relationship test simple int") {
    starStorage.storeInformation(1, 2);
    std::unordered_set<int> testRelationship = {2};
    std::unordered_set<int> reverseTestRelationship = {1};
    REQUIRE(starStorage.getFirstArgRelationships(1) == testRelationship);
    REQUIRE(starStorage.getSecondArgRelationships(2) ==
            reverseTestRelationship);
  }

  SECTION("StarStorage store information star relationship test simple int") {
    starStorage.storeInformation(1, 2);
    std::unordered_set<int> testRelationship = {2};
    std::unordered_set<int> reverseTestRelationship = {1};
    REQUIRE(starStorage.getFirstArgStarRelationships(1) == testRelationship);
    REQUIRE(starStorage.getSecondArgStarRelationships(2) ==
            reverseTestRelationship);
  }

  SECTION(
      "StarStorage store information normal relationship test complex int") {
    starStorage.storeInformation(1, 2);
    starStorage.storeInformation(2, 3);
    starStorage.storeInformation(3, 4);
    std::unordered_set<int> testRelationshipOne = {2};
    std::unordered_set<int> reverseTestRelationshipFour = {3};
    REQUIRE(starStorage.getFirstArgRelationships(1) == testRelationshipOne);
    REQUIRE(starStorage.getSecondArgRelationships(4) ==
            reverseTestRelationshipFour);
  }

  SECTION(
      "StarStorage store information normal relationship arg does not exist "
      "test complex int") {
    starStorage.storeInformation(1, 2);
    starStorage.storeInformation(2, 3);
    starStorage.storeInformation(3, 4);
    std::unordered_set<int> testRelationshipEmpty = {};
    REQUIRE(starStorage.getFirstArgRelationships(20) == testRelationshipEmpty);
    REQUIRE(starStorage.getSecondArgRelationships(17) == testRelationshipEmpty);
  }

  SECTION("StarStorage store information star relationship test complex int") {
    starStorage.storeInformation(1, 2);
    starStorage.storeInformation(2, 3);
    starStorage.storeInformation(3, 4);
    std::unordered_set<int> testRelationshipOne = {2, 3, 4};
    std::unordered_set<int> reverseTestRelationshipFour = {3, 2, 1};
    REQUIRE(starStorage.getFirstArgStarRelationships(1) == testRelationshipOne);
    REQUIRE(starStorage.getSecondArgStarRelationships(4) ==
            reverseTestRelationshipFour);
  }

  SECTION(
      "StarStorage store information star relationship arg does not exist test "
      "complex int") {
    starStorage.storeInformation(1, 2);
    starStorage.storeInformation(2, 3);
    starStorage.storeInformation(3, 4);
    std::unordered_set<int> testRelationshipEmpty = {};
    REQUIRE(starStorage.getFirstArgStarRelationships(20) ==
            testRelationshipEmpty);
    REQUIRE(starStorage.getSecondArgStarRelationships(17) ==
            testRelationshipEmpty);
  }

  // Test getRelationshipExists
  SECTION("StarStorage getStarRelationshipExists test complex int") {
    starStorage.storeInformation(1, 2);
    starStorage.storeInformation(2, 3);
    starStorage.storeInformation(3, 4);
    starStorage.storeInformation(5, 7);

    REQUIRE(starStorage.getStarRelationshipExists(1, 2));
    REQUIRE(starStorage.getStarRelationshipExists(2, 3));
    REQUIRE(starStorage.getStarRelationshipExists(3, 4));
    REQUIRE(starStorage.getStarRelationshipExists(2, 4));
    REQUIRE(starStorage.getStarRelationshipExists(1, 4));

    // test relationships not inserted in order
    starStorage.storeInformation(100, 103);
    starStorage.storeInformation(101, 102);
    starStorage.storeInformation(107, 109);
    starStorage.storeInformation(102, 105);
    starStorage.storeInformation(7, 101);
    REQUIRE(starStorage.getStarRelationshipExists(5, 105));

    REQUIRE_FALSE(starStorage.getStarRelationshipExists(1, 7));
  }

  SECTION(
      "StarStorage getStarRelationshipExists entity does not exist test "
      "complex int") {
    starStorage.storeInformation(1, 2);
    starStorage.storeInformation(2, 4);
    starStorage.storeInformation(5, 7);

    REQUIRE_FALSE(starStorage.getStarRelationshipExists(8, 17));
    REQUIRE_FALSE(starStorage.getStarRelationshipExists(1, 10));
  }

  SECTION(
      "StarStorage getStarRelationshipExists entity middle relationship "
      "addition test simple int") {
    starStorage.storeInformation(1, 2);
    starStorage.storeInformation(3, 4);
    starStorage.storeInformation(2, 3);
    starStorage.storeInformation(5, 6);

    REQUIRE(starStorage.getStarRelationshipExists(1, 4));
    REQUIRE_FALSE(starStorage.getStarRelationshipExists(1, 5));
  }

  SECTION(
      "StarStorage getStarRelationshipExists entity middle relationship "
      "addition test complex int") {
    starStorage.storeInformation(1, 2);
    starStorage.storeInformation(3, 4);
    starStorage.storeInformation(2, 3);
    starStorage.storeInformation(5, 6);
    starStorage.storeInformation(6, 7);
    starStorage.storeInformation(4, 5);

    REQUIRE(starStorage.getStarRelationshipExists(1, 7));
    REQUIRE_FALSE(starStorage.getStarRelationshipExists(4, 3));
  }
}
