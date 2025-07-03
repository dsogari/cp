/**
 * https://codeforces.com/contest/2114/submission/327198218
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
    a[i] >>= b[i];                      // get first odd factor
  }
  auto f = [&](int i, int j) {
    return a[i] == a[j] && b[i] > b[j] ? (1 << (b[j] + 1)) - 1 : 0;
  };
  vector<i64> pref(n + 1), suff(n + 1);
  for (int i = 0, j = n - 1; i < n; i++, j--) { // O(n)
    pref[i + 1] = pref[i] + (1 << b[i]) - (i > 0 ? f(i, i - 1) : 0);
    suff[j] = suff[j + 1] + (1 << b[j]) - (j + 1 < n ? f(j, j + 1) : 0);
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
