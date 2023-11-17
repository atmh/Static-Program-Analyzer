//
// Created by Volunteer The on 8/10/23.
//
#include "pkb/pattern_clause/PatternStorage.h"

namespace PKB {
class AssignPatternStorage
    : public PatternStorage<
          std::string, std::vector<std::string>,
          std::vector<std::pair<std::vector<std::string>, int>>> {};
}  // namespace PKB
