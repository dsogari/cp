/**
 * (c) 2024 Diego Sogari
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

bool simulate(int n, int &x, int d, int p) {
  return p == exchange(x, d ? x % n + 1 : n - (n - x + 1) % n);
}

void solve(int t) {
  Int n;
#ifndef ONLINE_JUDGE
  Int x, d;
#endif
  auto query = [&](int p) -> bool {
    println('?', p);
#ifndef ONLINE_JUDGE
    return simulate(n, x, d, p);
#else
    return Int();
#endif
  };
  int p = 1;
  while (!query(p)) {
    p = (p + 1) % n + 1;
  }
  auto ans = query(p % n + 1);
  println('!', ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
