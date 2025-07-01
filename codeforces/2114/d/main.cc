/**
 * https://codeforces.com/contest/2114/submission/326800176
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

const greater<int> gt;

void solve(int t) {
  Int n;
  vector<array<Int, 2>> a(n);
  if (n == 1) {
    return println(1);
  }
  i64 ans = LLONG_MAX;
  auto f = [&](int x1, int x2, int y1, int y2) {
    auto w = i64(x2 - x1 + 1);
    auto h = i64(y2 - y1 + 1);
    auto area = w * h;
    if (area < n) {
      area += min(w, h); // expand to fit
    }
    ans = min(ans, area);
  };
  array<int, 3> xmin = {INT_MAX, INT_MAX}, xmax = {}, ymin = xmin, ymax = xmax;
  for (auto &&[x, y] : a) { // O(n)
    xmin[2] = xmax[2] = x;
    ymin[2] = ymax[2] = y;
    ranges::sort(xmin);
    ranges::sort(xmax, gt);
    ranges::sort(ymin);
    ranges::sort(ymax, gt);
  }
  f(xmin[0], xmax[0], ymin[0], ymax[0]);
  for (auto &&[x, y] : a) { // O(n)
    f(xmin[x == xmin[0]], xmax[x == xmax[0]], ymin[y == ymin[0]],
      ymax[y == ymax[0]]);
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
