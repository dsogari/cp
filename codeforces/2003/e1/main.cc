/**
 * https://codeforces.com/contest/2003/submission/278699662
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#define debug
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

void solve(int t) { // O(m)
  Int n, m;
  vector<array<Int, 2>> intervals(m);
  int ans = n * (n - 1) / 2, zeros = 0, ones = 0, L = 1, R = 0, s = 0;
  for (int i = 0, j = m - 1; i <= j;) { // O(m)
    if (i == j) {
      auto [l, r] = intervals[i];
      ans -= zeros * (l - L) + ones * (R - r);
      L = l, R = r, s = 1;
      break;
    }
    {
      auto [l, r] = intervals[i++];
      ans -= zeros * (l - L) + (zeros + 1) * (r - l);
      zeros++, L = r + 1;
    }
    {
      auto [l, r] = intervals[j--];
      ans -= ones * (R - r) + (ones + 1) * (r - l);
      ones++, R = l - 1;
    }
  }
  auto [mn, mx] = minmax(zeros, ones);
  ans -= (mn + R - L + 1 - s) * (mx + s);
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
