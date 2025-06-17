/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "graph.h"

/**
 * Bridges (of undirected connected graph)
 */
struct Bridges : vector<array<int, 2>> {
  vector<int> low, siz;
  Bridges(const Graph &g, int s) : low(g.size()), siz(g.size()) {
    int t = 1;
    dfs(g, s, s, t);
  }
  void dfs(const Graph &g, int u, int p, int &t) {
    auto tx = low[u] = t++;
    siz[u] = 1;
    for (auto v : g[u]) {
      if (v != p) {
        if (low[v] == 0) {
          dfs(g, v, u, t); // post-order (visit leaves first)
          siz[u] += siz[v];
          if (low[v] > tx) {
            push_back({u, v});
          }
        }
        low[u] = min(low[u], low[v]);
      }
    }
  }
};
