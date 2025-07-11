/**
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

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

using Int = Number<int>;

void solve(int t) {
  Int n, k;
  vector<Int> a(n);
  if (k == 0) {
    auto ans = reduce(a.begin(), a.end(), i64(0));
    return println(ans);
  }
  i64 ans = LLONG_MAX;
  for (int l = 0; l < n; ++l) { // O(n^3)
    vector dp(n + 1, vector<i64>(n + 1, LLONG_MAX));
    dp[l][0] = 0;
    for (int r = l; r < n; ++r) {
      for (int c = 0; c < n; ++c) {
        auto &cur = dp[r][c];
        if (cur == LLONG_MAX) {
          break; // not reachable
        }
        dp[r + 1][c] = min(dp[r + 1][c], cur); // skipping ai
        if (r + 1 + k < n) {
          auto &next = dp[r + 1 + k][c + 1];
          next = min(next, cur + a[r]); // picking ai
        }
        if (max({+n, n - l + k, r + 1 + k}) <= (2 * k + 1) * (c + 1)) {
          ans = min(ans, cur + a[r]); // considering ai as the last one
        }
      }
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
