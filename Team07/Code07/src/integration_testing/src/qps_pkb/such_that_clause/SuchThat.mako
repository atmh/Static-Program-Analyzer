/**
 * This file is auto generated. Please modify SuchThat.mako instead
 */

#include "catch.hpp"

#include "pkb/PKBStorageAPI.h"
#include "qps/QPS.h"

#include <memory>
#include <set>
#include <list>

namespace {

bool isSameSet(const std::list<std::string>& a, const std::set<std::string>& b)
{
  std::set<std::string> setA;
  for (const auto& item : a)
  {
    if (setA.find(item) != setA.end()) return false; // not a set
    setA.insert(item);
  }

  if (setA.size() != b.size()) return false;

  for (const auto& item : setA)
  {
    if (b.find(item) == b.end()) return false; // cannot find item
  }

  return true;
}

}

% for arg1 in args1:
% for arg2 in args2:
TEST_CASE("${relation} - arg1 = ${arg1['val']} arg2 = ${arg2['val']}")
{
    % for select in selects:
    % for add_3 in add_entity_types:
    SECTION("Select ${select['val']}; add ${add_3['addType']}")
    {
        %if arg1['type'] == 'wildcard' and arg2['type'] == 'wildcard':
        // test has relationship
        {
        std::shared_ptr<PKB::PKBStorageAPI> pkb = std::make_shared<PKB::PKBStorageAPI>();
        std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead = pkb->getReadStorage();
        std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite = pkb->getWriteStorage();
        %if select['addType'].title() == "Call" or select['addType'].title() == "Read" or select['addType'].title() == "Print":
        pkbWrite->add${select['addType'].title()}Entity(1, "var");
        pkbWrite->add${select['addType'].title()}Entity(2, "var");
        %if add_3['addType'].title() == "Call" or add_3['addType'].title() == "Read" or add_3['addType'].title() == "Print":
        pkbWrite->add${add_3['addType'].title()}Entity(3, "var");
        %else:
        pkbWrite->add${add_3['addType'].title()}Entity(3);
        %endif
        %else:
        pkbWrite->add${select['addType'].title()}Entity(1);
        pkbWrite->add${select['addType'].title()}Entity(2);
        %if add_3['addType'].title() == "Call" or add_3['addType'].title() == "Read" or add_3['addType'].title() == "Print":
        pkbWrite->add${add_3['addType'].title()}Entity(3, "var");
        %else:
        pkbWrite->add${add_3['addType'].title()}Entity(3);
        %endif
        %endif
            
        pkbWrite->add${'Follows' if 'Follows' in relation else 'Parent'}Relationship(1, 2);
        pkbWrite->add${'Follows' if 'Follows' in relation else 'Parent'}Relationship(2, 3);

        QPS::QPS qps{pkbRead};
        auto res = qps.process("${declarations} Select ${select['val']} such that ${relation}(${arg1['val']}, ${arg2['val']})");
        REQUIRE(isSameSet(res, {${ arg_arg_res(select['addType'].title(), select['addType'].title(), add_3['addType'].title(), select['type'].title() ) }}));
        }
        // test has no relationship
        {
        std::shared_ptr<PKB::PKBStorageAPI> pkb = std::make_shared<PKB::PKBStorageAPI>();
        std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead = pkb->getReadStorage();
        std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite = pkb->getWriteStorage();
        %if select['addType'].title() == "Call" or select['addType'].title() == "Read" or select['addType'].title() == "Print":
        pkbWrite->add${select['addType'].title()}Entity(1, "var");
        %else:
        pkbWrite->add${select['addType'].title()}Entity(1);
        %endif

        QPS::QPS qps{pkbRead};
        auto res = qps.process("${declarations} Select ${select['val']} such that ${relation}(${arg1['val']}, ${arg2['val']})");
        REQUIRE(isSameSet(res, {}));
        }
        %endif
        std::shared_ptr<PKB::PKBStorageAPI> pkb = std::make_shared<PKB::PKBStorageAPI>();
        std::shared_ptr<PKB::PKBStorageReadInterface> pkbRead = pkb->getReadStorage();
        std::shared_ptr<PKB::PKBStorageWriteInterface> pkbWrite = pkb->getWriteStorage();

        %if select['addType'].title() == "Call" or select['addType'].title() == "Read" or select['addType'].title() == "Print":
        pkbWrite->add${select['addType'].title()}Entity(1, "var");
        pkbWrite->add${select['addType'].title()}Entity(2, "var");
        %if add_3['addType'].title() == "Call" or add_3['addType'].title() == "Read" or add_3['addType'].title() == "Print":
        pkbWrite->add${add_3['addType'].title()}Entity(3, "var");
        %else:
        pkbWrite->add${add_3['addType'].title()}Entity(3);
        %endif
        %else:
        pkbWrite->add${select['addType'].title()}Entity(1);
        pkbWrite->add${select['addType'].title()}Entity(2);
        %if add_3['addType'].title() == "Call" or add_3['addType'].title() == "Read" or add_3['addType'].title() == "Print":
        pkbWrite->add${add_3['addType'].title()}Entity(3, "var");
        %else:
        pkbWrite->add${add_3['addType'].title()}Entity(3);
        %endif
        %endif
    
        pkbWrite->add${'Follows' if 'Follows' in relation else 'Parent'}Relationship(1, 2);
        pkbWrite->add${'Follows' if 'Follows' in relation else 'Parent'}Relationship(2, 3);

        QPS::QPS qps{pkbRead};
        auto res = qps.process("${declarations} Select ${select['val']} such that ${relation}(${arg1['val']}, ${arg2['val']})");
    }
    %endfor
    %endfor
}

%endfor
%endfor
