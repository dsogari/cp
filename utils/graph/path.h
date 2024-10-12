/**
 * (c) 2024 Diego Sogari
 */
#include "graph/graph.h"

/**
 * Shortest path between two nodes
 */
struct Path : vector<int> {
  vector<int> dist, next;
  Path(const Graph &g, int s, int e) : dist(g.size(), -1), next(g.size(), -1) {
    dist[e] = 0;
    if (dfs(g, s) < INT_MAX) {
      for (int u = s; u >= 0; u = next[u]) {
        push_back(u);
      }
    }
  }
  int dfs(const Graph &g, int u) { // O(n)
    if (dist[u] >= 0) {
      return dist[u];
    }
    int ans = dist[u] = INT_MAX;
    for (auto &v : g[u]) {
      auto d = dfs(g, v);
      if (d < ans - 1) {
        ans = d + 1;
        next[u] = v;
      }
    }
    return dist[u] = ans;
  }
};
