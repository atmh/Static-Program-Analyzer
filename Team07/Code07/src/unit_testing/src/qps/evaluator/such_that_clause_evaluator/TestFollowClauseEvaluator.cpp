#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "catch.hpp"
#include "qps/evaluator/such_that_clause_evaluator/FollowsClauseEvaluator.h"
#include "qps/query/clauses/Argument.h"
#include "qps/query/declaration/Declaration.h"
#include "qps/table/NormalizedDataStorage.h"
#include "stubs/pkb/PKBStorageReadAPI.h"

TEST_CASE("Follow Clause Evaluation Value Value") {
  SECTION("No relationship") {
    QPS::FollowsClauseEvaluator evaluator(2, 3);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<PKB::PKBStorageReadStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }

  SECTION("Correct relationship") {
    QPS::FollowsClauseEvaluator evaluator(1, 2);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<PKB::PKBStorageReadStub>()};
    static_cast<PKB::PKBStorageReadStub*>(pkb.get())->withFollowsRelationship(
        {{1, {2}}});

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.trueTable());
  }

  SECTION("Swap args relationship") {
    QPS::FollowsClauseEvaluator evaluator(2, 1);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<PKB::PKBStorageReadStub>()};
    static_cast<PKB::PKBStorageReadStub*>(pkb.get())->withFollowsRelationship(
        {{1, {2}}});

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
    REQUIRE(!table.trueTable());
  }

  SECTION("Fail case 1") {
    QPS::FollowsClauseEvaluator evaluator(1, 2);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<PKB::PKBStorageReadStub>()};
    static_cast<PKB::PKBStorageReadStub*>(pkb.get())->withFollowsRelationship(
        {{2, {3}}});

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
    REQUIRE(!table.trueTable());
  }

  SECTION("Fail case 2") {
    QPS::FollowsClauseEvaluator evaluator(1, 1);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<PKB::PKBStorageReadStub>()};
    static_cast<PKB::PKBStorageReadStub*>(pkb.get())->withFollowsRelationship(
        {{2, {3}}});

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
    REQUIRE(!table.trueTable());
  }
}

TEST_CASE("Test synonym value") {
  SECTION("Success - 1") {
    struct TestStub : public PKB::PKBStorageReadStub {
      virtual const std::unordered_set<int>& getAssigns()
          const noexcept override {
        return assigns;
      }

      virtual std::unordered_set<int> getFollowsFirstArgRelationships(
          int argOne) override {
        return {2};
      }
      std::unordered_set<int> assigns{2};
    };

    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::FollowsClauseEvaluator evaluator(1, a);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
  }

  SECTION("Failure - 1, not correct declaration") {
    struct TestStub : public PKB::PKBStorageReadStub {
      virtual const std::unordered_set<int>& getCalls()
          const noexcept override {
        return calls;
      }

      virtual std::unordered_set<int> getFollowsFirstArgRelationships(
          int argOne) override {
        return {2};
      }
      std::unordered_set<int> calls{2};
    };

    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::FollowsClauseEvaluator evaluator(1, a);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(table.empty());
  }

  SECTION("Failure - 2, no result from relationship") {
    struct TestStub : public PKB::PKBStorageReadStub {
      virtual const std::unordered_set<int>& getCalls()
          const noexcept override {
        return calls;
      }

      virtual std::unordered_set<int> getFollowsFirstArgRelationships(
          int argOne) override {
        return {};
      }
      std::unordered_set<int> calls{2};
    };

    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::FollowsClauseEvaluator evaluator(1, a);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(table.empty());
  }

  SECTION("Failure - 3, no result from declaration") {
    struct TestStub : public PKB::PKBStorageReadStub {
      virtual const std::unordered_set<int>& getCalls()
          const noexcept override {
        return calls;
      }

      virtual std::unordered_set<int> getFollowsFirstArgRelationships(
          int argOne) override {
        return {2};
      }
      std::unordered_set<int> calls{};
    };

    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::FollowsClauseEvaluator evaluator(1, a);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(table.empty());
  }
}

