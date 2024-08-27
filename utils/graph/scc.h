/**
 * (c) 2024 Diego Sogari
 */
#include "graph.h"

/**
 * Strongly-connected components (of directed graph)
 */
struct SCC : vector<int> {
  int count = 0;
  vector<int> low, vis;
  SCC(const Digraph &g) : vector<int>(g.size()), low(g.size()) {
    for (int i = 0, t = 1; i < g.size(); i++) {
      if (low[i] == 0) {
        dfs(g, i, t);
      }
    }
  }
  void dfs(const Digraph &g, int u, int &t) {
    auto tx = low[u] = t++;
    vis.push_back(u);
    for (auto v : g[u]) {
      if (low[v] == 0) {
        dfs(g, v, t);
      }
      low[u] = min(low[u], low[v]);
    }
    if (low[u] == tx) { // component root
      count++;
      int i = vis.size();
      do {
        auto v = vis[--i];
        low[v] = g.size();
        (*this)[v] = count;
      } while (vis[i] != u);
      vis.resize(i);
    }
  }
};
