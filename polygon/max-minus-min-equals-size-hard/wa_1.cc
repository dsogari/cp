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
  ranges::sort(a);
  int ans = 0;
  for (int i = 0, j = 1; j < n;) {
    while (j < n - 1 && a[j] == a[j + 1]) {
      j++;
    }
    auto diff = a[j] - a[i], len = j - i + 1;
    if (diff <= len && diff > 1) {
      ans = max(ans, diff);
    }
    diff > len ? i++ : j++;
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
