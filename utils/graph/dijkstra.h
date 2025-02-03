/**
 * (c) 2024 Diego Sogari
 */
#include "graph.h"

/**
 * Dijkstra's algorithm for non-weighed graphs
 */
struct DijUnit : vector<array<int, 2>> {
  DijUnit(const Graph &g, int s)
      : vector<array<int, 2>>(g.size(), {INT_MAX, -1}) { // O(m)
    (*this)[s][0] = 0;
    queue<int> q;
    q.push(s);
    while (q.size()) {
      int u = q.front();
      q.pop();
      auto [du, pu] = (*this)[u];
      for (auto &v : g[u]) {
        auto &[dv, pv] = (*this)[v];
        if (du + 1 < dv) {
          dv = du + 1, pv = u;
          q.push(v);
        }
      }
    }
  }
};

/**
 * Dijkstra's algorithm for binary-weighed graphs
 */
struct DijBinary : vector<array<int, 2>> {
  DijBinary(const WGraph &g, int s)
      : vector<array<int, 2>>(g.size(), {INT_MAX, -1}) { // O(m)
    (*this)[s][0] = 0;
    deque<int> q;
    q.push_front(s);
    while (q.size()) {
      int u = q.front();
      q.pop_front();
      auto [du, pu] = (*this)[u];
      for (auto &[v, w] : g[u]) {
        auto &[dv, pv] = (*this)[v];
        if (du + w < dv) {
          dv = du + w, pv = u;
          w == 1 ? q.push_back(v) : q.push_front(v);
        }
      }
    }
  }
};

/**
 * Dijkstra's algorithm for sparse weighed graphs
 */
struct DijSparse : vector<pair<i64, int>> {
  DijSparse(const WGraph &g, int s)
      : vector<pair<i64, int>>(g.size(), {LLONG_MAX, -1}) { // O(m*log n)
    (*this)[s].first = 0;
    set<pair<i64, int>> q = {{0, s}};
    while (q.size()) {
      auto [du, u] = *q.begin();
      q.erase(q.begin());
      for (auto &[v, w] : g[u]) {
        auto &[dv, pv] = (*this)[v];
        if (du + w < dv) {
          q.erase({dv, v});
          dv = du + w, pv = u;
          q.insert({dv, v});
        }
      }
    }
  }
};

/**
 * Dijkstra's algorithm for dense weighed graphs
 */
struct DijDense : vector<pair<i64, int>> {
  DijDense(const WGraph &g, int s)
      : vector<pair<i64, int>>(g.size(), {LLONG_MAX, -1}) { // O(m + n^2)
    (*this)[s].first = 0;
    vector<bool> vis(size());
    for (int i = 0; i < size(); i++) {
      int u = -1;
      for (int j = 0; j < size(); j++) {
        if (!vis[j] && (u == -1 || (*this)[j].first < (*this)[u].first)) {
          u = j;
        }
      }
      auto [du, pu] = (*this)[u];
      if (du == LLONG_MAX) {
        break;
      }
      vis[u] = true;
      for (auto &[v, w] : g[u]) {
        auto &[dv, pv] = (*this)[v];
        if (du + w < dv) {
          dv = du + w, pv = u;
        }
      }
    }
  }
};
