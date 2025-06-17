/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "dsu.h"
#include "graph/graph.h"

/**
 * Lowest Common Ancestor (Tarjan's off-line algorithm)
 */
struct Tarjan : vector<vector<int>> {
  DSU dsu;
  vector<int> anc;
  Tarjan(const Graph &g, const vector<vector<int>> &q, int s)
      : vector<vector<int>>(g.size()), dsu(g.size()), anc(g.size(), -1) {
    dfs(g, q, s, s); // O(n)
  }
  void dfs(const Graph &g, const vector<vector<int>> &q, int u, int p) {
    anc[u] = u;
    for (auto &v : g[u]) {
      if (v != p) {
        dfs(g, q, v, u);
        anc[dsu.merge(v, u)] = u;
      }
    }
    for (auto &v : q[u]) {
      (*this)[u].push_back(anc[dsu.find(v)]);
    }
  }
};
