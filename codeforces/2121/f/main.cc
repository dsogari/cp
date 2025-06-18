/**
 * https://codeforces.com/contest/2121/submission/325045084
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
using I64 = Number<i64>;

void solve(int t) {
  Int n;
  I64 s;
  Int x;
  vector<Int> a(n);
  map<i64, int> sums1 = {{0, 1}}, sums2 = {{0, 1}};
  i64 sum1 = 0, sum2 = 0, ans = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] > x) {
      sums1.clear();
      sum1 = 0;
    } else {
      sum1 += a[i];
      ans += sums1[sum1 - s];
    }
    if (a[i] >= x) {
      sums2.clear();
      sum2 = 0;
    } else {
      sum2 += a[i];
      ans -= sums2[sum2 - s];
    }
    sums1[sum1]++;
    sums2[sum2]++;
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
