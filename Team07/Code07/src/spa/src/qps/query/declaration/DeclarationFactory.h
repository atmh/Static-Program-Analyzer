#pragma once

#include <memory>

#include "Declaration.h"

namespace QPS {

class DeclarationFactory {
 public:
  virtual std::shared_ptr<Declaration> createDeclaration(
      const std::string& name) const = 0;
  virtual std::shared_ptr<Declaration> createDeclaration(
      const std::string& name, const std::string& attr) const = 0;
  virtual ~DeclarationFactory() = 0;
};

}  // namespace QPS
