/**
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

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

void solve(int t) {
  Int n, s;
  vector<Int> a(n), b(n);
  ranges::sort(a);
  ranges::sort(b);
  int ans = INT_MAX;
  for (int i = 0, j = n - 1; i < n && j >= 0 && ans > 0;) {
    auto sum = a[i] + b[j];
    ans = min(ans, abs(sum - s));
    sum < s ? i++ : j--;
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
