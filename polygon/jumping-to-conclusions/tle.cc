/**
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

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

using Int = Number<int>;

template <typename T> struct Mat : vector<vector<T>> {
  int n, m;
  Mat(int n, int m) : vector<vector<T>>(n), n(n), m(m) {
    ranges::for_each(*this, [m](auto &row) { row.resize(m); });
  }
  Mat(int n, int m, T s) : vector<vector<T>>(n, vector<T>(m, s)), n(n), m(m) {}
};

void solve(int t) {
  Int n, m;
  Mat<Int> a(n, m);
  Mat<bool> vis(n, m);
  vector<array<int, 2>> q, prev;
  auto push = [&](int i, int j) {
    q.push_back({i, j});
    vis[i][j] = true;
  };
  push(0, 0);
  for (int ans = 0; q.size(); ans++) {
    swap(prev, q);
    for (auto [i, j] : prev) {
      if (i == n - 1 && j == m - 1) {
        return println(ans);
      }
      auto d = a[i][j];
      for (int k = max(0, i - d), end = min(n - 1, i + d); k <= end; k++) {
        if (!vis[k][j]) {
          push(k, j);
        }
      }
      for (int k = max(0, j - d), end = min(m - 1, j + d); k <= end; k++) {
        if (!vis[i][k]) {
          push(i, k);
        }
      }
    }
    prev.clear();
  }
  println(-1);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
