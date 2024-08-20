/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Directed Graph
 */
struct Digraph : vector<vector<int>> {
  const int n, m;
  Digraph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m) {
    for (auto &[u, v] : vector<array<Int, 2>>(m)) {
      add(u, v);
    }
  }
  void add(int u, int v) { (*this)[u].push_back(v); }
};

/**
 * Undirected Graph
 */
struct Graph : vector<vector<int>> {
  const int n, m;
  Graph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m) {
    for (auto &[u, v] : vector<array<Int, 2>>(m)) {
      add(u, v);
    }
  }
  void add(int u, int v) { _add(u, v), _add(v, u); }
  void _add(int u, int v) { (*this)[u].push_back(v); }
};

/**
 * Weighed Directed Graph
 */
struct WDigraph : vector<vector<array<int, 2>>> {
  const int n, m;
  WDigraph(int n, int m = 0)
      : vector<vector<array<int, 2>>>(n + 1), n(n), m(m) {
    for (auto &[u, v, w] : vector<array<Int, 3>>(m)) {
      add(u, v, w);
    }
  }
  void add(int u, int v, int w) { (*this)[u].push_back({v, w}); }
};

/**
 * Weighed Undirected Graph
 */
struct WGraph : vector<vector<array<int, 2>>> {
  const int n, m;
  WGraph(int n, int m = 0) : vector<vector<array<int, 2>>>(n + 1), n(n), m(m) {
    for (auto &[u, v, w] : vector<array<Int, 3>>(m)) {
      add(u, v, w);
    }
  }
  void add(int u, int v, int w) { _add(u, v, w), _add(v, u, w); }
  void _add(int u, int v, int w) { (*this)[u].push_back({v, w}); }
};

/**
 * Shortest Distances to a node (in weighed undirected graph)
 */
struct Dist : vector<array<int, 2>> {
  Dist(const WGraph &g, int e) : vector<array<int, 2>>(g.size()) {
    for (int u = 0; u < g.size(); u++) {
      dfs(g, u, u, e);
    }
  }
  int dfs(const WGraph &g, int u, int p, int e) {
    if (u == e || (*this)[u][0]) {
      return (*this)[u][0];
    }
    array<int, 2> ans = {INT_MAX, u};
    for (auto &[v, w] : g[u]) {
      if (v != p) {
        auto d = dfs(g, v, u, e);
        ans = min(ans, {d + w, v});
      }
    }
    return ((*this)[u] = ans)[0];
  }
};

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

/**
 * 2-Satisfiability solver
 */
struct TwoSat {
  const int n;
  Digraph g;
  TwoSat(int n) : g(2 * n), n(n) {}
  void add(int a, int b) { g.add(n + a, n + b); }
  void either(int a, int b) { implies(-a, b); }
  void notequal(int a, int b) { equal(-a, b); }
  void set(int a) { add(-a, a); }
  void equal(int a, int b) {
    implies(a, b);
    implies(-a, -b);
  }
  void implies(int a, int b) {
    add(a, b);   //  a ->  b
    add(-b, -a); // !b -> !a
  }
  bool operator()() const {
    SCC scc(g);
    for (int i = 1; i <= n; i++) {
      if (scc[n + i] == scc[n - i]) {
        return false;
      }
    }
    return true;
  }
};

/**
 * Traveling Salesman Problem (without starting point)
 */
template <typename T> struct TSP : vector<vector<T>> {
  TSP(const vector<vector<T>> &g) : TSP(g, g.size()) {}
  TSP(const vector<vector<T>> &g, int n)
      : vector<vector<T>>(n, vector<T>(1u << n, numeric_limits<T>::max())) {
    assert(n < 32);
    for (int i = 0; i < n; i++) {
      (*this)[i][1 << i] = {}; // shortest path ending at i, including i
    }
    for (int i = 1; i < 1u << n; i++) { // all subsets in increasing size
      for (int j = 0; j < n; j++) {     // select last node in path
        if (i & 1 << j) {               // last node is in subset?
          for (int k = 0; k < n; k++) { // select next node in path
            if (~i & 1 << k) {          // next node is not in subset?
              auto &next = (*this)[k][i | 1 << k];
              next = min(next, (*this)[j][i] + g[j][k]);
            }
          }
        }
      }
    }
  }
};

/**
 * Traveling Salesman Problem (with starting point)
 */
template <typename T> struct TSPPlus : vector<vector<T>> {
  vector<vector<int>> start;
  TSPPlus(const vector<vector<T>> &g) : TSPPlus(g, g.size()) {}
  TSPPlus(const vector<vector<T>> &g, int n)
      : vector<vector<T>>(n, vector<T>(1u << n, numeric_limits<T>::max())),
        start(n, vector<int>(1u << n)) {
    assert(n < 32);
    for (int i = 0; i < n; i++) {
      (*this)[i][1 << i] = {}; // shortest path ending at i, including i
      start[i][1 << i] = i;    // starting at i
    }
    for (int i = 1; i < 1u << n; i++) { // all subsets in increasing size
      for (int j = 0; j < n; j++) {     // select last node in path
        if (i & 1 << j) {               // last node is in subset?
          for (int k = 0; k < n; k++) { // select next node in path
            if (~i & 1 << k) {          // next node is not in subset?
              auto &next = (*this)[k][i | 1 << k];
              auto value = (*this)[j][i] + g[j][k];
              if (value < next) {
                next = value;
                start[k][i | 1 << k] = start[j][i];
              }
            }
          }
        }
      }
    }
  }
};
