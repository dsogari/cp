/**
 * https://codeforces.com/contest/2123/submission/327122716
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
  Int n;
  vector<Int> a(n);
  string ans(n, '1');
  vector<int> prefmin(n), suffmax(n);
  for (int i = 0, j = n - 1, mn = INT_MAX, mx = INT_MIN; i < n; i++, j--) {
    prefmin[i] = mn = min(mn, +a[i]);
    suffmax[j] = mx = max(mx, +a[j]);
  }
  for (int i = 1; i < n - 1; i++) {
    ans[i] = a[i] > suffmax[i + 1] || a[i] < prefmin[i - 1] ? '1' : '0';
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
