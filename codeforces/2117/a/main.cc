/**
 * https://codeforces.com/contest/2117/submission/323411366
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
  Int n, x;
  vector<Int> a(n);
  for (int i = 0, j = -1; i < n; i++) {
    if (a[i] == 1) {
      if (j < 0) {
        j = i;
      } else if (i - j + 1 > x) {
        return println("NO");
      }
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
