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

template <typename T>
vector<vector<T>> tsp(const vector<vector<T>> &g) { // O(n^2*2^n)
  int n = g.size(), s = 1 << n;
  vector<vector<T>> dp(n, vector<T>(s, numeric_limits<T>::max()));
  for (int i = 0; i < n; i++) {
    dp[i][1 << i] = {};
  }
  for (int i = 1; i < s; i++) {       // all subsets in increasing size
    for (int j = 0; j < n; j++) {     // select last node in path
      if ((1 << j) & i) {             // last node is in subset?
        for (int k = 0; k < n; k++) { // select next node in path
          if ((1 << k) & ~i) {        // next node is not in subset?
            int mask = (1 << k) | i;
            dp[k][mask] = min(dp[k][mask], dp[j][i] + g[j][k]);
          }
        }
      }
    }
  }
  return dp;
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
  n++, m++;
  auto getsums = [](auto &g, int n, int m, int c) { // O(n^2*m)
    vector<vector<int>> sums(n, vector<int>(n));
    for (int i = 0; i < n - 1; i++) {
      for (int j = i + 1; j < n; j++) {
        for (int k = 0; k < m; k++) {
          if (k != c) {
            sums[i][j] += abs(g(i, k) - g(j, k));
          }
        }
        sums[j][i] = sums[i][j];
      }
    }
    return sums;
  };
  auto f1 = [&](int i, int j) { return g[i][j]; };
  auto f2 = [&](int i, int j) { return g[j][i]; };
  vector<vector<int>> rdps(m), cdps(n);
  for (int j = 0; j < m; j++) { // O(m*n^2*2^n)
    auto dp = tsp(getsums(f1, n, m, j));
    rdps[j].resize(n);
    // for (int i = 0; i < n; i++) {
    //   rdps[j][i] = min(rdps[j][i], dp[]);
    // }
  }
  for (int i = 0; i < n; i++) { // O(n*m^2*2^m)
    auto dp = tsp(getsums(f2, m, n, i));
    vector<int> abc;
    cdps[i] = abc;
  }
  int ans = INT_MAX;
  for (int i = 0, rmask = (1 << n) - 1; i < n; i++) {
    for (int j = 0, cmask = (1 << m) - 1; j < m; j++) {
      ans = min(ans, rdps[j][rmask ^ (1 << i)] + cdps[i][cmask ^ (1 << j)]);
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
