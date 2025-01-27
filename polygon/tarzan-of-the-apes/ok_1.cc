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

struct Iota : vector<int> {
  Iota(int n, int s = 0) : vector<int>(n) { iota(begin(), end(), s); }
  Iota(int n, auto &&f, int s = 0) : Iota(n, s) { ranges::sort(*this, f); }
};

void solve(int t) {
  Int n;
  vector<array<Int, 3>> a(n);
  auto cmp = [&](int i, int j) { return a[i][0] < a[j][0]; };
  Iota idx(n, cmp); // O(n*log n)
  WDigraph g(n);
  vector<bool> vis(n);
  queue<int> q;
  auto first = ranges::find(idx, 0) - idx.begin();
  auto last = ranges::find(idx, n - 1) - idx.begin();
  q.push(first);
  vis[first] = true;
  auto f = [&](int i, int j) { // O(1)
    auto [xi, yi, hi] = a[idx[i]];
    auto [xj, yj, hj] = a[idx[j]];
    auto dx = abs(xj - xi), dy = abs(yj - yi);
    if (dx > hi) {
      return false;
    }
    auto d = sqrt(i64(dx) * dx + i64(dy) * dy);
    if (d <= hi) {
      g.add(i, j, d);
      if (!vis[j]) {
        if (d + hj > hi) {
          q.push(j);
        }
        vis[j] = true;
      }
    }
    return true;
  };
  while (q.size()) { // O(n^2)
    auto i = q.front();
    q.pop();
    for (int j = i + 1; j < n && f(i, j); j++)
      ; // search right
    for (int j = i - 1; j >= 0 && f(i, j); j--)
      ; // search left
  }
  Dist dist(g, first); // O(n^2*log n)
  if (dist[last].second < 0) {
    println(0);
    return;
  }
  vector<int> ans;
  for (int u = last; u != first; u = dist[u].second) {
    ans.push_back(idx[u] + 1);
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
