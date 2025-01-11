/**
 * https://codeforces.com/contest/2033/submission/300556402
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
  Int n;
  vector<Int> a(n);
  vector<bool> vis(n);
  int ans = 0;
  for (int i = 0, c = 1; i < n; i++, c = 1) {
    vis[i] = true;
    for (int j = a[i] - 1; !vis[j]; j = a[j] - 1, c++) {
      vis[j] = true;
    }
    ans += (c - 1) / 2;
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