TEST_CASE("Test value syonym") {
  SECTION("Success - 1") {
    struct TestStub : public PKB::PKBStorageReadStub {
      virtual const std::unordered_set<int>& getAssigns()
          const noexcept override {
        return assigns;
      }

      virtual std::unordered_set<int> getFollowsSecondArgRelationships(
          int argOne) override {
        return {1};
      }
      std::unordered_set<int> assigns{1};
    };

    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::FollowsClauseEvaluator evaluator(a, 2);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
  }

  SECTION("Success - 2") {
    struct TestStub : public PKB::PKBStorageReadStub {
      virtual const std::unordered_set<int>& getStmts()
          const noexcept override {
        return stmts;
      }

      virtual std::unordered_set<int> getFollowsSecondArgRelationships(
          int argOne) override {
        return {1};
      }
      std::unordered_set<int> stmts{1};
    };

    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::StatementDeclaration>("a");
    QPS::FollowsClauseEvaluator evaluator(a, 2);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
  }

  SECTION("Failure - 1, not correct declaration") {
    struct TestStub : public PKB::PKBStorageReadStub {
      virtual const std::unordered_set<int>& getCalls()
          const noexcept override {
        return calls;
      }

      virtual std::unordered_set<int> getFollowsSecondArgRelationships(
          int argOne) override {
        return {1};
      }
      std::unordered_set<int> calls{1};
    };

    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::FollowsClauseEvaluator evaluator(a, 2);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(table.empty());
  }

  SECTION("Failure - 2, no result from relationship") {
    struct TestStub : public PKB::PKBStorageReadStub {
      virtual const std::unordered_set<int>& getCalls()
          const noexcept override {
        return calls;
      }

      virtual std::unordered_set<int> getFollowsSecondArgRelationships(
          int argOne) override {
        return {};
      }
      std::unordered_set<int> calls{1};
    };

    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::FollowsClauseEvaluator evaluator(a, 2);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(table.empty());
  }

  SECTION("Failure - 3, no result from declaration") {
    struct TestStub : public PKB::PKBStorageReadStub {
      virtual const std::unordered_set<int>& getCalls()
          const noexcept override {
        return calls;
      }

      virtual std::unordered_set<int> getFollowsSecondArgRelationships(
          int argOne) override {
        return {1};
      }
      std::unordered_set<int> calls{};
    };

    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::FollowsClauseEvaluator evaluator(a, 2);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};

    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};

    QPS::Table table = evaluator.evaluate(pkb, dataStorage);

    REQUIRE(table.empty());
  }
}

TEST_CASE("Evaluate synonym synonym") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual const std::unordered_set<int>& getCalls() const noexcept override {
      return calls;
    }

    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }

    virtual std::unordered_set<int> getFollowsFirstArgRelationships(
        int argOne) override {
      switch (argOne) {
        case 1:
          return {2};
        case 2:
          return {3};
        case 4:
          return {5};  // there is a break here
        case 6:
          return {7};
        case 7:
          return {8};
        case 50:
          return {50};
        default:
          return {};
      }
    }
    std::unordered_set<int> calls{3, 4, 5, 6, 7, 8, 50};
    std::unordered_set<int> assigns{1, 2};
  };

  SECTION("test 1, same declaration type") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    std::shared_ptr<QPS::Declaration> b =
        std::make_shared<QPS::AssignDeclaration>("b");
    QPS::FollowsClauseEvaluator evaluator(a, b);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
  }

  SECTION("test 2, different declaration type") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    std::shared_ptr<QPS::Declaration> b =
        std::make_shared<QPS::CallDeclaration>("b");
    QPS::FollowsClauseEvaluator evaluator(a, b);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
  }

  SECTION("test 3, multiple result") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::CallDeclaration>("a");
    std::shared_ptr<QPS::Declaration> b =
        std::make_shared<QPS::CallDeclaration>("b");
    QPS::FollowsClauseEvaluator evaluator(a, b);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 4);
  }

  SECTION("Test 4, different declaration type, wrong order") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::CallDeclaration>("a");
    std::shared_ptr<QPS::Declaration> b =
        std::make_shared<QPS::AssignDeclaration>("b");
    QPS::FollowsClauseEvaluator evaluator(a, b);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }

  SECTION("Same declaration - 1")  // not realistic for follow but just to test
                                   // such that eval logic
  {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::CallDeclaration>("a");
    std::shared_ptr<QPS::Declaration> b =
        std::make_shared<QPS::CallDeclaration>("a");
    QPS::FollowsClauseEvaluator evaluator(a, b);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.size() == 1);
  }

  SECTION("Same declaration - 2") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    std::shared_ptr<QPS::Declaration> b =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::FollowsClauseEvaluator evaluator(a, b);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }
}

