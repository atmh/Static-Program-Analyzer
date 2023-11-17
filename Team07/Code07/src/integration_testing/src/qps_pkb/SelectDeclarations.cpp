#include <list>
#include <memory>
#include <set>

#include "catch.hpp"
#include "pkb/PKBStorageAPI.h"
#include "qps/QPS.h"

namespace {

bool isSameSet(const std::list<std::string>& a,
               const std::set<std::string>& b) {
  std::set<std::string> setA;
  for (const auto& item : a) {
    if (setA.find(item) != setA.end())
      return false;  // not a set
    setA.insert(item);
  }

  if (setA.size() != b.size())
    return false;

  for (const auto& item : setA) {
    if (b.find(item) == b.end())
      return false;  // cannot find item
  }

  return true;
}

}  // namespace

// non statements
TEST_CASE("Variable Query") {
  SECTION("No variables") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    auto res = qps.process("variable variable; Select variable");

    REQUIRE(isSameSet(res, {}));
  }

  SECTION("1 variable") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addVariableEntity("a");

    auto res = qps.process("variable variable; Select variable");

    REQUIRE(isSameSet(res, {"a"}));
  }

  SECTION("2 variable") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addVariableEntity("a");
    pkbWrite->addVariableEntity("b");

    auto res = qps.process("variable variable; Select variable");

    REQUIRE(isSameSet(res, {"a", "b"}));
  }

  SECTION("3 variable") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addVariableEntity("a");
    pkbWrite->addVariableEntity("b");
    pkbWrite->addVariableEntity("c");

    auto res = qps.process("variable variable; Select variable");

    REQUIRE(isSameSet(res, {"a", "b", "c"}));
  }

  SECTION("Mixed - non statement") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addVariableEntity("var");
    pkbWrite->addProcedureEntity("proc");

    auto res = qps.process("variable variable; Select variable");

    REQUIRE(isSameSet(res, {"var"}));
  }

  SECTION("Mixed - statement") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addVariableEntity("var");
    pkbWrite->addReadEntity(1, "var");

    auto res = qps.process("variable variable; Select variable");

    REQUIRE(isSameSet(res, {"var"}));
  }
}

TEST_CASE("Constant Query") {
  SECTION("No constant") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    auto res = qps.process("constant constant; Select constant");

    REQUIRE(isSameSet(res, {}));
  }

  SECTION("1 constant") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addConstantEntity("c1");

    auto res = qps.process("constant constant; Select constant");

    REQUIRE(isSameSet(res, {"c1"}));
  }

  SECTION("2 variable") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addConstantEntity("c1");
    pkbWrite->addConstantEntity("c2");

    auto res = qps.process("constant constant; Select constant");

    REQUIRE(isSameSet(res, {"c1", "c2"}));
  }

  SECTION("3 variable") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addConstantEntity("c1");
    pkbWrite->addConstantEntity("c2");
    pkbWrite->addConstantEntity("c3");

    auto res = qps.process("constant constant; Select constant");

    REQUIRE(isSameSet(res, {"c1", "c2", "c3"}));
  }

  SECTION("Mixed - non statement") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addConstantEntity("const1");
    pkbWrite->addProcedureEntity("proc1");

    auto res = qps.process("constant constant; Select constant");

    REQUIRE(isSameSet(res, {"const1"}));
  }

  SECTION("Mixed - statement") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addConstantEntity("const1");
    pkbWrite->addReadEntity(1, "var");

    auto res = qps.process("constant constant; Select constant");

    REQUIRE(isSameSet(res, {"const1"}));
  }
}

TEST_CASE("Procedure Query") {
  SECTION("No procedure") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    auto res = qps.process("procedure procedure; Select procedure");

    REQUIRE(isSameSet(res, {}));
  }

  SECTION("1 procedure") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addProcedureEntity("proc1");

    auto res = qps.process("procedure procedure; Select procedure");

    REQUIRE(isSameSet(res, {"proc1"}));
  }

  SECTION("2 procedure") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addProcedureEntity("proc1");
    pkbWrite->addProcedureEntity("proc2");

    auto res = qps.process("procedure procedure; Select procedure");

    REQUIRE(isSameSet(res, {"proc1", "proc2"}));
  }

  SECTION("3 variable") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addProcedureEntity("proc1");
    pkbWrite->addProcedureEntity("proc2");
    pkbWrite->addProcedureEntity("proc3");

    auto res = qps.process("procedure procedure; Select procedure");

    REQUIRE(isSameSet(res, {"proc1", "proc2", "proc3"}));
  }

  SECTION("Mixed - non statement") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addProcedureEntity("proc");
    pkbWrite->addVariableEntity("var");

    auto res = qps.process("procedure procedure; Select procedure");

    REQUIRE(isSameSet(res, {"proc"}));
  }

  SECTION("Mixed - statement") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addProcedureEntity("proc");
    pkbWrite->addReadEntity(1, "var");

    auto res = qps.process("procedure procedure; Select procedure");

    REQUIRE(isSameSet(res, {"proc"}));
  }
}

