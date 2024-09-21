/**
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

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

struct WGraph : vector<vector<array<int, 2>>> {
  const int n, m;
  WGraph(int n, int m = 0) : vector<vector<array<int, 2>>>(n + 1), n(n), m(m) {
    for (auto &[u, v, w] : vector<array<Int, 3>>(m)) {
      add(u, v, w);
    }
  }
  void add(int u, int v, int w) { _add(u, v, w), _add(v, u, w); }
  void _add(int u, int v, int w) { (*this)[u].push_back({v, w}); }
};

void solve(int t) {
  Int n, m, h;
  vector<Int> a(h);
  vector<bool> horses(n + 1);
  for (auto &u : a) {
    horses[u] = true;
  }
  WGraph g(n, m);
  auto f = [&](int s) {
    vector<pair<i64, bool>> times(n + 1, {LLONG_MAX, false});
    times[s] = {0, horses[s]};
    set<pair<i64, int>> q = {{0, s}};
    while (q.size()) { // O(m*log n)
      int u = q.begin()->second;
      q.erase(q.begin());
      auto [tu, hu] = times[u];
      for (auto &[v, w] : g[u]) {
        auto &[tv, hv] = times[v];
        auto ww = hu ? w / 2 : w;
        if (tu + ww < tv) {
          q.erase({tv, v});
          tv = tu + ww;
          hv = hu | horses[v];
          q.insert({tv, v});
        }
      }
    }
    return times;
  };
  auto times1 = f(1);
  auto times2 = f(n);
  i64 ans = LLONG_MAX;
  for (int i = 1; i <= n; i++) {
    auto t1 = times1[i].first;
    auto t2 = times2[i].first;
    ans = min(ans, max(t1, t2));
  }
  if (ans == LLONG_MAX) {
    ans = -1;
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
