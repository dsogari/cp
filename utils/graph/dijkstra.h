/**
 * (c) 2024 Diego Sogari
 */
#include "graph.h"

/**
 * Shortest Distances from a node (in weighed undirected graph)
 */
struct Dist : vector<pair<i64, int>> {
  Dist(const WGraph &g, int s)
      : vector<pair<i64, int>>(g.size(), {LONG_MAX, -1}) { // O(m*log n)
    (*this)[s].first = 0;
    set<pair<i64, int>> q = {{0, s}};
    while (q.size()) {
      int u = q.begin()->second;
      q.erase(q.begin());
      auto du = (*this)[u].first;
      for (auto &[v, w] : g[u]) {
        auto &[dv, p] = (*this)[v];
        if (du + w < dv) {
          q.erase({dv, v});
          dv = du + w, p = u;
          q.insert({dv, v});
        }
      }
    }
  }
};
