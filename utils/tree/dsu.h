/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "utils.h"

/**
 * Disjoint set union with path compression
 */
struct SimpleDSU {
  vector<int> par;
  SimpleDSU(int n) : par(n) { iota(par.begin(), par.end(), 0); }
  int find(int v) { return v == par[v] ? v : par[v] = find(par[v]); } // O(lg n)
  int merge(int a, int b) { // O(lg n) amortized
    a = find(a), b = find(b);
    if (a != b) {
      if (a < b) {
        swap(a, b);
      }
      par[b] = a;
    }
    return a;
  }
};

/**
 * Disjoint set union with size optimization
 */
struct DSU {
  vector<int> par, siz;
  DSU(int n) : par(n), siz(n, 1) { iota(par.begin(), par.end(), 0); }
  int find(int v) { return v == par[v] ? v : par[v] = find(par[v]); } // O(1)
  int merge(int a, int b) { // O(1) amortized
    a = find(a), b = find(b);
    if (a != b) {
      if (siz[a] < siz[b]) {
        swap(a, b);
      }
      siz[a] += exchange(siz[b], 0);
      par[b] = a;
    }
    return a;
  }
  int count() const { return siz.size() - ranges::count(siz, 0); } // O(n)
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
