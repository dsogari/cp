/**
 * https://codeforces.com/contest/2065/submission/305588926
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
  Int n, m, k;
  auto b = abs(n - m);
  if (k < b || k > max(n, m)) {
    return println(-1);
  }
  string ans(n + m, n < m ? '0' : '1');
  for (int i = 0; i < n + m - (k - b); i++) {
    ans[i] ^= i < k || (i - k) & 1;
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
