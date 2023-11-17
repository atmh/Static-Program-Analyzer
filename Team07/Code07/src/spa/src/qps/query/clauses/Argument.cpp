#include "Argument.h"

#include <cassert>

namespace QPS {

size_t Argument::ArgHash::operator()(const QPS::Argument& arg) const noexcept {
  size_t hash{};
  hash ^= std::hash<int>()(static_cast<int>(arg.argumentType));
  hash ^= std::hash<int>()(arg.x);
  hash ^= std::hash<std::string>()(arg.str);
  if (arg.declaration)
    hash ^= std::hash<std::string>()(arg.declaration->name());
  for (auto& e : arg.expr)
    hash ^= std::hash<std::string>()(e);
  hash ^= std::hash<bool>()(arg.exactMatch);
  return hash;
}

bool operator==(const Argument& lhs, const Argument& rhs) noexcept {
  if (lhs.argumentType != rhs.argumentType)
    return false;
  switch (lhs.argumentType) {
    case Argument::ArgumentType::SYNONYM:
      return (!lhs.declaration && !rhs.declaration) ||
             (lhs.declaration && rhs.declaration &&
              *lhs.declaration == *rhs.declaration);
    case Argument::ArgumentType::WILDCARD:
      return true;
    case Argument::ArgumentType::STRING:
      return lhs.str == rhs.str;
    case Argument::ArgumentType::INTEGER:
      return lhs.x == rhs.x;
    case Argument::ArgumentType::EXPR:
      return lhs.exactMatch == rhs.exactMatch && lhs.expr == rhs.expr;
    default:
      assert(false);
      return false;
  }
}

}  // namespace QPS