// statement related query
TEST_CASE("Statement Query") {
  SECTION("No statements 1") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    auto res = qps.process("stmt stmt; Select stmt");

    REQUIRE(isSameSet(res, {}));
  }

  SECTION("No statements 2") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addProcedureEntity("proc1");
    pkbWrite->addVariableEntity("var1");
    pkbWrite->addConstantEntity("const1");

    auto res = qps.process("stmt stmt; Select stmt");

    REQUIRE(isSameSet(res, {}));
  }

  SECTION("1 statement - 1") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addReadEntity(1, "var");

    auto res = qps.process("stmt stmt; Select stmt");

    REQUIRE(isSameSet(res, {"1"}));
  }

  SECTION("1 statement - 2") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addPrintEntity(1, "var");

    auto res = qps.process("stmt stmt; Select stmt");

    REQUIRE(isSameSet(res, {"1"}));
  }

  SECTION("1 statement - 3") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addAssignEntity(1);

    auto res = qps.process("stmt stmt; Select stmt");

    REQUIRE(isSameSet(res, {"1"}));
  }

  SECTION("1 statement - 4") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addCallEntity(1, "proc");

    auto res = qps.process("stmt stmt; Select stmt");

    REQUIRE(isSameSet(res, {"1"}));
  }

  SECTION("1 statement - 5") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addWhileEntity(1);

    auto res = qps.process("stmt stmt; Select stmt");

    REQUIRE(isSameSet(res, {"1"}));
  }

  SECTION("1 statement - 6") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addIfEntity(1);

    auto res = qps.process("stmt stmt; Select stmt");

    REQUIRE(isSameSet(res, {"1"}));
  }

  SECTION("Mixed statements") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addReadEntity(1, "var");
    pkbWrite->addPrintEntity(2, "var");
    pkbWrite->addAssignEntity(3);
    pkbWrite->addCallEntity(4, "proc");
    pkbWrite->addWhileEntity(5);
    pkbWrite->addIfEntity(6);

    auto res = qps.process("stmt stmt; Select stmt");

    REQUIRE(isSameSet(res, {"1", "2", "3", "4", "5", "6"}));
  }
}

TEST_CASE("Read Query") {
  SECTION("No Read") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    auto res = qps.process("read read; Select read");

    REQUIRE(isSameSet(res, {}));
  }

  SECTION("1 read") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addReadEntity(2, "var");

    auto res = qps.process("read read; Select read");

    REQUIRE(isSameSet(res, {"2"}));
  }

  SECTION("2 reads") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addReadEntity(1, "var");
    pkbWrite->addReadEntity(2, "var");

    auto res = qps.process("read read; Select read");

    REQUIRE(isSameSet(res, {"1", "2"}));
  }

  SECTION("3 reads") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addReadEntity(1, "var");
    pkbWrite->addReadEntity(2, "var");
    pkbWrite->addReadEntity(3, "var");

    auto res = qps.process("read read; Select read");

    REQUIRE(isSameSet(res, {"1", "2", "3"}));
  }

  SECTION("read varName attribute unique") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addReadEntity(1, "var1");
    pkbWrite->addReadEntity(2, "var2");
    pkbWrite->addReadEntity(3, "var3");

    auto res = qps.process("read read; Select read.varName");

    REQUIRE(isSameSet(res, {"var1", "var2", "var3"}));
  }

  SECTION("read varName attribute common") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addReadEntity(1, "var");
    pkbWrite->addReadEntity(2, "var");
    pkbWrite->addReadEntity(3, "var");

    auto res = qps.process("read read; Select read.varName");

    REQUIRE(isSameSet(res, {"var"}));
  }

  SECTION("read stmt# attribute") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addReadEntity(1, "var");
    pkbWrite->addReadEntity(2, "var");
    pkbWrite->addReadEntity(3, "var");

    auto res = qps.process("read read; Select read.stmt#");

    REQUIRE(isSameSet(res, {"1", "2", "3"}));
  }

  SECTION("Mixed - non statement") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addReadEntity(1, "var");
    pkbWrite->addProcedureEntity("proc");

    auto res = qps.process("read read; Select read");

    REQUIRE(isSameSet(res, {"1"}));
  }

  SECTION("Mixed - statement") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addReadEntity(1, "var");
    pkbWrite->addPrintEntity(2, "var");

    auto res = qps.process("read read; Select read");

    REQUIRE(isSameSet(res, {"1"}));
  }
}

