/**
 * https://codeforces.com/contest/2093/submission/327649906
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

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

template <typename T> struct String : basic_string<T> {
  using basic_string<T>::basic_string;
  String() { cin >> *this; }
};

using Int = Number<int>;
using Str = String<char>;

template <typename T> struct Mat : vector<vector<T>> {
  int n, m;
  Mat(int n, int m) : vector<vector<T>>(n), n(n), m(m) {
    ranges::for_each(*this, [m](auto &row) { row.resize(m); });
  }
  Mat(int n, int m, T s) : vector<vector<T>>(n, vector<T>(m, s)), n(n), m(m) {}
};

void solve(int t) {
  Int n, m;
  vector<Str> a(n);
  Mat<Str> b(m, n);
  vector<bool> good(n);
  int best = 0;
  for (int j = 0; j < m; j++) { // O(m*n)
    int cur = 0;
    for (int i = 0; i < n; i++) {
      auto ok = a[i] == b[j][i];
      good[i] = good[i] || ok;
      cur += ok;
    }
    best = max(best, cur);
  }
  auto bad = ranges::count(good, false);
  auto ans = bad ? -1 : n + 2 * (n - best);
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
