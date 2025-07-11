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
  for (int l = 0; l < n; ++l) { // O(n^3/k)
    vector<i64> dp(n + k + 1, LLONG_MAX);
    dp[l] = 0;
    for (int s = l, b = k + 1; s < n; s += k + 1, b += 2 * k + 1) {
      vector<i64> ndp(n + k + 1, LLONG_MAX);
      for (int r = s; r < n; ++r) {
        dp[r + 1] = min(dp[r + 1], dp[r]);      // skipping ai
        auto x = ndp[r + 1 + k] = dp[r] + a[r]; // picking ai
        if (max({n - k, n - l, r + 1}) <= b) {
          ans = min(ans, x); // considering ai as the last one
        }
      }
      swap(dp, ndp);
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
