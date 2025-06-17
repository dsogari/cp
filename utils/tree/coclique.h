/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "graph/graph.h"

/**
 * Tree Coclique (Independent Set)
 */
struct Coclique : vector<bool> {
  int count = 0;
  Coclique(const Graph &g, int s) : vector<bool>(g.size()) { dfs(g, s, s); }
  void dfs(const Graph &g, int u, int p) { // O(n)
    (*this)[u] = !(*this)[p];
    count += (*this)[u];
    for (auto v : g[u]) {
      if (v != p) {
        dfs(g, v, u);
      }
    }
  }
};
