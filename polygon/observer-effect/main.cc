/**
 * (c) 2024-2025 Diego Sogari
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
  bool found = false;
  for (int rem = n; rem > 2 && !found; rem--) {
    found = query(1);
  }
  auto ans = !found && query(n) || query(2);
  println('!', ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
