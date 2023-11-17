#include "catch.hpp"
#include "sp/design_extractor/extractors/FollowsExtractor.h"
#include "sp/node/Node.h"
#include "sp/node/StmtLstNode.h"
#include "sp/node/StmtNode.h"
#include "sp/node/stmt_nodes/CallNode.h"
#include "sp/node/stmt_nodes/PrintNode.h"
#include "stubs/pkb/PKBStorageWriteAPI.h"

using namespace SP;

class FollowsAdapterStub : public FollowsAdapter {
 public:
  FollowsAdapterStub(const std::shared_ptr<PKB::PKBStorageWriteInterface>& pkb)
      : FollowsAdapter(pkb) {}
};

TEST_CASE("FollowsExtractor Tests") {
  std::shared_ptr<PKB::PKBStorageWriteInterface> pkb =
      std::make_shared<PKB::PKBStorageWriteStub>();

  SECTION("Visit StmtListNode") {
    FollowsExtractor extractor{FollowsAdapterStub{pkb}};
    std::shared_ptr<PrintNode> stmt1 =
        std::make_shared<PrintNode>(1, "Print 1");
    std::shared_ptr<PrintNode> stmt2 =
        std::make_shared<PrintNode>(2, "Print 2");
    std::shared_ptr<PrintNode> stmt3 =
        std::make_shared<PrintNode>(3, "Print 3");
    std::vector<std::shared_ptr<PrintNode>> tmp = {stmt1, stmt2, stmt3};
    std::vector<std::shared_ptr<Node>> nodes(tmp.begin(), tmp.end());

    std::shared_ptr<StmtLstNode> stmtListNode =
        std::make_shared<StmtLstNode>(nodes);

    extractor.visitStmtList(stmtListNode);

    std::unordered_map<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>>
        storage = extractor.getStorage();
    // Assuming there are 2 Follows relationships
    REQUIRE(storage.size() == 2);

    for (auto& [ptr1, ptr2] : storage) {
      int stmtNo1 = ptr1->stmtNo;
      int stmtNo2 = ptr2->stmtNo;
      REQUIRE(stmtNo1 < stmtNo2);
      if (stmtNo1 == 1) {
        REQUIRE(stmtNo2 == 2);
      } else if (stmtNo1 == 2) {
        REQUIRE(stmtNo2 == 3);
      } else {
        REQUIRE(false);
      }
    }
  }

  SECTION("Visit Empty StmtListNode") {
    FollowsExtractor extractor{FollowsAdapterStub{pkb}};

    std::vector<std::shared_ptr<Node>> nodes{};
    // Create an empty StmtLstNode
    std::shared_ptr<StmtLstNode> stmtListNode =
        std::make_shared<StmtLstNode>(nodes);

    // Call visitStmtList on the empty StmtListNode
    extractor.visitStmtList(stmtListNode);

    // Ensure that no Follows relationships were extracted
    REQUIRE(extractor.getStorage().empty());
  }

  SECTION("Visit StmtListNode with Gaps") {
    FollowsExtractor extractor{FollowsAdapterStub{pkb}};

    std::shared_ptr<PrintNode> stmt1 =
        std::make_shared<PrintNode>(1, "Print 1");
    std::shared_ptr<PrintNode> stmt2 =
        std::make_shared<PrintNode>(3, "Print 3");
    std::shared_ptr<PrintNode> stmt3 =
        std::make_shared<PrintNode>(5, "Print 5");
    std::shared_ptr<PrintNode> stmt4 =
        std::make_shared<PrintNode>(7, "Print 7");

    std::vector<std::shared_ptr<PrintNode>> tmp = {stmt1, stmt2, stmt3, stmt4};
    std::vector<std::shared_ptr<Node>> nodes(tmp.begin(), tmp.end());

    std::shared_ptr<StmtLstNode> stmtListNode =
        std::make_shared<StmtLstNode>(nodes);

    extractor.visitStmtList(stmtListNode);
    std::unordered_map<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>>
        storage = extractor.getStorage();

    REQUIRE(storage.size() == 3);

    for (auto& [ptr1, ptr2] : storage) {
      int stmtNo1 = ptr1->stmtNo;
      int stmtNo2 = ptr2->stmtNo;
      REQUIRE(stmtNo1 < stmtNo2);
      if (stmtNo1 == 1) {
        REQUIRE(stmtNo2 == 3);  // Statement 1 follows Statement 3
      } else if (stmtNo1 == 3) {
        REQUIRE(stmtNo2 == 5);  // Statement 3 follows Statement 5
      } else if (stmtNo1 == 5) {
        REQUIRE(stmtNo2 == 7);  // Statement 5 follows Statement 7
      } else {
        REQUIRE(false);
      }
    }
  }

  SECTION(
      "Visit StmtListNode with Gaps and children is a mix of StmtNode types") {
    FollowsExtractor extractor{FollowsAdapterStub{pkb}};

    std::shared_ptr<CallNode> stmt1 = std::make_shared<CallNode>(1, "proc");
    std::shared_ptr<PrintNode> stmt2 = std::make_shared<PrintNode>(5, "print");

    std::vector<std::shared_ptr<StmtNode>> tmp{};

    tmp.push_back(std::static_pointer_cast<StmtNode>(stmt1));
    tmp.push_back(std::static_pointer_cast<StmtNode>(stmt2));

    std::vector<std::shared_ptr<Node>> nodes{tmp.begin(), tmp.end()};

    std::shared_ptr<StmtLstNode> stmtListNode =
        std::make_shared<StmtLstNode>(nodes);

    extractor.visitStmtList(stmtListNode);
    std::unordered_map<std::shared_ptr<StmtNode>, std::shared_ptr<StmtNode>>
        storage = extractor.getStorage();

    REQUIRE(storage.size() == 1);
    for (auto& [ptr1, ptr2] : storage) {
      int stmtNo1 = ptr1->stmtNo;
      int stmtNo2 = ptr2->stmtNo;
      if (stmtNo1 == 1) {
        REQUIRE(stmtNo2 == 5);  // Statement 1 follows Statement 5
      } else {
        REQUIRE(false);
      }
    }
  }

  SECTION("Visit Single StmtListNode") {
    FollowsExtractor extractor{FollowsAdapterStub{pkb}};

    std::shared_ptr<CallNode> stmt1 = std::make_shared<CallNode>(1, "proc");

    std::vector<std::shared_ptr<CallNode>> tmp = {stmt1};
    std::vector<std::shared_ptr<Node>> nodes(tmp.begin(), tmp.end());
    std::shared_ptr<StmtLstNode> stmtListNode =
        std::make_shared<StmtLstNode>(nodes);

    extractor.visitStmtList(stmtListNode);

    // Ensure that no Follows relationships were extracted since there is only
    // one statement
    REQUIRE(extractor.getStorage().empty());
  }

  SECTION("Extract Follows relationship for 2 statement in different nesting") {
    FollowsExtractor extractor{pkb};

    // Create a StmtLstNode with StmtNodes where multiple Follows relationships
    // exist
    std::shared_ptr<CallNode> stmt1 = std::make_shared<CallNode>(1, "proc1");
    std::shared_ptr<CallNode> stmt2 = std::make_shared<CallNode>(2, "proc3");

    std::vector<std::shared_ptr<CallNode>> tmp = {stmt2};
    std::vector<std::shared_ptr<Node>> nestNodes(tmp.begin(), tmp.end());
    std::shared_ptr<StmtLstNode> nest =
        std::make_shared<StmtLstNode>(nestNodes);

    std::vector<std::shared_ptr<Node>> nodes{};
    nodes.push_back(std::static_pointer_cast<Node>(stmt1));
    nodes.push_back(std::static_pointer_cast<Node>(nest));

    std::shared_ptr<StmtLstNode> stmtListNode =
        std::make_shared<StmtLstNode>(nodes);

    extractor.visitStmtList(stmtListNode);
    REQUIRE(extractor.getStorage().empty());
  }

  SECTION(
      "Extract Follows relationship in different nesting and same tree depth") {
    FollowsExtractor extractor{FollowsAdapterStub{pkb}};

    // Create a StmtLstNode with StmtNodes where multiple Follows relationships
    // exist
    std::shared_ptr<CallNode> stmt1 = std::make_shared<CallNode>(1, "proc1");
    std::shared_ptr<CallNode> stmt2 = std::make_shared<CallNode>(2, "proc2");
    std::shared_ptr<CallNode> stmt3 = std::make_shared<CallNode>(3, "proc3");
    std::shared_ptr<CallNode> stmt4 = std::make_shared<CallNode>(4, "proc4");

    std::vector<std::shared_ptr<CallNode>> tmp1 = {stmt1, stmt2};
    std::vector<std::shared_ptr<Node>> nest1(tmp1.begin(), tmp1.end());
    std::shared_ptr<StmtLstNode> nestNode1 =
        std::make_shared<StmtLstNode>(nest1);

    std::vector<std::shared_ptr<CallNode>> tmp2 = {stmt3, stmt4};
    std::vector<std::shared_ptr<Node>> nest2(tmp2.begin(), tmp2.end());
    std::shared_ptr<StmtLstNode> nestNode2 =
        std::make_shared<StmtLstNode>(nest2);

    std::vector<std::shared_ptr<Node>> children = {
        std::static_pointer_cast<Node>(nestNode1),
        std::static_pointer_cast<Node>(nestNode2)};

    std::shared_ptr<StmtLstNode> stmtListNode =
        std::make_shared<StmtLstNode>(children);
    // Call visitStmtList to extract Follows relationships
    extractor.visitStmtList(stmtListNode);

    // Ensure that Follows relationships were extracted correctly
    REQUIRE(extractor.getStorage().empty());
  }
}
