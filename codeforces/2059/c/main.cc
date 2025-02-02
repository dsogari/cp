/**
 * https://codeforces.com/contest/2059/submission/304184855
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
    for (auto &row : *this) {
      row.resize(m);
    }
  }
  Mat(int n, int m, T s) : vector<vector<T>>(n, vector<T>(m, s)), n(n), m(m) {}
};

void solve(int t) {
  Int n;
  Mat<Int> g(n, n);
  vector<int> len(n);
  for (int i = 0; i < n; i++) { // O(n^2)
    for (int j = n - 1; j >= 0 && g[i][j] == 1; j--) {
      len[i] = n - j;
    }
  }
  ranges::sort(len); // O(n*log n)
  int ans = 0;
  for (int i = 0; i < n; i++) { // O(n)
    ans = 1 + min(ans, len[i]);
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
