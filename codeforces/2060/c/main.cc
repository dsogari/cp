/**
 * https://codeforces.com/contest/2060/submission/301809674
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
  vector<int> cnt(n + 1);
  for (auto &&ai : a) {
    cnt[ai]++;
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (1 <= k - i && k - i <= n) {
      ans += min(cnt[i], cnt[k - i]);
    }
  }
  ans /= 2;
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
