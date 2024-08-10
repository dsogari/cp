/**
 * https://codeforces.com/contest/1993/submission/275637276
 *
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

template <typename T> struct TSP : vector<vector<T>> {
  TSP(const vector<vector<T>> &g) : TSP(g, g.size()) {}
  TSP(const vector<vector<T>> &g, int n)
      : vector<vector<T>>(n, vector<T>(1 << n, numeric_limits<T>::max())) {
    for (int i = 0; i < n; i++) {
      (*this)[i][1 << i] = {}; // shortest path ending at i, including only i
    }
    for (int i = 1; i < 1 << n; i++) {  // all subsets in increasing size
      for (int j = 0; j < n; j++) {     // select last node in path
        if ((1 << j) & i) {             // last node is in subset?
          for (int k = 0; k < n; k++) { // select next node in path
            if ((1 << k) & ~i) {        // next node is not in subset?
              int mask = (1 << k) | i;  // include next node in subset
              (*this)[k][mask] = min((*this)[k][mask], (*this)[j][i] + g[j][k]);
            }
          }
        }
      }
    }
  }
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
  auto getbest = [](const auto &dp, int n) { // O(n^2)
    vector<int> ans(n, INT_MAX);
    for (int i = 0; i < n; i++) {
      int ix = ((1 << n) - 1) ^ (1 << i); // excluding i
      for (int j = 0; j < n; j++) {
        ans[i] = min(ans[i], dp[j][ix]); // ending at j
      }
    }
    return ans;
  };
  auto f1 = [&](int i, int j) { return g[i][j]; };
  auto f2 = [&](int i, int j) { return g[j][i]; };
  vector<vector<int>> rdps(m), cdps(n);
  for (int j = 0; j < m; j++) {       // O(m*n^2*2^n)
    auto sums = getsums(f1, n, m, j); // excluding column j
    rdps[j] = getbest(TSP(sums), n);
  }
  for (int i = 0; i < n; i++) {       // O(n*m^2*2^m)
    auto sums = getsums(f2, m, n, i); // excluding row i
    cdps[i] = getbest(TSP(sums), m);
  }
  int ans = INT_MAX;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      ans = min(ans, rdps[j][i] + cdps[i][j]);
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
