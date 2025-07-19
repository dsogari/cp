/**
 * https://codeforces.com/contest/2126/submission/329542802
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
  vector<Int> p(n), s(n);
  if (p[n - 1] != s[0]) {
    return println("NO");
  }
  for (int i = 1; i < n; i++) { // O(n log A)
    if (p[i - 1] % p[i] || s[i] % s[i - 1] ||
        (min(p[i], s[i - 1]) < gcd(+p[i - 1], +s[i]))) {
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