TEST_CASE("Print Query") {
  SECTION("No print") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    auto res = qps.process("print print; Select print");

    REQUIRE(isSameSet(res, {}));
  }

  SECTION("1 print") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addPrintEntity(2, "var");

    auto res = qps.process("print print; Select print");

    REQUIRE(isSameSet(res, {"2"}));
  }

  SECTION("2 prints") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addPrintEntity(1, "var");
    pkbWrite->addPrintEntity(2, "var");

    auto res = qps.process("print print; Select print");

    REQUIRE(isSameSet(res, {"1", "2"}));
  }

  SECTION("3 prints") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addPrintEntity(1, "var");
    pkbWrite->addPrintEntity(2, "var");
    pkbWrite->addPrintEntity(3, "var");

    auto res = qps.process("print print; Select print");

    REQUIRE(isSameSet(res, {"1", "2", "3"}));
  }

  SECTION("print varName attribute unique") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addPrintEntity(1, "var1");
    pkbWrite->addPrintEntity(2, "var2");
    pkbWrite->addPrintEntity(3, "var3");

    auto res = qps.process("print print; Select print.varName");

    REQUIRE(isSameSet(res, {"var1", "var2", "var3"}));
  }

  SECTION("print varName attribute common") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addPrintEntity(1, "var");
    pkbWrite->addPrintEntity(2, "var");
    pkbWrite->addPrintEntity(3, "var");

    auto res = qps.process("print print; Select print.varName");

    REQUIRE(isSameSet(res, {"var"}));
  }

  SECTION("print stmt# attribute") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addPrintEntity(1, "var");
    pkbWrite->addPrintEntity(2, "var");
    pkbWrite->addPrintEntity(3, "var");

    auto res = qps.process("print print; Select print.stmt#");

    REQUIRE(isSameSet(res, {"1", "2", "3"}));
  }

  SECTION("Mixed - non statement") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addPrintEntity(1, "var");
    pkbWrite->addProcedureEntity("proc");

    auto res = qps.process("print print; Select print");

    REQUIRE(isSameSet(res, {"1"}));
  }

  SECTION("Mixed - statement") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addPrintEntity(1, "var");
    pkbWrite->addAssignEntity(2);

    auto res = qps.process("print print; Select print");

    REQUIRE(isSameSet(res, {"1"}));
  }
}

TEST_CASE("Assign Query") {
  SECTION("No assign") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    auto res = qps.process("assign assign; Select assign");

    REQUIRE(isSameSet(res, {}));
  }

  SECTION("1 assign") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addAssignEntity(2);

    auto res = qps.process("assign assign; Select assign");

    REQUIRE(isSameSet(res, {"2"}));
  }

  SECTION("2 assigns") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addAssignEntity(1);
    pkbWrite->addAssignEntity(2);

    auto res = qps.process("assign assign; Select assign");

    REQUIRE(isSameSet(res, {"1", "2"}));
  }

  SECTION("3 assigns") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addAssignEntity(1);
    pkbWrite->addAssignEntity(2);
    pkbWrite->addAssignEntity(3);

    auto res = qps.process("assign assign; Select assign");

    REQUIRE(isSameSet(res, {"1", "2", "3"}));
  }

  SECTION("Mixed - non statement") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addAssignEntity(1);
    pkbWrite->addProcedureEntity("proc");

    auto res = qps.process("assign assign; Select assign");

    REQUIRE(isSameSet(res, {"1"}));
  }

  SECTION("Mixed - statement") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addAssignEntity(1);
    pkbWrite->addReadEntity(2, "var");

    auto res = qps.process("assign assign; Select assign");

    REQUIRE(isSameSet(res, {"1"}));
  }
}

