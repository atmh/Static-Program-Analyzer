//
// Created by Volunteer The on 7/9/23.
//
#include "catch.hpp"
#include "pkb/utils/BiDirectionalMap.h"

using namespace PKB;

TEST_CASE("Test BiDirectionalMap for <int,int>") {
  int keyOne = 1;
  int valueOne = 2;
  int invalidFirst = 3;
  int keyTwo = 4;
  int valueTwo = 5;

  BiDirectionalMap<int, int> map;

  // testing for single mapping
  map.addMapping(keyOne, valueOne);

  SECTION("test getMap") {
    // tests for single mapping

    std::unordered_map<int, std::unordered_set<int>> getMap = map.getMap();
    std::unordered_map<int, std::unordered_set<int>> expectedMap;
    std::unordered_map<int, std::unordered_set<int>> nonExpectedMap;
    expectedMap[keyOne].insert(valueOne);
    nonExpectedMap[keyOne].insert(invalidFirst);
    REQUIRE(getMap == expectedMap);
    REQUIRE_FALSE(getMap == nonExpectedMap);

    std::unordered_map<int, std::unordered_set<int>> getReverseMap =
        map.getReverseMap();
    std::unordered_map<int, std::unordered_set<int>> expectedReverseMap;
    std::unordered_map<int, std::unordered_set<int>> nonExpectedReverseMap;
    expectedReverseMap[valueOne].insert(keyOne);
    nonExpectedReverseMap[valueOne].insert({invalidFirst});
    REQUIRE(getReverseMap == expectedReverseMap);
    REQUIRE_FALSE(getReverseMap == nonExpectedReverseMap);

    // testing for multiple mappings to Key
    map.addMapping(keyOne, valueTwo);
    getMap = map.getMap();
    getReverseMap = map.getReverseMap();

    expectedMap[keyOne].insert(valueTwo);
    nonExpectedMap[keyOne].insert(invalidFirst);
    REQUIRE(getMap == expectedMap);
    REQUIRE_FALSE(getMap == nonExpectedMap);

    expectedReverseMap[valueTwo].insert(keyOne);
    nonExpectedReverseMap[valueTwo].insert(invalidFirst);
    REQUIRE(getReverseMap == expectedReverseMap);
    REQUIRE_FALSE(getReverseMap == nonExpectedReverseMap);
  }

  SECTION("Test empty") {
    BiDirectionalMap<int, int> emptyMap;

    REQUIRE(emptyMap.empty());
    emptyMap.addMapping(keyOne, valueTwo);
    REQUIRE_FALSE(emptyMap.empty());
  }

  SECTION("Test get values") {
    map.addMapping(keyOne, valueOne);
    std::unordered_set<int> values = {valueOne};
    std::unordered_set<int> nonValues = {invalidFirst};

    REQUIRE(map.getValues(keyOne) == values);
    REQUIRE_FALSE(map.getValues(keyOne) == nonValues);

    std::unordered_set<int> multipleValues = {valueOne, valueTwo};
    map.addMapping(keyOne, valueTwo);
    REQUIRE(map.getValues(keyOne) == multipleValues);
    REQUIRE_FALSE(map.getValues(keyOne) == nonValues);
  }

  SECTION("Test get keys") {
    // test single key
    map.addMapping(keyOne, valueOne);
    std::unordered_set<int> keys = {keyOne};
    std::unordered_set<int> nonKeys = {invalidFirst};
    REQUIRE(map.getKeys(valueOne) == keys);
    REQUIRE_FALSE(map.getKeys(valueOne) == nonKeys);

    // test multiple keys
    map.addMapping(keyTwo, valueOne);
    std::unordered_set<int> multipleKeys = {keyOne, keyTwo};
    REQUIRE(map.getKeys(valueOne) == multipleKeys);
    REQUIRE_FALSE(map.getKeys(valueOne) == nonKeys);
  }

  SECTION("Test hasKey") {
    map.addMapping(keyOne, valueOne);
    REQUIRE(map.hasKey(keyOne));
    REQUIRE_FALSE(map.hasKey(invalidFirst));

    map.addMapping(keyTwo, valueOne);

    REQUIRE(map.hasKey(keyTwo));
    REQUIRE_FALSE(map.hasKey(valueOne));
  }

  SECTION("Test hasValue") {
    map.addMapping(keyOne, valueOne);
    REQUIRE(map.hasValue(valueOne));
    REQUIRE_FALSE(map.hasValue(invalidFirst));
  }

  SECTION("Test hasMapping") {
    map.addMapping(keyOne, valueOne);
    REQUIRE(map.hasMapping(keyOne, valueOne));
    REQUIRE_FALSE(map.hasMapping(keyOne, invalidFirst));
    REQUIRE_FALSE(map.hasMapping(invalidFirst, valueOne));
  }

  SECTION("Test addMapping") {
    // test single key value mapping
    map.addMapping(keyOne, valueOne);
    std::unordered_map<int, std::unordered_set<int>> testMap;
    std::unordered_map<int, std::unordered_set<int>> testReverseMap;
    testMap[keyOne].insert(valueOne);
    testReverseMap[valueOne].insert(keyOne);

    REQUIRE(map.getKeys(valueOne) == testReverseMap.at(valueOne));
    REQUIRE(map.getValues(keyOne) == testMap.at(keyOne));
    REQUIRE(map.getKeys(invalidFirst).empty());

    // test multiple value to key mapping
    map.addMapping(keyOne, valueTwo);
    testMap[keyOne].insert(valueTwo);
    testReverseMap[valueTwo].insert(keyOne);
    REQUIRE(map.getKeys(valueOne) == testReverseMap.at(valueOne));
    REQUIRE(map.getKeys(valueTwo) == testReverseMap.at(valueOne));
    REQUIRE(map.getKeys(valueOne) == testReverseMap.at(valueTwo));
    REQUIRE(map.getKeys(valueTwo) == testReverseMap.at(valueTwo));
    REQUIRE(map.getKeys(invalidFirst).empty());
    REQUIRE(map.getValues(keyOne) == testMap.at(keyOne));
  }
}

