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
  vector<int> rows(n, m);
  vector<array<int, 3>> prev(n * m / 2 + 1);
  queue<array<int, 3>> q;
  for (int i = 0; i < n; i++) {
    q.push({i, 0, 1});
    q.push({i, m - 1, -1});
  }
  int rem = n * m / 2;
  while (q.size()) {
    auto [i1, j1, k1] = q.front();
    auto [i2, j2, k2] = exchange(prev[a[i1][j1]], q.front());
    q.pop();
    if (k2) {
      rem--;
      if (--rows[i1] > 1) {
        q.push({i1, j1 + k1, k1});
      }
      if (--rows[i2] > 1) {
        q.push({i2, j2 + k2, k2});
      }
    }
  }
  auto ans = rem ? "NO" : "YES";
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
