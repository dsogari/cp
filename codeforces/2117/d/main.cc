/**
 * https://codeforces.com/contest/2117/submission/323474987
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
  vector<Int> a(n);
  auto c = 2 * a[0] - a[1];
  if (c < 0 || c % (n + 1)) {
    return println("NO");
  }
  auto y = c / (n + 1);
  auto x = a[0] - n * y;
  if (x < 0) {
    return println("NO");
  }
  for (int i = 2; i < n; i++) {
    if (x * (i + 1) + y * (n - i) != a[i]) {
      return println("NO");
    }
  }
  println("YES");
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
