/**
 * https://codeforces.com/contest/2059/submission/304155585
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
  Int n, k;
  vector<Int> a(n);
  int ans = 1;
  if (n == k) {
    for (int i = 1; i < n; i += 2, ans++) { // O(n)
      if (a[i] != ans) {
        break;
      }
    }
  } else {
    auto cmp = [](int a) { return a != 1; };
    int i = find_if(a.begin() + 1, a.end(), cmp) - a.begin(); // O(n)
    if (i > n - k + 1) {
      ans = 2;
    }
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
