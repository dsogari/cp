/**
 * https://codeforces.com/contest/2091/submission/328136726
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
  vector<int> dp(k + 1, -1);
  dp[0] = 0;
  for (int i = k; i > 1; i -= 2) { // O(k^2)
    vector<int> ndp(i - 1, -1);
    for (int j = 0, mx = 0; j <= i; j++) {
      mx = max(mx - 1, dp[j]); // decrease max remainder or take the greater one
      if (mx < 0) {
        continue; // no remainders reachable
      }
      if ((s - j) % i <= mx) {
        return println(i);
      }
      int l = (j + 1) % (i - 1);                // starting point for mod k-2
      ndp[l] = 2 * ((s - j) / i - 1) + (l < j); // reachable remainders mod k-2
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
