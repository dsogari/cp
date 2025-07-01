/**
 * https://codeforces.com/contest/2114/submission/326626520
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
  Int n;
  vector<array<Int, 2>> a(n);
  if (n == 1) {
    return println(1);
  }
  set<array<int, 2>> xs, ys;
  auto add = [&](int x, int y) {
    xs.insert({x, y});
    ys.insert({y, x});
  };
  auto rem = [&](int x, int y) {
    xs.erase({x, y});
    ys.erase({y, x});
  };
  for (auto &&[x, y] : a) {
    add(x, y);
  }
  i64 ans = LLONG_MAX;
  auto f = [&]() {
    auto x1 = (*xs.begin())[0];
    auto x2 = (*xs.rbegin())[0];
    auto y1 = (*ys.begin())[0];
    auto y2 = (*ys.rbegin())[0];
    auto w = i64(x2 - x1 + 1);
    auto h = i64(y2 - y1 + 1);
    auto area = w * h;
    if (area < n) {
      area += min(w, h); // expand to fit
    }
    ans = min(ans, area);
  };
  auto f2 = [&](const array<int, 2> &cell, bool isy) {
    auto [x, y] = cell;
    if (isy) {
      swap(x, y);
    }
    rem(x, y);
    f();
    add(x, y);
  };
  f();
  f2(*xs.begin(), false);
  f2(*xs.rbegin(), false);
  f2(*ys.begin(), true);
  f2(*ys.rbegin(), true);
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
