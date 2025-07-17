/**
 * https://codeforces.com/contest/2126/submission/329554360
 *
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

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

void solve(int t) {
  Int n, q;
  vector<Int> a(n);
  WGraph g(n, n - 1);
  vector<array<Int, 2>> b(q);
  map<array<int, 2>, i64> memo;
  vector<array<int, 2>> par(n + 1);
  i64 ans = 0;
  auto dfs = [&](auto &dfs, int u, int p) -> void {
    for (auto &&[v, c] : g[u]) {
      if (v != p) {
        par[v] = {u, c};
        memo[{u, a[v - 1]}] += c;
        if (a[u - 1] != a[v - 1]) {
          ans += c;
        }
        dfs(dfs, v, u);
      }
    }
  };
  dfs(dfs, 1, 1);
  for (auto &&[v, x] : b) {
    if (a[v - 1] != x) {
      auto [p, c] = par[v];
      if (p) {
        if (a[p - 1] == a[v - 1]) {
          ans += c;
        }
        if (a[p - 1] == x) {
          ans -= c;
        }
        memo[{p, a[v - 1]}] -= c;
        memo[{p, x}] += c;
      }
      ans += memo[{v, a[v - 1]}] - memo[{v, x}];
      a[v - 1] = x;
    }
    println(ans);
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
