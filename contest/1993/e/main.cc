/**
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

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

template <typename T> struct Mat : vector<vector<T>> {
  const int n, m;
  Mat(int n, int m) : vector<vector<T>>(n), n(n), m(m) {
    for (auto &row : *this) {
      row.resize(m);
    }
  }
  Mat(int n, int m, T s) : vector<vector<T>>(n, vector<T>(m, s)), n(n), m(m) {}
};

void solve(int t) {
  Int n, m;
  Mat<Int> g(n, m);
  g.emplace_back(m + 1, 0); // add row
  for (int i = 0; i < n; i++) {
    g[i].push_back(0); // add column
    for (int j = 0; j < m; j++) {
      g[i][m] ^= g[i][j]; // last column
      g[n][j] ^= g[i][j]; // last row
      g[n][m] ^= g[i][j]; // bottom-right corner
    }
  }
  auto getsums = [](auto &g, int n, int m) { // O(n^2*m)
    vector<vector<int>> sums(n, vector<int>(n + 1));
    for (int i = 0; i < n; i++) {
      for (int k = i + 1; k <= n; k++) {
        for (int j = 0; j <= m; j++) {
          sums[i][k] += abs(g(i, j) - g(k, j));
        }
      }
    }
    return sums;
  };
  auto f1 = [&](int i, int j) { return g[i][j]; };
  auto f2 = [&](int i, int j) { return g[j][i]; };
  auto rdsums = getsums(f1, n, m);
  auto cdsums = getsums(f2, m, n);
  auto getbest = [&](int r, int c) { // O(?)
    int sum = 0;
    // TSP
    return sum;
  };
  int ans = INT_MAX;
  for (int i = 0; i <= n; i++) { // O(?)
    for (int j = 0; j <= m; j++) {
      ans = min(ans, getbest(i, j));
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
