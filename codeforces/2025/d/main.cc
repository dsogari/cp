/**
 * https://codeforces.com/contest/2025/submission/286363048
 *
 * Brute force; DP
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
  r.push_back(0);
  vector<int> checks(m + 1), diff(m + 1);
  for (int i = 0, k = 0; i <= n; i++) { // O(m^2+n)
    if (r[i] == 0) {
      for (int j = 0; j < k; j++) {
        diff[j + 1] += diff[j];
      }
      for (int j = 0; j <= k; j++) {
        checks[j] += exchange(diff[j], 0);
      }
      for (int j = ++k; j > 0; j--) {
        checks[j] = max(checks[j], checks[j - 1]);
      }
    } else if (abs(r[i]) <= k) {
      if (r[i] > 0) {
        diff[r[i]]++;
      } else {
        diff[0]++;
        diff[k + r[i] + 1]--;
      }
    }
  }
  int ans = *ranges::max_element(checks);
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
