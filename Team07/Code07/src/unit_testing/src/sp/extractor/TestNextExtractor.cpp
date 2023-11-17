#include <iostream>

#include "catch.hpp"
#include "sp/design_extractor/DesignExtractor.h"
#include "sp/design_extractor/extractors/NextExtractor.h"
#include "sp/extractor_adapter/adapters/NextAdapter.h"
#include "sp/helper.h"
#include "sp/node/Node.h"
#include "sp/node/StmtLstNode.h"
#include "sp/node/stmt_nodes/ReadNode.h"
#include "stubs/pkb/PKBStorageWriteAPI.h"

using namespace SP;

class NextAdapterStub : public NextAdapter {
 public:
  NextAdapterStub(const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
      : NextAdapter(pkb) {}
};

inline void dfs(const std::shared_ptr<Node>& node,
                const std::shared_ptr<DesignExtractor>& extractor) {
  if (node == nullptr)
    return;

  node->accept(*extractor);
  for (const auto& child : node->getChildren()) {
    dfs(child, extractor);
  }
  node->accept(*extractor);
}

inline void testNextExtractor(
    const std::shared_ptr<StmtLstNode>& stmtLst,
    std::unordered_map<int, std::unordered_set<int>> expected) {
  std::shared_ptr<PKB::PKBStorageWriteInterface> pkb =
      std::make_shared<PKB::PKBStorageWriteStub>();
  NextAdapterStub adapter{pkb};
  std::shared_ptr<NextExtractor> nextExtractor =
      std::make_shared<NextExtractor>(adapter);
  dfs(stmtLst, nextExtractor);

  std::unordered_map<int, std::unordered_set<int>> result;
  for (const auto& [s1, s2] : nextExtractor->getStorage()) {
    std::shared_ptr<StmtNode> stmt1 = std::dynamic_pointer_cast<StmtNode>(s1);
    std::shared_ptr<StmtNode> stmt2 = std::dynamic_pointer_cast<StmtNode>(s2);
    result[stmt1->stmtNo].insert(stmt2->stmtNo);
  }

  REQUIRE(result == expected);
}

inline std::vector<std::shared_ptr<Node>> convertToNodeVec(
    const std::vector<std::shared_ptr<ReadNode>> reads) {
  std::vector<std::shared_ptr<Node>> result{};
  for (const auto& read : reads) {
    result.push_back(read);
  }
  return result;
}

TEST_CASE("Test NextExtractor") {
  SECTION("1 -> 2 -> 3") {
    std::vector<std::shared_ptr<ReadNode>> readNodes =
        makeNodes<ReadNode>({1, 2, 3}, {"a", "b", "c"});
    std::shared_ptr<StmtLstNode> stmtLst =
        std::make_shared<StmtLstNode>(convertToNodeVec(readNodes));
    std::unordered_map<int, std::unordered_set<int>> expected{{1, {2}},
                                                              {2, {3}}};
    testNextExtractor(stmtLst, expected);
  }

  SECTION("1 -> 2 -> 3 -> 4 -> 5 -> 2 -> 6") {
    std::vector<std::shared_ptr<ReadNode>> outerStmts =
        makeNodes<ReadNode>({1, 6}, {"a", "b"});
    std::vector<std::shared_ptr<ReadNode>> innerWhileStmts =
        makeNodes<ReadNode>({3, 4, 5}, {"a", "b", "c"});

    std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(
        2, std::unordered_set<std::string>{}, std::unordered_set<std::string>{},
        std::make_shared<StmtLstNode>(convertToNodeVec(innerWhileStmts)));

    std::vector<std::shared_ptr<Node>> children{outerStmts[0], whileNode,
                                                outerStmts[1]};
    std::shared_ptr<StmtLstNode> stmtLst =
        std::make_shared<StmtLstNode>(children);
    std::unordered_map<int, std::unordered_set<int>> expected{
        {1, {2}}, {2, {3, 6}}, {3, {4}}, {4, {5}}, {5, {2}}};
    testNextExtractor(stmtLst, expected);
  }

  SECTION("1 -> 2 -> 3 -> 4, 2 -> 5 -> 6, 4 -> 7, 6 -> 7") {
    std::vector<std::shared_ptr<ReadNode>> outerStmts =
        makeNodes<ReadNode>({1, 7}, {"a", "b"});
    std::vector<std::shared_ptr<ReadNode>> innerIfThenStmts =
        makeNodes<ReadNode>({3, 4}, {"a", "b"});

    std::vector<std::shared_ptr<ReadNode>> innerIfElseStmts =
        makeNodes<ReadNode>({5, 6}, {"a", "b"});

    std::shared_ptr<StmtLstNode> thenStmtLst =
        std::make_shared<StmtLstNode>(convertToNodeVec(innerIfThenStmts));

    std::shared_ptr<StmtLstNode> elseStmtLst =
        std::make_shared<StmtLstNode>(convertToNodeVec(innerIfElseStmts));

    std::shared_ptr<IfNode> ifNode = std::make_shared<IfNode>(
        2, std::unordered_set<std::string>{}, std::unordered_set<std::string>{},
        thenStmtLst, elseStmtLst);
    std::vector<std::shared_ptr<Node>> children{outerStmts[0], ifNode,
                                                outerStmts[1]};
    std::shared_ptr<StmtLstNode> stmtLst =
        std::make_shared<StmtLstNode>(children);
    std::unordered_map<int, std::unordered_set<int>> expected{
        {1, {2}}, {2, {3, 5}}, {3, {4}}, {5, {6}}, {4, {7}}, {6, {7}}};
    testNextExtractor(stmtLst, expected);
  }

  SECTION(
      "1 -> 2 -> 3 -> 4, 2 -> 5 -> 6, 4 -> 7, 6 -> 7 -> 8 -> 9 -> 7 -> 10") {
    std::vector<std::shared_ptr<ReadNode>> outerStmts =
        makeNodes<ReadNode>({1, 10}, {"a", "b"});
    std::vector<std::shared_ptr<ReadNode>> innerIfThenStmts =
        makeNodes<ReadNode>({3, 4}, {"a", "b"});

    std::vector<std::shared_ptr<ReadNode>> innerIfElseStmts =
        makeNodes<ReadNode>({5, 6}, {"a", "b"});

    std::vector<std::shared_ptr<ReadNode>> innerWhileStmts =
        makeNodes<ReadNode>({8, 9}, {"a", "b"});

    std::shared_ptr<StmtLstNode> thenStmtLst =
        std::make_shared<StmtLstNode>(convertToNodeVec(innerIfThenStmts));

    std::shared_ptr<StmtLstNode> elseStmtLst =
        std::make_shared<StmtLstNode>(convertToNodeVec(innerIfElseStmts));

    std::shared_ptr<IfNode> ifNode = std::make_shared<IfNode>(
        2, std::unordered_set<std::string>{}, std::unordered_set<std::string>{},
        thenStmtLst, elseStmtLst);

    std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(
        7, std::unordered_set<std::string>{}, std::unordered_set<std::string>{},
        std::make_shared<StmtLstNode>(convertToNodeVec(innerWhileStmts)));

    std::vector<std::shared_ptr<Node>> children{outerStmts[0], ifNode,
                                                whileNode, outerStmts[1]};
    std::shared_ptr<StmtLstNode> stmtLst =
        std::make_shared<StmtLstNode>(children);
    std::unordered_map<int, std::unordered_set<int>> expected{
        {1, {2}}, {2, {3, 5}},  {3, {4}}, {5, {6}}, {4, {7}},
        {6, {7}}, {7, {8, 10}}, {8, {9}}, {9, {7}}};
    testNextExtractor(stmtLst, expected);
  }

  SECTION("nested if in while: 1 -> 2 -> 3 -> 4 -> 3, 2 -> 6, 3 -> 7, 6 -> 7") {
    std::vector<std::shared_ptr<ReadNode>> outerStmts =
        makeNodes<ReadNode>({1, 7}, {"a", "b"});

    std::vector<std::shared_ptr<ReadNode>> innerBlockStmts =
        makeNodes<ReadNode>({4, 6}, {"a", "b"});

    std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(
        3, std::unordered_set<std::string>{}, std::unordered_set<std::string>{},
        std::make_shared<StmtLstNode>(
            std::vector<std::shared_ptr<Node>>{innerBlockStmts[0]}));

    std::shared_ptr<StmtLstNode> thenStmtLst = std::make_shared<StmtLstNode>(
        std::vector<std::shared_ptr<Node>>{whileNode});

    std::shared_ptr<StmtLstNode> elseStmtLst = std::make_shared<StmtLstNode>(
        std::vector<std::shared_ptr<Node>>{innerBlockStmts[1]});

    std::shared_ptr<IfNode> ifNode = std::make_shared<IfNode>(
        2, std::unordered_set<std::string>{}, std::unordered_set<std::string>{},
        thenStmtLst, elseStmtLst);
    std::vector<std::shared_ptr<Node>> children{outerStmts[0], ifNode,
                                                outerStmts[1]};
    std::shared_ptr<StmtLstNode> stmtLst =
        std::make_shared<StmtLstNode>(children);
    std::unordered_map<int, std::unordered_set<int>> expected{
        {1, {2}}, {2, {3, 6}}, {3, {4, 7}}, {4, {3}}, {6, {7}}};
    testNextExtractor(stmtLst, expected);
  }

  SECTION("No stmt after if: 1 -> 2 -> 3 -> 4 -> 3, 2 -> 6") {
    std::vector<std::shared_ptr<ReadNode>> outerStmts =
        makeNodes<ReadNode>({1}, {"a"});

    std::vector<std::shared_ptr<ReadNode>> innerBlockStmts =
        makeNodes<ReadNode>({4, 6}, {"a", "b"});

    std::shared_ptr<WhileNode> whileNode = std::make_shared<WhileNode>(
        3, std::unordered_set<std::string>{}, std::unordered_set<std::string>{},
        std::make_shared<StmtLstNode>(
            std::vector<std::shared_ptr<Node>>{innerBlockStmts[0]}));

    std::shared_ptr<StmtLstNode> thenStmtLst = std::make_shared<StmtLstNode>(
        std::vector<std::shared_ptr<Node>>{whileNode});

    std::shared_ptr<StmtLstNode> elseStmtLst = std::make_shared<StmtLstNode>(
        std::vector<std::shared_ptr<Node>>{innerBlockStmts[1]});

    std::shared_ptr<IfNode> ifNode = std::make_shared<IfNode>(
        2, std::unordered_set<std::string>{}, std::unordered_set<std::string>{},
        thenStmtLst, elseStmtLst);
    std::vector<std::shared_ptr<Node>> children{outerStmts[0], ifNode};
    std::shared_ptr<StmtLstNode> stmtLst =
        std::make_shared<StmtLstNode>(children);
    std::unordered_map<int, std::unordered_set<int>> expected{
        {1, {2}}, {2, {3, 6}}, {3, {4}}, {4, {3}}};
    testNextExtractor(stmtLst, expected);
  }

  SECTION(
      "Multiple nesting of if and while: 1 -> 3 -> 4 -> 5 -> 4 -> 6 -> 3,  1 "
      "-> 7 -> 8, 7 -> 9, 9 -> 10, 9 -> 11") {
    std::vector<std::shared_ptr<ReadNode>> stmts =
        makeNodes<ReadNode>({5, 6, 8, 10, 11}, {"a", "b", "a", "b", "c"});

    // making while nodes
    std::shared_ptr<WhileNode> innerWhile = std::make_shared<WhileNode>(
        4, std::unordered_set<std::string>{}, std::unordered_set<std::string>{},
        std::make_shared<StmtLstNode>(
            std::vector<std::shared_ptr<Node>>{stmts[0]}));

    std::shared_ptr<WhileNode> outerWhile = std::make_shared<WhileNode>(
        3, std::unordered_set<std::string>{}, std::unordered_set<std::string>{},
        std::make_shared<StmtLstNode>(
            std::vector<std::shared_ptr<Node>>{innerWhile, stmts[1]}));

    std::shared_ptr<IfNode> ifNode1 = std::make_shared<IfNode>(
        9, std::unordered_set<std::string>{}, std::unordered_set<std::string>{},
        std::make_shared<StmtLstNode>(
            std::vector<std::shared_ptr<Node>>{stmts[3]}),
        std::make_shared<StmtLstNode>(
            std::vector<std::shared_ptr<Node>>{stmts[4]}));

    std::shared_ptr<IfNode> ifNode2 = std::make_shared<IfNode>(
        7, std::unordered_set<std::string>{}, std::unordered_set<std::string>{},
        std::make_shared<StmtLstNode>(
            std::vector<std::shared_ptr<Node>>{stmts[2]}),
        std::make_shared<StmtLstNode>(
            std::vector<std::shared_ptr<Node>>{ifNode1}));

    std::shared_ptr<StmtLstNode> thenStmtLst3 = std::make_shared<StmtLstNode>(
        std::vector<std::shared_ptr<Node>>{outerWhile});
    std::shared_ptr<StmtLstNode> elseStmtLst3 = std::make_shared<StmtLstNode>(
        std::vector<std::shared_ptr<Node>>{ifNode2});

    std::shared_ptr<IfNode> ifNode3 = std::make_shared<IfNode>(
        1, std::unordered_set<std::string>{}, std::unordered_set<std::string>{},
        thenStmtLst3, elseStmtLst3);

    std::vector<std::shared_ptr<Node>> children{ifNode3};
    std::shared_ptr<StmtLstNode> stmtLst =
        std::make_shared<StmtLstNode>(children);
    std::unordered_map<int, std::unordered_set<int>> expected{
        {1, {3, 7}}, {3, {4}},    {4, {5, 6}},  {5, {4}},
        {6, {3}},    {7, {8, 9}}, {9, {10, 11}}};
    testNextExtractor(stmtLst, expected);
  }
}
