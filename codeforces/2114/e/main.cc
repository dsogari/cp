/**
 * https://codeforces.com/contest/2114/submission/326804506
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

template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

using Int = Number<int>;

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

void solve(int t) {
  Int n;
  vector<Int> a(n);
  Graph g(n, n - 1);
  vector<i64> ans(n);
  auto dfs = [&](auto &dfs, int u, int p, i64 sum, i64 mn, i64 mx) -> void {
    sum += a[u - 1];
    ans[u - 1] = sum - mn;
    mn = min(mn, sum);
    mx = max(mx, sum);
    for (auto &&v : g[u]) {
      if (v != p) {
        dfs(dfs, v, u, -sum, -mx, -mn);
      }
    }
  };
  dfs(dfs, 1, 1, 0, 0, 0);
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
