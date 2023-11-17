//
// Created by Volunteer The on 8/10/23.
//
#include "pkb/pattern_clause/PatternStorage.h"

namespace PKB {
class IfPatternStorage
    : public PatternStorage<std::string, std::string, std::unordered_set<int>> {
};

}  // namespace PKB
