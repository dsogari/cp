/**
 * https://codeforces.com/contest/1993/submission/276852390
 *
 * (c) 2024 Diego Sogari
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

struct Str : string {
  Str() { cin >> *this; }
};

constexpr int absmod(int x, int m) { return (m + x % m) % m; };

void solve(int t) { // O((n + k)*log n)
  Int n, k, w, h;
  Str s;
  map<array<int, 2>, int> cnt;
  int x = 0, y = 0;
  for (int i = 0; i < n; i++) { // O(n*log n)
    x += (s[i] == 'L') - (s[i] == 'R');
    y += (s[i] == 'U') - (s[i] == 'D');
    cnt[{absmod(x, 2 * w), absmod(y, 2 * h)}]++;
  }
  i64 ans = 0;
  for (int i = 0, x0 = 0, y0 = 0; i < k; i++) { // O(k*log n)
    ans += cnt[{x0, y0}];
    x0 = absmod(x0 - x, 2 * w); // move Y axis in opposite direction
    y0 = absmod(y0 - y, 2 * h); // move X axis in opposite direction
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
