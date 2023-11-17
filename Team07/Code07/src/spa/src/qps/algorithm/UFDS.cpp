#include "UFDS.h"

#include <numeric>

namespace QPS {

UFDS::UFDS(int n) {
  par.resize(n);
  std::iota(par.begin(), par.end(), 0);
}

int UFDS::getPar(int u) {
  while (u != par[u]) {
    u = par[u] = par[par[u]];
  }
  return u;
}

void UFDS::merge(int u, int v) {
  u = getPar(u);
  v = getPar(v);
  if (u == v)
    return;
  par[u] = v;
}

}  // namespace QPS
