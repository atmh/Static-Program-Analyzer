#pragma once

namespace QPS {

class Validateable {
 public:
  virtual bool validate() const = 0;
  virtual ~Validateable() = 0;
};

}  // namespace QPS
