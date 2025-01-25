/**
 * https://codeforces.com/contest/2055/submission/302541175
 *
 * Geometry; greedy; brute force
 *
 * (c) 2025 Diego Sogari
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

void solve(int t) {
  Int n;
  vector<array<Int, 2>> rows(n);
  vector<i64> pref(n + 1);
  bool horiz = true;
  for (int i = 0, prevl, prevlen; i < n; i++) { // O(n)
    auto [l, r] = rows[i];
    auto len = r - l + 1;
    pref[i + 1] = pref[i] + len;
    horiz = horiz && len % 2 == 0 &&
            (i == 0 || (len == prevlen && abs(l - prevl) < len / 2));
    prevl = l, prevlen = len;
  }
  if (horiz) {
    return println("YES");
  }
  auto f = [&](int k, bool invert) { // O(n)
    vector<int> len(n);
    for (int i = 0, dx, prevl = INT_MIN, prevr = INT_MAX; i + k < n; i++) {
      auto [l1, r1] = rows[i];
      auto [l2, r2] = rows[i + k];
      if (invert) {
        r1 = -exchange(l1, -r1);
        r2 = -exchange(l2, -r2);
      }
      if (i == 0) {
        dx = r2 - r1;
      } else if (i >= k) {
        r1 -= len[i - k];
      }
      len[i] = r1 - l1 + 1;
      if (len[i] <= 0 || r1 < prevl || l1 > prevr || r1 + dx != r2 ||
          l1 + dx < l2 || (i + 2 * k >= n && l1 + dx > l2)) {
        return false;
      }
      prevl = l1, prevr = r1;
    }
    return true;
  };
  for (int k = 1; k <= n / 2; k++) { // O(n*log n)
    i64 sum = 0;
    for (int i = 0; i < n; i += k, sum = -sum) {
      int r = min(i + k, +n);
      sum += pref[r] - pref[i];
    }
    if (sum == 0 && (f(k, false) || f(k, true))) {
      return println("YES");
    }
  }
  println("NO");
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
