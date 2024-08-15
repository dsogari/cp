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

struct Graph : vector<vector<int>> {
  const int n, m;
  Graph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m) {
    for (auto &[u, v] : vector<array<Int, 2>>(m)) {
      add(u, v);
    }
  }
  void add(int u, int v) { _add(u, v), _add(v, u); }
  void _add(int u, int v) { (*this)[u].push_back(v); }
};

void solve(int t) {
  Int n, m;
  Graph g(2 * n, m);
  for (int u = 1; u <= n; u++) { // O(n + m)
    for (auto &&v : g[u]) {
      if (v > u && v <= n) {
        g.add(v, n + u);
        g.add(n + u, n + v);
      }
    }
  }
  list<array<int, 3>> intervals;
  vector<vector<decltype(intervals)::iterator>> its(2 * n + 1);
  vector<int> add(2 * n + 1);
  int ans = n;
  for (int u = 1, c = 0, mx = 0; u <= 2 * n; u++) { // O(n + m)
    for (auto &&it : its[u]) {
      add[(*it)[0]] = (*it)[2];
      intervals.erase(it);
    }
    int v = u;
    if (g[u].size()) {
      v = *ranges::max_element(g[u]);
      auto it = intervals.rbegin();
      for (int l = u, r = v; it != intervals.rend() && l < r; it++) {
        auto &[l1, r1, len] = *it;
        len -= max(0, min(r, r1) - max(l, l1)); // intersection
        l = max(l, r1);                         // difference
      }
      intervals.push_back({u, v, v - u});
      its[v].push_back(prev(intervals.end()));
    }
    mx = max(mx, v);
    if (mx <= u) {
      c++;
    }
    if (u >= n) {
      ans = min(ans, n - c);
      c += add[u - n + 1] - 1;
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
