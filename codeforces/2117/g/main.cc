/**
 * https://codeforces.com/contest/2117/submission/323560813
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

template <typename T> struct DijSparse : vector<pair<T, int>> {
  DijSparse(const WGraph &g, int s) : vector<pair<T, int>>(g.size(), {{}, -1}) {
    (*this)[s].first = 0;
    set<pair<T, int>> q = {{0, s}};
    while (q.size()) {
      auto [du, u] = *q.begin();
      q.erase(q.begin());
      for (auto &[v, w] : g[u]) {
        auto &[dv, pv] = (*this)[v];
        if (pv == -1 || du + w < dv) {
          q.erase({dv, v});
          dv = du + w, pv = u;
          q.insert({dv, v});
        }
      }
    }
  }
};

struct Dist {
  int x;
  Dist(int a = 0) : x(a) {}
  Dist operator+(Dist d) const { return max(x, d.x); }
  bool operator<(Dist d) const { return x < d.x; }
};

void solve(int t) {
  Int n, m;
  WGraph g(n, m);
  DijSparse<Dist> d1(g, 1), dn(g, n);
  int ans = INT_MAX;
  for (int i = 0; i < m; i++) {
    auto [u, v, w] = g.edges[i];
    auto x = max(d1[u].first.x, dn[v].first.x);
    ans = min(ans, w + max(+w, x));
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
