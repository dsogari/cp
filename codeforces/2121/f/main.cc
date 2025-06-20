/**
 * https://codeforces.com/contest/2121/submission/325213191
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
  auto f = [&](int x) {
    map<i64, int> sums = {{0, 1}};
    i64 sum = 0, ans = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] > x) {
        sums.clear();
      }
      sum += a[i];
      ans += sums[sum - s];
      sums[sum]++;
    }
    return ans;
  };
  auto ans = f(x) - f(x - 1);
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
