/**
 * https://codeforces.com/contest/2055/submission/300755131
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
  Int n, k, l;
  vector<Int> a(n);
  ranges::sort(a); // O(n*log n)
  int ans = 2 * a[0], pos = 2 * k;
  for (int i = 1; i < n && pos < 2 * l; i++) { // O(n)
    int dist = 2 * a[i] - pos;                 // distance from next one
    if (dist > 0) {
      dist -= min(ans, dist);
      dist /= 2;
      ans += dist;
    } else {
      dist += min(ans, -dist);
    }
    pos += dist + 2 * k;
  }
  ans += max(0, 2 * l - pos);
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
