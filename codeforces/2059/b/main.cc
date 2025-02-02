/**
 * https://codeforces.com/contest/2059/submission/304149091
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
  if (n == k) {
    int ans = 1;
    for (int i = 1; i < n; i += 2, ans++) {
      if (a[i] != ans) {
        break;
      }
    }
    return println(ans);
  }
  auto cmp = [](int a) { return a != 1; };
  int i = find_if(a.begin() + 1, a.end(), cmp) - a.begin();
  int ans = n - i >= k - 1                                                  ? 1
            : i > 3 || (i < n && a[i]) != 2 || (i + 1 < n && a[i + 1]) != 2 ? 2
                                                                            : 3;
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
