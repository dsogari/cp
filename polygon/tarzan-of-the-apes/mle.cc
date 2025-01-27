/**
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

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

struct WDigraph : vector<vector<pair<int, double>>> {
  const int n, m;
  WDigraph(int n, int m = 0)
      : vector<vector<pair<int, double>>>(n + 1), n(n), m(m) {}
  void add(int u, int v, double w) { (*this)[u].push_back({v, w}); }
};

struct Dist : vector<pair<double, int>> {
  Dist(const WDigraph &g, int s)
      : vector<pair<double, int>>(g.size(), {LLONG_MAX, -1}) { // O(m*log n)
    (*this)[s].first = 0;
    set<pair<double, int>> q = {{0, s}};
    while (q.size()) {
      auto [du, u] = *q.begin();
      q.erase(q.begin());
      for (auto &[v, w] : g[u]) {
        auto &[dv, p] = (*this)[v];
        if (du + w < dv) {
          q.erase({dv, v});
          dv = du + w, p = u;
          q.insert({dv, v});
        }
      }
    }
  }
};

void solve(int t) {
  Int n;
  vector<array<Int, 3>> a(n);
  WDigraph g(n);
  for (int i = 0; i < n; i++) { // O(n^2)
    for (int j = 0; j < n; j++) {
      if (i != j) {
        auto [xi, yi, hi] = a[i];
        auto [xj, yj, hj] = a[j];
        i64 dx = xj - xi, dy = yj - yi;
        auto d = sqrt(dx * dx + dy * dy);
        if (d <= hi) {
          g.add(i, j, d);
        }
      }
    }
  }
  Dist dist(g, 0); // O(n^2*log n)
  if (dist[n - 1].second < 0) {
    println(0);
    return;
  }
  vector<int> ans;
  for (int u = n - 1; u != 0; u = dist[u].second) {
    ans.push_back(u + 1);
  }
  ranges::reverse(ans);
  println(ans.size());
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
