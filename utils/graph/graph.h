/**
 * (c) 2024 Diego Sogari
 */
#include "io.h"

/**
 * Directed Graph
 */
struct Digraph : vector<vector<int>> {
  const int n, m;
  vector<array<Int, 2>> edges;
  Digraph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m), edges(m) {
    for (auto &[u, v] : edges) {
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
  vector<array<Int, 2>> edges;
  Graph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m), edges(m) {
    for (auto &[u, v] : edges) {
      add(u, v);
    }
  }
  void add(int u, int v) { (*this)[u].push_back(v), (*this)[v].push_back(u); }
};

/**
 * Weighed Directed Graph
 */
struct WDigraph : vector<vector<array<int, 2>>> {
  const int n, m;
  vector<array<Int, 3>> edges;
  WDigraph(int n, int m = 0)
      : vector<vector<array<int, 2>>>(n + 1), n(n), m(m), edges(m) {
    for (auto &[u, v, w] : edges) {
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
  vector<array<Int, 3>> edges;
  WGraph(int n, int m = 0)
      : vector<vector<array<int, 2>>>(n + 1), n(n), m(m), edges(m) {
    for (auto &[u, v, w] : edges) {
      add(u, v, w);
    }
  }
  void add(int u, int v, int w) {
    (*this)[u].push_back({v, w}), (*this)[v].push_back({u, w});
  }
};

/**
 * Undirected Graph with labeled edges
 */
struct LGraph : vector<vector<array<int, 2>>> {
  const int n, m;
  vector<array<Int, 2>> edges;
  LGraph(int n, int m = 0)
      : vector<vector<array<int, 2>>>(n + 1), n(n), m(m), edges(m) {
    for (int i = 0; i < m; i++) {
      add(edges[i][0], edges[i][1], i);
    }
  }
  void add(int u, int v, int id) {
    (*this)[u].push_back({v, id}), (*this)[v].push_back({u, id});
  }
};
