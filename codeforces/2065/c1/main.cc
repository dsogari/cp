/**
 * https://codeforces.com/contest/2065/submission/305209954
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

const less<int> lt;

void solve(int t) {
  Int n, m;
  vector<Int> a(n), b(m);
  ranges::sort(b);
  a[0] = min(+a[0], b[0] - a[0]);
  for (int i = 1; i < n; i++) { // O(n*log n)
    auto j = ranges::lower_bound(b, a[i] + a[i - 1], lt) - b.begin();
    if (a[i] < a[i - 1]) {
      if (j == m) {
        return println("NO");
      }
      a[i] = b[j] - a[i];
    } else if (j < m) {
      a[i] = min(+a[i], b[j] - a[i]);
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
