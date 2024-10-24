/**
 * https://codeforces.com/contest/2025/submission/286300042
 *
 * (c) 2024 Diego Sogari
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

void solve(int t) {
  Int n, m;
  vector<Int> r(n);
  vector checks(m + 1, vector<array<int, 2>>(m + 1));
  for (int i = 0, j = 0; i < n; i++) { // O(n)
    if (r[i] == 0) {
      j++;
    } else {
      checks[j][abs(r[i])][r[i] < 0]++;
    }
  }
  for (int i = 0; i <= m; i++) { // O(m^2)
    for (int j = 0; j < m; j++) {
      checks[i][j + 1][0] += checks[i][j][0];
      checks[i][j + 1][1] += checks[i][j][1];
    }
  }
  vector<int> dp0(m + 1), dp1(m + 1);
  int ans = 0;
  for (int i = 0; i <= m; i++) { // O(m^2)
    for (int j = 0; j <= m; j++) {
      if (i + j <= m) {
        int ca = checks[i + j][i][0];
        int cb = checks[i + j][j][1];
        dp1[j] = max(dp0[j], j > 0 ? dp1[j - 1] : 0) + ca + cb;
      }
    }
    ans = max(ans, dp1[m - i]);
    swap(dp0, dp1);
  }
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
#ifdef ONLINE_JUDGE
  int t = 1;
#else
  Int t;
#endif
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
