/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Disjoint set union (Union find)
 */
struct DSU {
  vector<int> par, siz;
  DSU(int n) : par(n + 1), siz(n + 1) {}
  int add(int v) { return siz[v] = 1, par[v] = v; }
  int find(int v) { return v == par[v] ? v : par[v] = find(par[v]); }
  int merge(int a, int b) {
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
