/**
 * https://codeforces.com/contest/1984/submission/277068306
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

template <typename T> struct Mod {
  constexpr static T _def = 998244353;
  static i64 inv(i64 x, i64 m) { // O(log^2 m) / x and m must be coprime
    return x < 0 ? inv(x % m + m, m) : x > 1 ? m - inv(m % x, x) * m / x : 1;
  } // https://codeforces.com/blog/entry/23365
  T x, m;
  operator T() const { return x; }
  void set(i64 y) { x = (y %= m) < 0 ? y + m : y; };
  Mod(i64 x = 0, T m = _def) : m(m) { set(x); }
  Mod operator+(auto y) const { return Mod(x, m) += y; }
  Mod operator-(auto y) const { return Mod(x, m) -= y; }
  Mod operator*(auto y) const { return Mod(x, m) *= y; }
  Mod operator/(auto y) const { return Mod(x, m) /= y; }
  Mod &operator+=(i64 y) { return set(x + y), *this; }
  Mod &operator-=(i64 y) { return set(x - y), *this; }
  Mod &operator*=(i64 y) { return set(x * y), *this; }
  Mod &operator/=(i64 y) { return *this *= inv(y, m); }
  Mod pow(auto y) const { // O(log y) / 0^(-inf,0] -> 1
    Mod ans(1, m), base(y < 0 ? inv(x, m) : x, m);
    for (y = abs(y); y; y >>= 1, base *= base) {
      y & 1 ? ans *= base : ans;
    }
    return ans;
  }
};
using Mint = Mod<int>;

void solve(int t) {
  Int n;
  vector<Int> a(n);
  map<i64, Mint> dp = {{0, 1}};
  for (auto &&ai : a) {
    map<i64, Mint> dp1;
    for (auto &&[c, u] : dp) {
      dp1[c + ai] += u;
      dp1[abs(c + ai)] += u;
    }
    dp = {*dp1.begin(), *dp1.rbegin()};
  }
  println(dp.rbegin()->second);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