TEST_CASE("Synonym wildcard") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual const std::unordered_set<int>& getCalls() const noexcept override {
      return calls;
    }

    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }

    virtual std::unordered_set<int> getFollowsFirstArgRelationships(
        int argOne) override {
      switch (argOne) {
        case 1:
          return {2};
        case 2:
          return {3};
        case 4:
          return {5};  // there is a break here
        case 6:
          return {7};
        case 7:
          return {8};
        default:
          return {};
      }
    }
    std::unordered_set<int> calls{3, 4, 5, 6, 7, 8};
    std::unordered_set<int> assigns{1, 2};
  };

  SECTION("test 1") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::CallDeclaration>("a");
    QPS::Argument wildcard;
    QPS::FollowsClauseEvaluator evaluator(a, wildcard);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 3);
  }

  SECTION("test 2") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::Argument wildcard;
    QPS::FollowsClauseEvaluator evaluator(a, wildcard);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 2);
  }

  SECTION("test 3") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::ReadDeclaration>("r");
    QPS::Argument wildcard;
    QPS::FollowsClauseEvaluator evaluator(a, wildcard);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }
}

TEST_CASE("Wildcard synonym") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual const std::unordered_set<int>& getCalls() const noexcept override {
      return calls;
    }

    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }

    virtual std::unordered_set<int> getFollowsSecondArgRelationships(
        int argTwo) override {
      switch (argTwo) {
        case 2:
          return {1};
        case 4:
          return {3};
        case 6:
          return {5};  // a break here
        case 7:
          return {6};
        case 8:
          return {7};
        default:
          return {};
      }
    }

    std::unordered_set<int> calls{3, 4, 5, 6, 7, 8};
    std::unordered_set<int> assigns{1, 2};
  };

  SECTION("test 1") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::CallDeclaration>("a");
    QPS::Argument wildcard;
    QPS::FollowsClauseEvaluator evaluator(wildcard, a);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 4);
  }

  SECTION("test 2") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::AssignDeclaration>("a");
    QPS::Argument wildcard;
    QPS::FollowsClauseEvaluator evaluator(wildcard, a);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(!table.empty());
    REQUIRE(table.size() == 1);
  }

  SECTION("test 3") {
    std::shared_ptr<QPS::Declaration> a =
        std::make_shared<QPS::ReadDeclaration>("r");
    QPS::Argument wildcard;
    QPS::FollowsClauseEvaluator evaluator(wildcard, a);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }
}

