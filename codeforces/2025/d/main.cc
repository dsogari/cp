/**
 * https://codeforces.com/contest/2025/submission/285935817
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
  vector<array<vector<int>, 2>> checks(m + 1);
  for (int i = 0, j = 0; i < n; i++) { // O(n)
    if (r[i] == 0) {
      j++;
    } else {
      checks[j][r[i] < 0].push_back(abs(r[i]));
    }
  }
  for (int i = 0; i <= m; i++) { // O(n*log n)
    ranges::sort(checks[i][0]);
    ranges::sort(checks[i][1]);
  }
  vector<int> dp0(m + 1), dp1(m + 1);
  int ans = 0;
  for (int i = 0; i <= m; i++) { // O(m^2*log n)
    for (int j = 0; j <= m; j++) {
      if (i + j <= m) {
        auto &[a, b] = checks[i + j];
        int cnta = ranges::upper_bound(a, i) - a.begin();
        int cntb = ranges::upper_bound(b, j) - b.begin();
        dp1[j] = max(dp0[j], j > 0 ? dp1[j - 1] : 0) + cnta + cntb;
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
