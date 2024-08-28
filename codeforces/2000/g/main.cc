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

struct WGraph : vector<vector<array<int, 3>>> {
  const int n, m;
  WGraph(int n, int m = 0) : vector<vector<array<int, 3>>>(n + 1), n(n), m(m) {
    for (auto &[u, v, w, z] : vector<array<Int, 4>>(m)) {
      add(u, v, w, z);
    }
  }
  void add(int u, int v, int w, int z) { _add(u, v, w, z), _add(v, u, w, z); }
  void _add(int u, int v, int w, int z) { (*this)[u].push_back({v, w, z}); }
};

struct Dist : vector<array<int, 2>> {
  Dist(const WGraph &g, int e) : vector<array<int, 2>>(g.size()) {
    for (int u = 0; u < g.size(); u++) {
      dfs(g, u, u, e);
    }
  }
  int dfs(const WGraph &g, int u, int p, int e) {
    if (u == e || (*this)[u][0]) {
      return (*this)[u][0];
    }
    array<int, 2> ans = {INT_MAX, u};
    for (auto &[v, w, _] : g[u]) {
      if (v != p) {
        auto d = dfs(g, v, u, e);
        ans = min(ans, {d + w, v});
      }
    }
    return ((*this)[u] = ans)[0];
  }
};

void solve(int t) {
  Int n, m, t0, t1, t2;
  WGraph g(n, m);
  Dist d(g, n);      // O(n)
  int len = d[1][0]; // shortest route taking only buses
  if (t2 <= t0 - len) {
    println(t0 - len);
    return;
  }
  vector<int> path;
  for (int u = 1; u != n; u = d[u][1]) { // O(n)
    path.push_back(u);
  }
  int ans = -1;
  for (int i = path.size() - 1; i >= 0; i--) { // O(n)
    auto [l, u] = d[path[i]]; // length of time to travel to n on bus
    if (t2 > t0 - l) {
      // cannot take bus on the trip to u starting now
      // either wait t2 - t1 minutes and set time limit to t1, or
      // walk
      // we have to reach u at most at t0 - d[path[i + 1]]
      //
      auto call = t2 - t1;
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
