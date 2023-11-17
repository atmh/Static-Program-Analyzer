#pragma once

#include <optional>

#include "DeclarationFactory.h"

namespace QPS {
template <typename DeclarationType>
class DeclarationCreator : public DeclarationFactory {
 public:
  virtual std::shared_ptr<Declaration> createDeclaration(
      const std::string& name) const override;
  virtual std::shared_ptr<Declaration> createDeclaration(
      const std::string& name, const std::string& attr) const override;

 private:
  const static std::optional<std::string> nameAttr, integerAttr;
};
}  // namespace QPS
