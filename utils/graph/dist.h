/**
 * (c) 2024 Diego Sogari
 */
#include "graph.h"

/**
 * Shortest Distances to a node (in weighed undirected graph)
 */
struct Dist : vector<array<int, 2>> {
  Dist(const WGraph &g, int e) : vector<array<int, 2>>(g.size()) {
    for (int u = 0; u < g.size(); u++) {
      dfs(g, u, u, e);
    }
  }
  int dfs(const WGraph &g, int u, int p, int e) {
    if (u == e || (*this)[u][0]) {
      return (*this)[u][0];
    }
    array<int, 2> ans = {INT_MAX, u};
    for (auto &[v, w] : g[u]) {
      if (v != p) {
        auto d = dfs(g, v, u, e);
        ans = min(ans, {d + w, v});
      }
    }
    return ((*this)[u] = ans)[0];
  }
};
