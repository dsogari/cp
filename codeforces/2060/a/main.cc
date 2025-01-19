/**
 * https://codeforces.com/contest/2060/submission/301744557
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
  Int a, b, c, d;
  int x = a + b;
  int ans = 1 + (b + x == c) + (x + c == d);
  x = c - b;
  ans = max(ans, 1 + (a + b == x) + (x + c == d));
  x = d - c;
  ans = max(ans, 1 + (a + b == x) + (b + x == c));
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
