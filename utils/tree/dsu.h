/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Disjoint set union (Union find)
 */
struct DSU {
  vector<int> par, siz;
  DSU(int n) : par(n + 1, -1), siz(n + 1) {}
  bool has(int v) const { return par[v] != -1; }                      // O(1)
  int add(int v) { return siz[v] = 1, par[v] = v; }                   // O(1)
  int find(int v) { return v == par[v] ? v : par[v] = find(par[v]); } // O(1)
  int merge(int a, int b) { // O(1) amortized
    a = find(a), b = find(b);
    if (a != b) {
      if (siz[a] < siz[b]) {
        swap(a, b);
      }
      siz[a] += siz[b];
      par[b] = a;
    }
    return a;
  }
};
