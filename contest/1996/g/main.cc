/**
 * https://codeforces.com/contest/1996/submission/276096042
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
// #define debug
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

void solve(int t) {
  Int n, m;
  vector<array<Int, 2>> edges(m);
  map<int, array<int, 2>> map;
  for (auto &&[a, b] : edges) {
    auto &[_lt, gt] = map[a];
    auto &[lt, _gt] = map[b];
    gt = max<int>(gt, b);
    lt = max<int>(lt, a);
  }
  vector<array<Int, 2>> edges2;
  for (auto &&[a, b] : map) {
    if (b[0]) {
      edges2.push_back({b[0], a});
    }
    if (b[1]) {
      edges2.push_back({a, b[1]});
    }
  }
  vector<int> prev(n + 1), next(n + 1);
  for (int u = 1; u <= n; u++) {
    prev[u] = u - 1;
    next[u] = u + 1;
  }
  next[n] = 0;
  int ans = n;
  auto f = [&](auto &self, int i, int l, int r, int c) { // O(m + n*log n)
    if (i == m || c <= 1) {
      ans = min(ans, n - c);
      return;
    }
    auto [a, b] = edges2[i];
    int la = 0, rb = 0, ca = 0, cb = 0;
    for (int u = l, v = r, cnt = 0; u && v && (ca + cb < c) && (!la || !rb);
         u = next[u], v = prev[v], cnt++) {
      if (!la) {
        if (u >= a) {
          la = u;
          ca = cnt;
        } else if (v == a) {
          la = v;
          ca = c - cnt - 1;
        } else if (v < a) {
          la = next[v];
          ca = c - cnt;
        }
      }
      if (!rb) {
        if (v < b) {
          rb = v;
          cb = cnt;
        } else if (u >= b) {
          rb = prev[u];
          cb = c - cnt;
        }
      }
    }
    if (ca + cb == 0 || ca + cb == c) {
      self(self, i + 1, l, r, c);
      return; // 1. edge covers the whole interval; or
              // 2. does not cover the interval; or
              // 3. does not cover any remaining roads
    }
    if (!ca) {
      auto d = next[rb];
      prev[d] = next[rb] = 0;
      self(self, i + 1, l, rb, c - cb);
      self(self, i + 1, d, r, cb);
    } else if (!cb) {
      auto d = prev[la];
      next[d] = prev[la] = 0;
      self(self, i + 1, l, d, ca);
      self(self, i + 1, la, r, c - ca);
    } else {
      next[prev[la]] = next[rb];
      prev[next[rb]] = prev[la];
      prev[la] = next[rb] = 0;
      self(self, i + 1, la, rb, c - ca - cb);
      self(self, i + 1, l, r, ca + cb);
    }
  };
  f(f, 0, 1, n, n);
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
