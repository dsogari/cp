/**
 * https://codeforces.com/contest/2000/submission/276466032
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
  Int n, k;
  vector<array<Int, 2>> rect(n);
  vector<int> dp(k + 1, INT_MAX);
  dp[0] = 0;
  for (auto &[w, h] : rect) { // O(n*k^2)
    vector<int> cost(min(+k, w + h) + 1);
    for (int x = 1; x < cost.size(); x++) {
      auto extra = w + h - x;
      auto side = min({+w, +h, extra / 2}); // maximize area to be cleared
      cost[x] = w * h - side * (extra - side);
    }
    for (int j = k; j > 0; j--) {
      for (int x = min(j, w + h); x > 0 && dp[j - x] < INT_MAX; x--) {
        dp[j] = min(dp[j], dp[j - x] + cost[x]);
      }
    }
  }
  int ans = dp[k] < INT_MAX ? dp[k] : -1;
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
