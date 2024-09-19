/**
 * https://codeforces.com/contest/2005/submission/281840592
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef ONLINE_JUDGE
#define debug
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

template <typename T, size_t N>
array<T, N> &operator+=(array<T, N> &lhs, const array<T, N> &rhs) {
  for (int i = 0; i < N; i++) {
    lhs[i] += rhs[i];
  }
  return lhs;
}

void solve(int t) {
  Int n;
  vector<Int> a(n), b(n);
  auto f = [&](auto &self, int l, int r) -> map<array<int, 2>, array<i64, 3>> {
    map<array<int, 2>, array<i64, 3>> dp;
    if (l + 1 < r) {
      auto mid = (l + r) / 2;
      auto dp1 = self(self, l, mid);
      auto dp2 = self(self, mid, r);
      array<i64, 3> c;
      for (auto [d1, c1] : dp1) {
        for (auto [d2, c2] : dp2) {
          c[0] = c1[0] * c2[0];
          c[1] = c1[0] * c2[1];
          c[2] = c1[0] * c2[2] + c1[1] * c2[0] + c1[2] * c2[0];
          if (c[0] + c[1] + c[2]) {
            auto x = gcd(d1[0], d2[0]);
            auto y = gcd(d1[1], d2[1]);
            dp[{x, y}] += c;
          }
          c[0] = 0;
          c[1] = c1[0] * c2[0] + c1[1] * c2[0];
          c[2] = c1[0] * c2[1] + c1[1] * c2[1];
          if (c[0] + c[1] + c[2]) {
            auto x = gcd(d1[0], d2[1]);
            auto y = gcd(d1[1], d2[0]);
            dp[{x, y}] += c;
          }
        }
      }
    } else if (l < r) {
      dp[{a[l], b[l]}] = {1, 0, 0};
    }
    return dp;
  };
  auto dp = f(f, 0, n);
  int ans = 0;
  i64 cnt = 0;
  for (auto &&[p, c] : dp) {
    auto [d0, d1] = p;
    if (d0 + d1 > ans) {
      ans = d0 + d1;
      cnt = 0;
    }
    if (d0 + d1 == ans) {
      cnt += c[0] + 2 * c[1] + c[2];
    }
  }
  println(ans, cnt);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
