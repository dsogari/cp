/**
 * https://codeforces.com/contest/2005/submission/281925657
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
  int n, m;
  Mat(int n, int m) : vector<vector<T>>(n), n(n), m(m) {
    for (auto &row : *this) {
      row.resize(m);
    }
  }
  Mat(int n, int m, T s) : vector<vector<T>>(n, vector<T>(m, s)), n(n), m(m) {}
};

void solve(int t) {
  Int l, n, m;
  vector<Int> a(l);
  Mat<Int> b(n, m);
  unordered_set<int> valid;
  int mx = 0;
  for (; mx < l && valid.insert(a[mx]).second; mx++)
    ;
  Mat<bool> dp0(n + 1, m + 1), dp1(n + 1, m + 1);
  for (int k = mx - 1; k >= 0; k--) {
    for (int i = n - 1; i >= 0; i--) {
      for (int j = m - 1; j >= 0; j--) {
        dp1[i][j] = dp1[i + 1][j] | dp1[i][j + 1] |
                    (b[i][j] == a[k] && !dp0[i + 1][j + 1]);
      }
    }
    swap(dp0, dp1);
  }
  auto ans = dp0[0][0] ? 'T' : 'N';
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
