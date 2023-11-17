#pragma once

#include <vector>

namespace QPS {

class UFDS {
 public:
  UFDS(int n);

  int getPar(int u);

  void merge(int u, int v);

 private:
  std::vector<int> par;
};

}  // namespace QPS
