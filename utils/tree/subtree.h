/**
 * (c) 2024 Diego Sogari
 */
#include "graph/graph.h"

/**
 * Tree node information
 */
struct NodeInfo {
  int par, dep, siz, hei;
};

/**
 * Parent, Depth, Size and Height of subtree
 */
struct Subtree : vector<NodeInfo> {
  Subtree(const Graph &g, int s) : vector<NodeInfo>(g.size()) { dfs(g, s, s); }
  void dfs(const Graph &g, int u, int p, int d = 1) { // O(n)
    auto &cur = (*this)[u] = {p, d, 1, 1};
    for (auto &v : g[u]) {
      if (v != p) {
        dfs(g, v, u, d + 1);
        cur.siz += (*this)[v].siz;
        cur.hei = max(cur.hei, 1 + (*this)[v].hei);
      }
    }
  }
};
