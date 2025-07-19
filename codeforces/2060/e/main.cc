/**
 * https://codeforces.com/contest/2060/submission/329768432
 *
 * Graph theory; DSU; DFS; greedy
 *
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#define debug(...)
#else
#include "debug.h"
init();
#endif

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

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

void solve(int t) {
  Int n, m1, m2;
  vector<array<Int, 2>> f(m1), g(m2);
  DSU inboth(n + 1), ing(n + 1);
  for (auto [u, v] : g) {
    ing.merge(u, v);
  }
  int ans = 0;
  for (auto [u, v] : f) {
    if (ing.find(u) != ing.find(v)) {
      ans++; // edges to be removed
    } else {
      inboth.merge(u, v);
    }
  }
  ans += inboth.cnt - ing.cnt; // edges to be added
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
