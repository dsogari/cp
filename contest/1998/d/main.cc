/**
 * https://codeforces.com/contest/1998/submission/275863908
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#define debug
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

struct Digraph : vector<vector<int>> {
  const int n, m;
  Digraph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m) {
    for (auto &[u, v] : vector<array<Int, 2>>(m)) {
      add(u, v);
    }
  }
  void add(int u, int v) { (*this)[u].push_back(v); }
};

void solve(int t) {
  Int n, m;
  Digraph g(n, m);
  for (int u = 1; u < n; u++) {
    g.add(u, u + 1);
  }
  string ans(n - 1, '1');
  vector<int> dp(n + 1, n); // minimum distance traveled by Elsie
  dp[1] = 0;
  for (int u = 1, s = 2, mx = 0; s < n; u++, s++) { // O(n + m)
    auto d = dp[u] + 1;
    for (auto &v : g[u]) {
      dp[v] = min(dp[v], d);
      mx = max(mx, v - dp[v]);
    }
    ans[u] = (mx <= s) + '0';
  }
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
