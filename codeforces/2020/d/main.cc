/**
 * https://codeforces.com/contest/2020/submission/329768362
 *
 * Graph; DP; DSU
 *
 * (c) 2024 Diego Sogari
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

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

using Int = Number<int>;

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
  Int n, m;
  vector<array<Int, 3>> ops(m);
  vector by_d(11, vector<set<array<int, 2>>>(11));
  for (auto &&[a, d, k] : ops) { // O(m*log m)
    if (k > 0) {
      assert(d >= 1 && d <= 10);
      a--;
      by_d[d][a % d].insert({a, a + d * k});
    }
  }
  DSU dsu(n);
  for (int i = 1; i <= 10; i++) { // O(d^2*n)
    for (int j = 0; j < i; j++) {
      int last = 0;
      for (auto [l, r] : by_d[i][j]) {
        for (last = max(last, l); last + i <= r; last += i) {
          dsu.merge(last, last + i);
        }
      }
    }
  }
  println(dsu.cnt);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
