/**
 * https://codeforces.com/contest/2065/submission/305352149
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
  string ans(n, '0');
  vector<bool> vis(n + 1);
  for (int u = 1; u <= n; u++) { // O(n)
    vis[a[u - 1]] = true;
    for (auto &&v : g[u]) {
      if (vis[a[v - 1]]) {
        ans[a[v - 1] - 1] = '1';
      }
      vis[a[v - 1]] = true;
    }
    for (auto &&v : g[u]) {
      vis[a[v - 1]] = false;
    }
    vis[a[u - 1]] = false;
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
