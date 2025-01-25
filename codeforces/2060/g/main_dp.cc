/**
 * https://codeforces.com/contest/2060/submission/302300580
 *
 * Sorting; DP
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

struct Iota : vector<int> {
  Iota(int n, int s = 0) : vector<int>(n) { iota(begin(), end(), s); }
  Iota(int n, auto &&f, int s = 0) : Iota(n, s) { ranges::sort(*this, f); }
};

void solve(int t) {
  Int n;
  vector<Int> a(n), b(n);
  auto cmp = [&](int i, int j) { return min(a[i], b[i]) < min(a[j], b[j]); };
  Iota idx(n, cmp);
  array<bool, 4> dp = {true, false, false, true};
  for (int i = 1; i < n; i++) {
    decltype(dp) ndp = {};
    auto j = idx[i - 1], k = idx[i];
    if (a[j] < a[k] && b[j] < b[k]) { // keep flipped state
      ndp[0] |= dp[0];                // flip none
      ndp[1] |= dp[1];                // flip none
      ndp[2] |= dp[3];                // flip both
      ndp[3] |= dp[2];                // flip both
    }
    if (a[j] < b[k] && b[j] < a[k]) { // change flipped state
      ndp[0] |= dp[2];                // flip prvious only
      ndp[1] |= dp[3];                // flip prvious only
      ndp[2] |= dp[1];                // flip current only
      ndp[3] |= dp[0];                // flip current only
    }
    dp = ndp;
  }
  auto ans = dp[0] || dp[2] ? "YES" : "NO";
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
