/**
 * https://codeforces.com/contest/2126/submission/329397514
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
  Int n, k;
  vector<Int> a(n);
  auto x = a[k - 1];
  ranges::sort(a);
  int i = ranges::upper_bound(a, x) - a.begin();
  for (int l = 0; i < n; i++) {
    auto d = a[i] - x;
    if (d > x - l) {
      return println("NO");
    }
    l += d;
    x = a[i];
  }
  println("YES");
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