TEST_CASE("Test BiDirectionalMap for <int,string>") {
  int keyOne = 1;
  std::string valueOne = "valueOne";
  int invalidKey = 3;
  std::string invalidValue = "invalid";
  int keyTwo = 2;
  std::string valueTwo = "valueTwo";

  BiDirectionalMap<int, std::string> map;

  // testing for single mapping
  map.addMapping(keyOne, valueOne);

  SECTION("test getMap") {
    // tests for single mapping

    std::unordered_map<int, std::unordered_set<std::string>> getMap =
        map.getMap();
    std::unordered_map<int, std::unordered_set<std::string>> expectedMap;
    std::unordered_map<int, std::unordered_set<std::string>> nonExpectedMap;
    expectedMap[keyOne].insert(valueOne);
    nonExpectedMap[keyOne].insert(invalidValue);
    REQUIRE(getMap == expectedMap);
    REQUIRE_FALSE(getMap == nonExpectedMap);

    std::unordered_map<std::string, std::unordered_set<int>> getReverseMap =
        map.getReverseMap();
    std::unordered_map<std::string, std::unordered_set<int>> expectedReverseMap;
    std::unordered_map<std::string, std::unordered_set<int>>
        nonExpectedReverseMap;
    expectedReverseMap[valueOne].insert(keyOne);
    nonExpectedReverseMap[valueOne].insert({invalidKey});
    REQUIRE(getReverseMap == expectedReverseMap);
    REQUIRE_FALSE(getReverseMap == nonExpectedReverseMap);

    // testing for multiple mappings to Key
    map.addMapping(keyOne, valueTwo);
    getMap = map.getMap();
    getReverseMap = map.getReverseMap();

    expectedMap[keyOne].insert(valueTwo);
    nonExpectedMap[keyOne].insert(invalidValue);
    REQUIRE(getMap == expectedMap);
    REQUIRE_FALSE(getMap == nonExpectedMap);

    expectedReverseMap[valueTwo].insert(keyOne);
    nonExpectedReverseMap[valueTwo].insert(invalidKey);
    REQUIRE(getReverseMap == expectedReverseMap);
    REQUIRE_FALSE(getReverseMap == nonExpectedReverseMap);
  }

  SECTION("Test empty") {
    BiDirectionalMap<int, std::string> emptyMap;

    REQUIRE(emptyMap.empty());
    emptyMap.addMapping(keyOne, valueTwo);
    REQUIRE_FALSE(emptyMap.empty());
  }

  SECTION("Test get values") {
    map.addMapping(keyOne, valueOne);
    std::unordered_set<std::string> values = {valueOne};
    std::unordered_set<std::string> nonValues = {invalidValue};

    REQUIRE(map.getValues(keyOne) == values);
    REQUIRE_FALSE(map.getValues(keyOne) == nonValues);

    std::unordered_set<std::string> multipleValues = {valueOne, valueTwo};
    map.addMapping(keyOne, valueTwo);
    REQUIRE(map.getValues(keyOne) == multipleValues);
    REQUIRE_FALSE(map.getValues(keyOne) == nonValues);
  }

  SECTION("Test get keys") {
    // test single key
    map.addMapping(keyOne, valueOne);
    std::unordered_set<int> keys = {keyOne};
    std::unordered_set<int> nonKeys = {invalidKey};
    REQUIRE(map.getKeys(valueOne) == keys);
    REQUIRE_FALSE(map.getKeys(valueOne) == nonKeys);

    // test multiple keys
    map.addMapping(keyTwo, valueOne);
    std::unordered_set<int> multipleKeys = {keyOne, keyTwo};
    REQUIRE(map.getKeys(valueOne) == multipleKeys);
    REQUIRE_FALSE(map.getKeys(valueOne) == nonKeys);
  }

  SECTION("Test hasKey") {
    map.addMapping(keyOne, valueOne);
    REQUIRE(map.hasKey(keyOne));
    REQUIRE_FALSE(map.hasKey(invalidKey));

    map.addMapping(keyTwo, valueOne);

    REQUIRE(map.hasKey(keyTwo));
    REQUIRE_FALSE(map.hasKey(invalidKey));
  }

  SECTION("Test hasValue") {
    map.addMapping(keyOne, valueOne);
    REQUIRE(map.hasValue(valueOne));
    REQUIRE_FALSE(map.hasValue(invalidValue));
  }

  SECTION("Test hasMapping") {
    map.addMapping(keyOne, valueOne);
    REQUIRE(map.hasMapping(keyOne, valueOne));
    REQUIRE_FALSE(map.hasMapping(keyOne, invalidValue));
    REQUIRE_FALSE(map.hasMapping(invalidKey, valueOne));
  }

  SECTION("Test addMapping") {
    // test single key value mapping
    map.addMapping(keyOne, valueOne);
    std::unordered_map<int, std::unordered_set<std::string>> testMap;
    std::unordered_map<std::string, std::unordered_set<int>> testReverseMap;
    testMap[keyOne].insert(valueOne);
    testReverseMap[valueOne].insert(keyOne);

    REQUIRE(map.getKeys(valueOne) == testReverseMap.at(valueOne));
    REQUIRE(map.getValues(keyOne) == testMap.at(keyOne));
    REQUIRE(map.getKeys(invalidValue).empty());

    // test multiple value to key mapping
    map.addMapping(keyOne, valueTwo);
    testMap[keyOne].insert(valueTwo);
    testReverseMap[valueTwo].insert(keyOne);
    REQUIRE(map.getKeys(valueOne) == testReverseMap.at(valueOne));
    REQUIRE(map.getKeys(valueTwo) == testReverseMap.at(valueOne));
    REQUIRE(map.getKeys(valueOne) == testReverseMap.at(valueTwo));
    REQUIRE(map.getKeys(valueTwo) == testReverseMap.at(valueTwo));
    REQUIRE(map.getKeys(invalidValue).empty());
    REQUIRE(map.getValues(keyOne) == testMap.at(keyOne));
  }
}
