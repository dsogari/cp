/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "graph/graph.h"

/**
 * Tree Matching
 */
struct Match : vector<int> {
  int count = 0;
  Match(const Graph &g, int s) : vector<int>(g.size(), -1) { dfs(g, s, s); }
  void dfs(const Graph &g, int u, int p) { // O(n)
    for (auto v : g[u]) {
      if (v != p) {
        dfs(g, v, u); // post-order (visit leaves first)
        if ((*this)[u] == (*this)[v]) {
          (*this)[u] = v;
          (*this)[v] = u;
          count++;
        }
      }
    }
  }
};
