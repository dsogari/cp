/**
 * https://codeforces.com/contest/2060/submission/302303333
 *
 * Sorting; greedy
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
  vector<int> pairof(2 * n + 1);
  bool even = true;
  for (int i = 0; i < n; i++) { // O(n)
    auto [mn, mx] = minmax(a[i], b[i]);
    pairof[mn] = mx;
    even ^= a[i] > b[i];
  }
  for (int i = 0, x = 0, y, prev = 0; i < n; i++) { // O(n)
    while (!(y = pairof[++x]))
      ; // find next pair
    if (prev > y) {
      println("NO");
      return;
    }
    even |= prev < x && i % 2; // odd number of flips before i-th pair
    prev = y;
  }
  auto ans = even || n % 2 ? "YES" : "NO";
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
