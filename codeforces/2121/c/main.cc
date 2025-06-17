/**
 * https://codeforces.com/contest/2121/submission/324900521
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

template <typename T> struct Mat : vector<vector<T>> {
  int n, m;
  Mat(int n, int m) : vector<vector<T>>(n), n(n), m(m) {
    ranges::for_each(*this, [m](auto &row) { row.resize(m); });
  }
  Mat(int n, int m, T s) : vector<vector<T>>(n, vector<T>(m, s)), n(n), m(m) {}
};

void solve(int t) {
  Int n, m;
  Mat<Int> g(n, m);
  vector<int> rows(n), cols(m);
  int mx = 0, row = -1, col = -1;
  for (auto &&row : g) {
    mx = max(mx, +*ranges::max_element(row));
  }
  for (int i = 0, c = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (g[i][j] == mx) {
        if (rows[i]++) {
          if (row < 0) {
            row = i;
          } else if (row != i) {
            return println(mx);
          }
        }
        if (cols[j]++) {
          if (col < 0) {
            col = j;
          } else if (col != j) {
            return println(mx);
          }
        }
        if (rows[i] == 1 && cols[j] == 1 && c++ > 1) {
          return println(mx);
        }
      }
    }
  }
  if (row >= 0 && col >= 0) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (g[i][j] == mx && row != i && col != j) {
          return println(mx);
        }
      }
    }
  }
  println(mx - 1);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
