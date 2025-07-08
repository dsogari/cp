/**
 * https://codeforces.com/contest/2091/submission/328157586
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

using Int = Number<int>;

void solve(int t) {
  Int s, k;
  if (s % k == 0) {
    return println(k);
  }
  if (s > k * k) {
    return println(max(1, k - 2));
  }
  vector<bool> dp(s + 1);
  dp[0] = true;
  for (bool back = false; k > 1; back = !back, k--) {
    vector<bool> ndp(s + 1);
    if (back) {
      for (int i = s - k; i >= 0; i--) {
        ndp[i] = dp[i + k] | ndp[i + k];
      }
    } else {
      for (int i = k; i <= s; i++) {
        ndp[i] = dp[i - k] | ndp[i - k];
      }
      if (ndp[s]) {
        return println(k);
      }
    }
    swap(dp, ndp);
  }
  println(1);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
