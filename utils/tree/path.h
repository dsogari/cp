/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "graph/graph.h"

/**
 * Path between two nodes
 */
struct Path : vector<int> {
  Path(const Graph &g, int s, int e) { dfs(g, s, e, s); }
  bool dfs(const Graph &g, int a, int b, int p) { // O(n)
    push_back(a);
    if (a == b) {
      return true;
    }
    for (auto &v : g[a]) {
      if (v != p && dfs(g, v, b, a)) {
        return true;
      }
    }
    pop_back();
    return false;
  }
};
