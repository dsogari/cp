/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "utils.h"

/**
 * Disjoint set union with path compression
 */
struct PaintDSU {
  vector<int> par;
  PaintDSU(int n) : par(n) { iota(par.begin(), par.end(), 0); }
  int find(int u) { return u == par[u] ? u : par[u] = find(par[u]); } // O(lg n)
  int merge(int u, int p) { return par[find(u)] = find(p); } // [u->p] O(lg n)
};

/**
 * Disjoint set union with size optimization
 */
struct DSU {
  int cnt; // number of disjoint sets
  vector<int> par, siz;
  DSU(int n) : cnt(n), par(n), siz(n, 1) { iota(par.begin(), par.end(), 0); }
  int size(int u) { return siz[find(u)]; }                            // O(1)
  int find(int u) { return u == par[u] ? u : par[u] = find(par[u]); } // O(1)
  int merge(int u, int v) { // O(1) amortized
    u = find(u), v = find(v);
    if (u != v) {
      if (siz[u] < siz[v]) {
        swap(u, v);
      }
      siz[u] += exchange(siz[v], 0);
      par[v] = u;
      cnt--;
    }
    return u;
  }
};

/**
 * Sparse Disjoint set union
 */
template <typename T> struct SparseDSU {
  unordered_map<T, pair<T, int>> nodes;
  bool has(T v) const { return nodes.count(v); } // O(1)
  T add(T v) { return nodes[v] = {v, 1}, v; }    // O(1)
  T find(T v) {                                  // O(1)
    auto &par = nodes[v].first;
    return v == par ? v : par = find(par);
  }
  T merge(T a, T b) { // O(1) amortized
    a = find(a), b = find(b);
    if (a != b) {
      if (nodes[a].second < nodes[b].second) {
        swap(a, b);
      }
      nodes[a].second += nodes[b].second;
      nodes[b].first = a;
    }
    return a;
  }
};
