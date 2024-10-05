/**
 * https://codeforces.com/contest/2008/submission/280760713
 *
 * (c) 2024 Diego Sogari
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
  int offset = -(a[0] >= k);
  if (n > 1) {
    offset = n - 1;
    int d = reduce(a.begin(), a.end(), 0, gcd<int, int>);
    if (d > 1) {
      offset = min(offset, (k - 1) / (d - 1));
    }
  }
  println(k + offset);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
