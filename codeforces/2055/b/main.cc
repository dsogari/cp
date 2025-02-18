/**
 * https://codeforces.com/contest/2055/submission/300683307
 *
 * Greedy
 *
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

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
  int c = 0, mn = INT_MAX;
  for (int i = 0; i < n; i++) {
    if (a[i] < b[i]) {
      if (c) {
        println("NO");
        return;
      }
      c = b[i] - a[i];
    } else {
      mn = min(mn, a[i] - b[i]);
    }
  }
  auto ans = c <= mn ? "YES" : "NO";
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
