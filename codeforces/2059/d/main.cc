/**
 * https://codeforces.com/contest/2059/submission/304230196
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

struct Graph : vector<vector<int>> {
  const int n, m;
  vector<array<Int, 2>> edges;
  Graph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m), edges(m) {
    for (auto &[u, v] : edges) {
      add(u, v);
    }
  }
  void add(int u, int v) { (*this)[u].push_back(v), (*this)[v].push_back(u); }
};

void solve(int t) {
  Int n, s1, s2;
  Int m1;
  Graph g1(n, m1);
  Int m2;
  Graph g2(n, m2);
  vector dist(n + 1, vector<int>(n + 1, INT_MAX));
  set<array<int, 3>> q = {{0, s1, s2}};
  dist[s1][s2] = 0;
  int ans = INT_MAX;
  while (q.size()) { // O(m1*m2*log n)
    auto [du, u1, u2] = *q.begin();
    q.erase(q.begin());
    for (auto &v1 : g1[u1]) {
      for (auto &v2 : g2[u2]) {
        auto &dv = dist[v1][v2];
        auto d = abs(v1 - v2);
        if (du + d < dv) {
          q.erase({dv, v1, v2});
          dv = du + d;
          q.insert({dv, v1, v2});
        }
        if (u1 == u2 && v1 == v2) { // same edge in both graphs
          ans = min(ans, dv);
        }
      }
    }
  }
  if (ans == INT_MAX) {
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