TEST_CASE("Call Query") {
  SECTION("No call") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    auto res = qps.process("call call; Select call");

    REQUIRE(isSameSet(res, {}));
  }

  SECTION("1 call") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addCallEntity(2, "proc");

    auto res = qps.process("call call; Select call");

    REQUIRE(isSameSet(res, {"2"}));
  }

  SECTION("2 calls") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addCallEntity(1, "proc");
    pkbWrite->addCallEntity(2, "proc");

    auto res = qps.process("call call; Select call");

    REQUIRE(isSameSet(res, {"1", "2"}));
  }

  SECTION("3 calls") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addCallEntity(1, "proc");
    pkbWrite->addCallEntity(2, "proc");
    pkbWrite->addCallEntity(3, "proc");

    auto res = qps.process("call call; Select call");

    REQUIRE(isSameSet(res, {"1", "2", "3"}));
  }

  SECTION("call procName attribute unique") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addCallEntity(1, "proc1");
    pkbWrite->addCallEntity(2, "proc2");
    pkbWrite->addCallEntity(3, "proc3");

    auto res = qps.process("call call; Select call.procName");
    REQUIRE(isSameSet(res, {"proc1", "proc2", "proc3"}));
  }

  SECTION("call procName attribute common") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addCallEntity(1, "proc");
    pkbWrite->addCallEntity(2, "proc");
    pkbWrite->addCallEntity(3, "proc");

    auto res = qps.process("call call; Select call.procName");
    REQUIRE(isSameSet(res, {"proc"}));
  }

  SECTION("call stmt# attribute") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addCallEntity(1, "proc");
    pkbWrite->addCallEntity(2, "proc");
    pkbWrite->addCallEntity(3, "proc");

    auto res = qps.process("call call; Select call.stmt#");

    REQUIRE(isSameSet(res, {"1", "2", "3"}));
  }

  SECTION("Mixed - non statement") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addCallEntity(1, "proc");
    pkbWrite->addProcedureEntity("proc");

    auto res = qps.process("call call; Select call");

    REQUIRE(isSameSet(res, {"1"}));
  }

  SECTION("Mixed - statement") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addCallEntity(1, "proc");
    pkbWrite->addReadEntity(2, "var");

    auto res = qps.process("call call; Select call");

    REQUIRE(isSameSet(res, {"1"}));
  }
}

TEST_CASE("While Query") {
  SECTION("No while") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    auto res = qps.process("while while; Select while");

    REQUIRE(isSameSet(res, {}));
  }

  SECTION("1 while") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addWhileEntity(2);

    auto res = qps.process("while while; Select while");

    REQUIRE(isSameSet(res, {"2"}));
  }

  SECTION("2 whiles") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addWhileEntity(1);
    pkbWrite->addWhileEntity(2);

    auto res = qps.process("while while; Select while");

    REQUIRE(isSameSet(res, {"1", "2"}));
  }

  SECTION("3 whiles") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addWhileEntity(1);
    pkbWrite->addWhileEntity(2);
    pkbWrite->addWhileEntity(3);

    auto res = qps.process("while while; Select while");

    REQUIRE(isSameSet(res, {"1", "2", "3"}));
  }

  SECTION("Mixed - non statement") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addWhileEntity(1);
    pkbWrite->addProcedureEntity("proc");

    auto res = qps.process("while while; Select while");

    REQUIRE(isSameSet(res, {"1"}));
  }

  SECTION("Mixed - statement") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addWhileEntity(1);
    pkbWrite->addReadEntity(2, "var");

    auto res = qps.process("while while; Select while");

    REQUIRE(isSameSet(res, {"1"}));
  }
}

TEST_CASE("If Query") {
  SECTION("No if") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    auto res = qps.process("if if; Select if");

    REQUIRE(isSameSet(res, {}));
  }

  SECTION("1 if") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addIfEntity(2);

    auto res = qps.process("if if; Select if");

    REQUIRE(isSameSet(res, {"2"}));
  }

  SECTION("2 ifs") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addIfEntity(1);
    pkbWrite->addIfEntity(2);

    auto res = qps.process("if if; Select if");

    REQUIRE(isSameSet(res, {"1", "2"}));
  }

  SECTION("3 ifs") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addIfEntity(1);
    pkbWrite->addIfEntity(2);
    pkbWrite->addIfEntity(3);

    auto res = qps.process("if if; Select if");

    REQUIRE(isSameSet(res, {"1", "2", "3"}));
  }

  SECTION("Mixed - non statement") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addIfEntity(1);
    pkbWrite->addProcedureEntity("proc");

    auto res = qps.process("if if; Select if");

    REQUIRE(isSameSet(res, {"1"}));
  }

  SECTION("Mixed - statement") {
    std::shared_ptr<PKB::PKBStorageAPI> pkb =
        std::make_shared<PKB::PKBStorageAPI>();
    std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead =
        pkb->getReadStorage();
    std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite =
        pkb->getWriteStorage();
    QPS::QPS qps{pkbRead};

    pkbWrite->addIfEntity(1);
    pkbWrite->addReadEntity(2, "var");

    auto res = qps.process("if if; Select if");

    REQUIRE(isSameSet(res, {"1"}));
  }
}
