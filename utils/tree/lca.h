/**
 * (c) 2024 Diego Sogari
 */
#include "dsu.h"
#include "graph/graph.h"

/**
 * Lowest Common Ancestor (Tarjan's off-line algorithm)
 */
struct LCA : vector<vector<int>> {
  DSU dsu;
  vector<int> anc, vis;
  LCA(const Graph &g, const vector<vector<int>> &q, int s)
      : vector<vector<int>>(g.size()), dsu(g.size()), anc(g.size()),
        vis(g.size()) {
    dfs(g, q, s, s);
  }
  void dfs(const Graph &g, const vector<vector<int>> &q, int u, int p) {
    for (auto &v : g[u]) {
      if (v != p) {
        dfs(g, q, v, u);
        anc[dsu.merge(v, u)] = u;
      }
    }
    for (auto &v : q[u]) {
      if (vis[v]) { // otherwise, wait until v is processed
        (*this)[u].push_back(anc[dsu.find(v)]);
      }
    }
  }
};
