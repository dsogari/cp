/**
 * https://codeforces.com/contest/2059/submission/304221182
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
  Int n;
  Mat<Int> a(n, n);
  for (int i = 0; i < n; i++) { // O(n^2)
    a[i].push_back(0);
    for (int j = n - 1; j >= 0; j--) {
      a[i][j] = min(+n, a[i][j] + a[i][j + 1]);
    }
  }
  for (int j = n - 1; j >= 0; j--) { // O(n^2)
    vector<int> cnt(n + 1);
    for (int i = 0; i < n; i++) {
      a[i][j] = (a[i][j] != n - j) + a[i][j + 1];
      cnt[a[i][j]]++;
    }
    for (int i = n; i > 0; i--) {
      if (cnt[i] > n - i) {
        return println(n - j);
      }
      cnt[i - 1] += cnt[i];
    }
  }
  println(n);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
