/**
 * https://codeforces.com/contest/2014/submission/282891993
 *
 * (c) 2024 Diego Sogari
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
  Int n, c;
  vector<Int> a(n);
  Graph g(n, n - 1);
  auto f = [&](auto &self, int u, int p) -> array<i64, 2> { // O(n)
    array<i64, 2> ans = {0, a[u - 1]};
    for (auto &&v : g[u]) {
      if (v != p) {
        auto [c1, c2] = self(self, v, u);
        ans[0] += max(c1, c2);
        ans[1] += max(c1, c2 - 2 * c);
      }
    }
    return ans;
  };
  auto [c1, c2] = f(f, 1, 1); // O(n)
  println(max(c1, c2));
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
