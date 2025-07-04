/**
 * https://codeforces.com/contest/2121/submission/325216361
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
  int ans = 0, total = 0;
  for (auto &&row : g) {
    ans = max(ans, +*ranges::max_element(row));
  }
  vector<int> rowc(n), colc(m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (g[i][j] == ans) {
        rowc[i]++;
        colc[j]++;
        total++;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (rowc[i] + colc[j] - (g[i][j] == ans) == total) {
        return println(ans - 1);
      }
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
