/**
 * (c) 2024 Diego Sogari
 */
#include "io.h"

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
 * Undirected Graph with labeled edges
 */
struct LGraph : vector<vector<array<int, 2>>> {
  const int n, m;
  vector<array<Int, 2>> edges;
  LGraph(int n, int m = 0)
      : vector<vector<array<int, 2>>>(n + 1), n(n), m(m), edges(m) {
    for (int i = 0; i < m; i++) {
      auto [u, v] = edges[i];
      add(u, v, i);
    }
  }
  void add(int u, int v, int id) { _add(u, v, id), _add(v, u, id); }
  void _add(int u, int v, int id) { (*this)[u].push_back({v, id}); }
};
