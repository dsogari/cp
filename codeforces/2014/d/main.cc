/**
 * https://codeforces.com/contest/2014/submission/282480647
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

void solve(int t) {
  Int n, d, k;
  vector<array<Int, 2>> a(k);
  vector<int> left(n + 1), right(n + 1);
  for (auto [l, r] : a) {
    left[l]++;
    right[r]++;
  }
  int b = 1, m = 1;
  for (int i = 1, w = 0, mx = 0, mn = k; i <= n; i++) { // O(n)
    w += left[i];
    if (i >= d) {
      int j = i - d + 1;
      if (w > mx) {
        mx = w, b = j;
      }
      if (w < mn) {
        mn = w, m = j;
      }
      w -= right[j];
    }
  }
  println(b, m);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
