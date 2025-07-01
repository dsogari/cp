/**
 * https://codeforces.com/contest/2114/submission/326811339
 *
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
  vector<int> b(n);
  for (int i = 0; i < n; i++) {         // O(n*log A)
    b[i] = countr_zero<unsigned>(a[i]); // get base-2 exponent
  }
  auto f = [&](int e1, int e2, bool same) {
    return (1 << e1) - (same && e1 > e2 ? (1 << (e2 + 1)) - 1 : 0);
  };
  vector<i64> pref(n + 1), suff(n + 1);
  for (int i = 0, prev = 0; i < n; i++) { // O(n)
    auto odd = a[i] >> b[i];
    pref[i + 1] = pref[i] + f(b[i], i == 0 ? 0 : b[i - 1], odd == prev);
    prev = odd;
  }
  for (int i = n - 1, prev = 0; i >= 0; i--) { // O(n)
    auto odd = a[i] >> b[i];
    suff[i] = suff[i + 1] + f(b[i], i + 1 == n ? 0 : b[i + 1], odd == prev);
    prev = odd;
  }
  i64 mx = 0;
  for (int i = 0; i < n; i++) { // O(n)
    mx = max(mx, suff[0] - suff[i] + (1 << b[i]) + pref[n] - pref[i + 1]);
  }
  auto ans = k <= mx ? "YES" : "NO";
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
