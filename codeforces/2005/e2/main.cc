/**
 * https://codeforces.com/contest/2005/submission/282548881
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
  vector<int> pos(n * m + 1, -1);
  for (int i = 0; i < l && pos[a[i]] < 0; i++) {
    pos[a[i]] = i;
  }
  vector<array<int, 2>> dp0(m + 1, {INT_MAX, INT_MAX});
  auto dp1 = dp0;
  for (int i = n - 1; i >= 0; i--) { // O(n*m)
    for (int j = m - 1; j >= 0; j--) {
      dp1[j][0] = min(dp0[j][0], dp1[j + 1][0]);
      dp1[j][1] = min(dp0[j][1], dp1[j + 1][1]);
      auto k = pos[b[i][j]];
      if (k >= 0) {
        if (k < dp1[j][0] && k % 2 == 0 && k + 1 < dp0[j + 1][1]) {
          dp1[j][0] = k;
        }
        if (k < dp1[j][1] && k % 2 == 1 && k + 1 < dp0[j + 1][0]) {
          dp1[j][1] = k;
        }
      }
    }
    swap(dp0, dp1);
  }
  auto ans = dp0[0][0] == 0 ? 'T' : 'N';
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
