/**
 * https://codeforces.com/contest/2106/submission/317321384
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
  Int n, m;
  vector<Int> a(n), b(m);
  vector<int> pref(m), suff(m);
  for (int j1 = 0, j2 = m - 1, i1 = 0, i2 = n - 1; j1 < m; j1++, j2--) {
    while (i1 < n && a[i1] < b[j1]) i1++;
    while (i2 >= 0 && a[i2] < b[j2]) i2--;
    pref[j1] = i1++;
    suff[j2] = i2--;
  }
  if (pref.back() < n) {
    return println(0);
  }
  int ans = INT_MAX;
  for (int i = 0; i < m; i++) {
    auto left = i > 0 ? pref[i - 1] : -1;
    auto right = i < m - 1 ? suff[i + 1] : +n;
    if (left < right) {
      ans = min(ans, +b[i]);
    }
  }
  if (ans == INT_MAX) {
    ans = -1;
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
