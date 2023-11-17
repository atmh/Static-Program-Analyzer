#include "Declaration.h"

namespace QPS {

Declaration::Declaration(const std::string& declarationName, Type type)
    : declarationName(declarationName), type_(type) {}

const std::string& Declaration::name() const noexcept {
  return declarationName;
}

Declaration::Type Declaration::type() const noexcept {
  return type_;
}

bool operator==(const Declaration& lhs, const Declaration& rhs) {
  return lhs.declarationName == rhs.declarationName;
}

Declaration::~Declaration() = default;

}  // namespace QPS
