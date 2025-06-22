/**
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

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

using Int = Number<int>;

struct Digraph : vector<vector<int>> {
  const int n, m;
  vector<array<Int, 2>> edges;
  Digraph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m), edges(m) {
    for (auto &[u, v] : edges) {
      add(u, v);
    }
  }
  void add(int u, int v) { (*this)[u].push_back(v); }
};

struct HopcroftKarp {
  const Digraph &g;
  vector<int> pair_u, pair_v, dist;
  HopcroftKarp(const Digraph &g, int r)
      : g(g), pair_u(g.size()), pair_v(r + 1), dist(g.size()) {}
  int compute() { // O(m*sqrt n)
    int ans = 0;
    while (bfs()) {
      for (int u = 1; u <= g.n; u++) {
        if (pair_u[u] == 0 && dfs(u)) {
          ans++;
        }
      }
    }
    return ans;
  }
  bool bfs() {
    queue<int> q;
    for (int u = 1; u <= g.n; u++) {
      if (pair_u[u] == 0) {
        dist[u] = 0;
        q.push(u);
      } else {
        dist[u] = INT_MAX;
      }
    }
    dist[0] = INT_MAX;
    while (q.size()) {
      int u = q.front();
      q.pop();
      if (dist[u] < dist[0]) {
        for (auto &v : g[u]) {
          if (dist[pair_v[v]] == INT_MAX) {
            dist[pair_v[v]] = dist[u] + 1;
            q.push(pair_v[v]);
          }
        }
      }
    }
    return dist[0] != INT_MAX;
  }
  bool dfs(int u) {
    if (u == 0) {
      return true;
    }
    for (auto &v : g[u]) {
      if (dist[pair_v[v]] == dist[u] + 1) {
        if (dfs(pair_v[v])) {
          pair_v[v] = u;
          pair_u[u] = v;
          return true;
        }
      }
    }
    dist[u] = INT_MAX;
    return false;
  }
};

void solve(int t) {
  Int n;
  vector<array<Int, 2>> a(n);
  ranges::sort(a); // O(n*log n)
  Digraph g(n);
  for (int i = 0; i < n; i++) { // O(n^2)
    for (int j = i + 1; j < n; j++) {
      if (a[i][1] <= a[j][1]) {
        g.add(i + 1, j + 1);
      }
    }
  }
  HopcroftKarp hk(g, n);
  int ans = n - hk.compute(); // O(n^2.5)
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
