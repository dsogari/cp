/**
 * https://codeforces.com/contest/2014/submission/282459616
 *
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
  for (auto &u : a) { // O(h)
    horses[u] = true;
  }
  WGraph g(n, m);
  auto f = [&](int s) { // O(m*log n)
    vector<array<i64, 2>> times(n + 1, {LLONG_MAX, LLONG_MAX});
    times[s] = {0, horses[s] ? 0 : LLONG_MAX};
    set<tuple<i64, bool, int>> q = {{0, false, s}};
    while (q.size()) { // O(m*log n)
      auto [tu, hu, u] = *q.begin();
      q.erase(q.begin());
      for (auto &[v, w] : g[u]) {
        auto &[t1v, t2v] = times[v];
        if (hu | horses[u]) {
          if (tu + w / 2 < t2v) {
            q.erase({t2v, true, v});
            t2v = tu + w / 2;
            q.insert({t2v, true, v});
          }
        } else {
          if (tu + w < t1v) {
            q.erase({t1v, false, v});
            t1v = tu + w;
            q.insert({t1v, false, v});
          }
        }
      }
    }
    return times;
  };
  auto times1 = f(1); // O(m*log n)
  auto times2 = f(n); // O(m*log n)
  i64 ans = LLONG_MAX;
  for (int i = 1; i <= n; i++) { // O(n)
    auto [t11, t12] = times1[i];
    auto [t21, t22] = times2[i];
    ans = min(ans, max(min(t11, t12), min(t21, t22)));
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
