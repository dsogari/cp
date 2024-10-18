/**
 * https://codeforces.com/contest/2025/submission/286540350
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

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

struct LGraph : vector<vector<array<int, 2>>> {
  const int n, m;
  vector<array<Int, 2>> edges;
  LGraph(int n, int m = 0)
      : vector<vector<array<int, 2>>>(n + 1), n(n), m(m), edges(m) {
    for (int i = 0; i < m; i++) {
      auto [u, v] = edges[i];
      add(u, v, i);
    }
  }
  void add(int u, int v, int id) { _add(u, v, id), _add(v, u, id); }
  void _add(int u, int v, int id) { (*this)[u].push_back({v, id}); }
};

void solve(int t) {
  Int n, m;
  LGraph g(n, m);
  vector<bool> vis(n + 1), evis(m);
  vector<string> ans(m);
  auto get = [&](int u, int id, bool op) {
    return string(1, "xy"[u == g.edges[id][1]]) + string(1, "+-"[op]);
  };
  auto f = [&](auto &self, int u) -> int {
    vis[u] = true;
    int prev = -1;
    for (auto &&[v, id1] : g[u]) {
      if (!evis[id1]) {
        evis[id1] = true;
        int id2 = vis[v] ? -1 : self(self, v);
        if (id2 >= 0) { // use child as a match
          ans[id1] = get(v, id1, id1 > id2);
          ans[id2] = get(v, id2, id2 > id1);
        } else if (prev >= 0) { // use parent as a match
          ans[id1] = get(u, id1, id1 > prev);
          ans[prev] = get(u, prev, prev > id1);
          prev = -1;
        } else { // child needs a match
          prev = id1;
        }
      }
    }
    return prev;
  };
  for (int u = 1; u <= n; u++) { // O(n + m)
    if (!vis[u]) {
      auto id = f(f, u);
      if (id >= 0) {
        ans[id] = get(u, id, false); // missing match for u
      }
    }
  }
  for (auto &&s : ans) {
    println(s);
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
#ifdef ONLINE_JUDGE
  int t = 1;
#else
  Int t;
#endif
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
