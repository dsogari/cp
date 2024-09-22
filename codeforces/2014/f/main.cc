/**
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

struct Graph : vector<vector<int>> {
  const int n, m;
  vector<array<Int, 2>> e;
  Graph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m), e(m) {
    for (auto &[u, v] : e) {
      add(u, v);
    }
  }
  void add(int u, int v) { _add(u, v), _add(v, u); }
  void _add(int u, int v) { (*this)[u].push_back(v); }
};

void solve(int t) {
  Int n, c;
  vector<Int> a(n);
  Graph g(n, n - 1);
  vector<int> idx(n);
  iota(idx.begin(), idx.end(), 0);
  auto cmp = [&](int i, int j) { return a[i] > a[j]; };
  vector<bool> vis(n + 1);
  for (int i = 0; i < n; i++) { // O(n*log n)
    ranges::sort(idx.begin() + i, idx.end(), cmp);
    auto u = idx[i] + 1;
    int k = 0;
    for (auto &&v : g[u]) {
      k += vis[v];
    }
    if (a[u - 1] > k * c) {
      vis[u] = true;
      for (auto &&v : g[u]) {
        a[v - 1] -= c;
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) { // O(n)
    if (vis[i]) {
      ans += a[i - 1];
    }
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