TEST_CASE("value wildcard") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual const std::unordered_set<int>& getCalls() const noexcept override {
      return calls;
    }

    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }

    virtual std::unordered_set<int> getFollowsSecondArgRelationships(
        int argTwo) override {
      switch (argTwo) {
        case 2:
          return {1};
        case 4:
          return {3};
        case 6:
          return {5};  // a break here
        case 7:
          return {6};
        case 8:
          return {7};
        default:
          return {};
      }
    }

    virtual std::unordered_set<int> getFollowsFirstArgRelationships(
        int argOne) override {
      switch (argOne) {
        case 1:
          return {2};
        case 2:
          return {3};
        case 4:
          return {5};  // there is a break here
        case 6:
          return {7};
        case 7:
          return {8};
        default:
          return {};
      }
    }

    std::unordered_set<int> calls{3, 4, 5, 6, 7, 8};
    std::unordered_set<int> assigns{1, 2};
  };

  SECTION("Test 1") {
    QPS::Argument wildcard;
    QPS::FollowsClauseEvaluator evaluator(1, wildcard);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.trueTable());
    REQUIRE(!table.empty());
  }

  SECTION("Test 2") {
    QPS::Argument wildcard;
    QPS::FollowsClauseEvaluator evaluator(8, wildcard);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }

  SECTION("Test 3") {
    QPS::Argument wildcard;
    QPS::FollowsClauseEvaluator evaluator(7, wildcard);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.trueTable());
    REQUIRE(!table.empty());
  }
}

TEST_CASE("wild card value") {
  struct TestStub : public PKB::PKBStorageReadStub {
    virtual const std::unordered_set<int>& getCalls() const noexcept override {
      return calls;
    }

    virtual const std::unordered_set<int>& getAssigns()
        const noexcept override {
      return assigns;
    }

    virtual std::unordered_set<int> getFollowsSecondArgRelationships(
        int argTwo) override {
      switch (argTwo) {
        case 2:
          return {1};
        case 4:
          return {3};
        case 6:
          return {5};  // a break here
        case 7:
          return {6};
        case 8:
          return {7};
        default:
          return {};
      }
    }

    virtual std::unordered_set<int> getFollowsFirstArgRelationships(
        int argOne) override {
      switch (argOne) {
        case 1:
          return {2};
        case 2:
          return {3};
        case 4:
          return {5};  // there is a break here
        case 6:
          return {7};
        case 7:
          return {8};
        default:
          return {};
      }
    }

    std::unordered_set<int> calls{3, 4, 5, 6, 7, 8};
    std::unordered_set<int> assigns{1, 2};
  };

  SECTION("Test 1") {
    QPS::Argument wildcard;
    QPS::FollowsClauseEvaluator evaluator(wildcard, 1);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }

  SECTION("Test 2") {
    QPS::Argument wildcard;
    QPS::FollowsClauseEvaluator evaluator(wildcard, 8);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.trueTable());
  }

  SECTION("Test 3") {
    QPS::Argument wildcard;
    QPS::FollowsClauseEvaluator evaluator(wildcard, 7);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.trueTable());
    REQUIRE(!table.empty());
  }
}

TEST_CASE("wildcard wildcard") {
  SECTION("True") {
    struct TestStub : public PKB::PKBStorageReadStub {
      virtual bool hasFollowsRelationship() override { return true; }
    };

    QPS::Argument wildcard1;
    QPS::Argument wildcard2;
    QPS::FollowsClauseEvaluator evaluator(wildcard1, wildcard2);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.trueTable());
  }

  SECTION("False") {
    struct TestStub : public PKB::PKBStorageReadStub {
      virtual bool hasFollowsRelationship() override { return false; }
    };

    QPS::Argument wildcard1;
    QPS::Argument wildcard2;
    QPS::FollowsClauseEvaluator evaluator(wildcard1, wildcard2);
    std::shared_ptr<PKB::PKBStorageReadInterface> pkb{
        std::make_shared<TestStub>()};
    std::shared_ptr<QPS::NormalizedDataStorage> dataStorage{
        std::make_shared<QPS::NormalizedDataStorage>()};
    QPS::Table table = evaluator.evaluate(pkb, dataStorage);
    REQUIRE(table.empty());
  }
}
