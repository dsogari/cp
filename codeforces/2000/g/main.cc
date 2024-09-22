/**
 * https://codeforces.com/contest/2000/submission/282429246
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

void solve(int t) {
  Int n, m, t0, t1, t2;
  WGraph g(n, m);
  vector<int> times(n + 1, -1);
  times[n] = t0;
  set<array<int, 2>> q = {{t0, n}};
  while (q.size()) { // O(m*log n)
    auto [tu, u] = *q.rbegin();
    q.erase(prev(q.end()));
    for (auto &[v, w, z] : g[u]) {
      auto &tv = times[v];
      auto ty = tu <= t1 || tu - w >= t2 ? tu - w : max(t1 - w, tu - z);
      if (ty > tv) {
        q.erase({tv, v});
        tv = ty;
        q.insert({tv, v});
      }
    }
  }
  println(times[1]);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
