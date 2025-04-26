/**
 * https://codeforces.com/contest/2106/submission/317050191
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

void solve(int t) {
  Int n, k;
  vector<Int> a(n), b(n);
  int mn = INT_MAX, mx = INT_MIN, sum = -1;
  for (int i = 0; i < n; i++) {
    if (b[i] >= 0) {
      const auto s = a[i] + b[i];
      if (sum < 0) {
        sum = s;
      } else if (s != sum) {
        return println(0);
      }
    } else {
      mn = min(mn, +a[i]);
      mx = max(mx, +a[i]);
    }
  }
  int ans = 0;
  if (sum < 0) {
    ans = 1 + mn + k - mx; // ans > 0 && ans <= k
  } else if (mn == INT_MAX || mn + k >= sum && mx <= sum) {
    ans = 1;
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
