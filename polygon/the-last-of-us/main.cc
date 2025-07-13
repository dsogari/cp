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
    auto ans = reduce(a.begin(), a.end(), i64(0)); // O(n)
    return println(ans);
  }
  i64 ans = LLONG_MAX;
  for (int l = 0, m = 2 * k + 1; l < n; l++) { // O(n^3/k)
    vector<i64> dp(n + k + 1);
    for (int s = l, w = m; s < n; s += k + 1, w += m) {
      vector<i64> ndp(n + k + 1, LLONG_MAX);
      for (int r = s; r < n; r++) {
        ndp[r + k + 1] = min(ndp[r + k], dp[r] + a[r]); // skip or pick ai
      }
      if (max({+n, n - l + k, s + 1 + k}) <= w) {
        ans = min(ans, ndp[min(w, n + k)]); // consider ai as the last one
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
