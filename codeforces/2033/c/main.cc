/**
 * https://codeforces.com/contest/2033/submission/300316101
 *
 * Greedy; two pointers
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
  for (int l = (n - 1) / 2, r = n / 2; l > 0;) {
    auto pl = a[l--], pr = a[r++];
    auto &cl = a[l], &cr = a[r];
    if (cl == pl || cr == pr) {
      swap(cl, cr);
    }
  }
  int ans = 0;
  for (int i = 1; i < n; i++) {
    ans += a[i] == a[i - 1];
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
