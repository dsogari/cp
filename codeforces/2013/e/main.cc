/**
 * https://codeforces.com/contest/2013/submission/282188773
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

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

void solve(int t) {
  Int n;
  vector<Int> a(n);
  i64 ans = 0;
  int l = 0, prev = 0;
  for (int r = n; l < r; l++) { // O(n*log V)
    auto cur = prev;
    for (int i = l; i < r; i++) {
      auto d = gcd<int, int>(prev, a[i]);
      if (cur == 0 || d < cur) {
        cur = d;
        swap(a[i], a[l]);
      } else if (d == prev) {
        swap(a[i--], a[--r]);
      }
    }
    prev = cur;
    ans += cur;
  }
  for (int i = l; i < n; i++) { // O(n*log V)
    prev = gcd<int, int>(prev, a[i]);
    ans += prev;
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
