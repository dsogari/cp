/**
 * https://codeforces.com/contest/2121/submission/325214803
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
  Int n;
  vector<Int> a(n), b(n);
  vector<array<int, 2>> ans;
  auto f = [&](auto &a, auto &b, int type, int i, int j) {
    swap(a[i], b[j]);
    ans.push_back({type, i});
  };
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - 1 - i; j++) {
      if (a[j] > a[j + 1]) {
        f(a, a, 1, j, j + 1);
      }
      if (b[j] > b[j + 1]) {
        f(b, b, 2, j, j + 1);
      }
    }
  }
  for (int i = 0; i < n; i++) {
    if (a[i] > b[i]) {
      f(a, b, 3, i, i);
    }
  }
  println(ans.size());
  for (auto &&[type, i] : ans) {
    println(type, i + 1);
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
