/**
 * https://codeforces.com/contest/2013/submission/282180042
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using namespace placeholders;
using i64 = int64_t;

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
using I64 = Num<i64>;

void solve(int t) {
  Int n;
  vector<I64> a(n);
  i64 mn = LLONG_MAX, mx = 0, pref = 0, suff = 0;
  for (int i = 0; i < n; i++) { // O(n)
    pref += a[i];
    suff += a[n - i - 1];
    mn = min(mn, pref / (i + 1));
    mx = max(mx, (suff + i) / (i + 1));
  }
  println(mx - mn);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
