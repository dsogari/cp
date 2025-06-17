/**
 * https://the-algorithms.com/algorithm/hopcroft-karp
 *
 * Credit: Krishna Pal Deora (https://github.com/Krishnapal4050)
 */
#pragma once

#include "graph.h"

/**
 * Hopcroft-Karp algorithm for maximum matching in bipartite graph
 */
struct HopcroftKarp {
  const Digraph &g;
  vector<int> pair_u, pair_v, dist;
  HopcroftKarp(const Digraph &g, int r)
      : g(g), pair_u(g.size()), pair_v(r + 1), dist(g.size()) {}
  int compute() { // O(m*sqrt n)
    int ans = 0;
    while (bfs()) {
      for (int u = 1; u <= g.n; u++) {
        if (pair_u[u] == 0 && dfs(u)) {
          ans++;
        }
      }
    }
    return ans;
  }
  bool bfs() {
    queue<int> q;
    for (int u = 1; u <= g.n; u++) {
      if (pair_u[u] == 0) {
        dist[u] = 0;
        q.push(u);
      } else {
        dist[u] = INT_MAX;
      }
    }
    dist[0] = INT_MAX;
    while (q.size()) {
      int u = q.front();
      q.pop();
      if (dist[u] < dist[0]) {
        for (auto &v : g[u]) {
          if (dist[pair_v[v]] == INT_MAX) {
            dist[pair_v[v]] = dist[u] + 1;
            q.push(pair_v[v]);
          }
        }
      }
    }
    return dist[0] != INT_MAX;
  }
  bool dfs(int u) {
    if (u == 0) {
      return true;
    }
    for (auto &v : g[u]) {
      if (dist[pair_v[v]] == dist[u] + 1) {
        if (dfs(pair_v[v])) {
          pair_v[v] = u;
          pair_u[u] = v;
          return true;
        }
      }
    }
    dist[u] = INT_MAX;
    return false;
  }
};
