/**
 * https://codeforces.com/contest/2020/submission/284706557
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;

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

template <typename T, auto M> struct Mod {
  using V = conditional_t<sizeof(T) <= 4, u64, u128>;
  // static V inv(V x, V m) { return x > 1 ? m - inv(m % x, x) * m / x : 1; }
  static V inv(V x, V m) { // O(log^2 m) | x and m coprime
    for (V a = exchange(x, 1), b = exchange(m, 0); b; a = exchange(b, a % b)) {
      x = exchange(m, x - (a / b) * m);
    }
    return x >= M ? x + M : x;
  }
  make_unsigned_t<T> x;
  Mod() : x(0) {}
  Mod(auto y) : x(y % M) { x >= M ? x += M : x; }
  operator T() const { return x; }
  Mod operator-() const { return Mod() -= *this; }
  Mod operator+(auto rhs) const { return Mod(*this) += rhs; }
  Mod operator-(auto rhs) const { return Mod(*this) -= rhs; }
  Mod operator*(auto rhs) const { return Mod(*this) *= rhs; }
  Mod operator/(auto rhs) const { return Mod(*this) /= rhs; }
  Mod &operator+=(Mod rhs) { return (x += rhs.x) >= M ? x -= M : x, *this; }
  Mod &operator-=(Mod rhs) { return (x -= rhs.x) >= M ? x += M : x, *this; }
  Mod &operator*=(Mod rhs) { return x = x * V(rhs.x) % M, *this; }
  Mod &operator/=(Mod rhs) { return x = x * inv(rhs.x, M) % M, *this; }
  Mod pow(auto y) const { // O(log y) | 0^(-inf,0] -> 1
    Mod ans(1), base(*this);
    for (auto e = y < 0 ? ~y + u128(1) : +y; e; e >>= 1, base *= base) {
      e & 1 ? ans *= base : ans;
    }
    return y < 0 ? Mod(1) /= ans : ans;
  }
};
using Mint = Mod<int, 1000000007>;

constexpr int logmaxa = 10, maxp = 1e4;

void solve(int t) {
  Int n;
  vector<Int> a(n), p(n);
  Mint ans = 0;
  for (int b1 = 0; b1 < logmaxa; b1++) { // O(n*log^2 max(a))
    for (int b2 = 0; b2 < logmaxa; b2++) {
      array<array<Mint, 2>, 2> dp = {};
      dp[0][0] = 1;
      for (int i = 0; i < n; i++) {
        auto a1 = a[i] >> b1 & 1;
        auto a2 = a[i] >> b2 & 1;
        auto prev = dp; // don't use swap here
        dp = {};
        for (int c1 = 0; c1 < 2; c1++) {
          for (int c2 = 0; c2 < 2; c2++) {
            dp[c1][c2] += prev[c1][c2] * (maxp - p[i]);
            dp[c1 ^ a1][c2 ^ a2] += prev[c1][c2] * +p[i];
          }
        }
      }
      ans += dp[1][1] * (1 << (b1 + b2)); // contrib. of pair of bits in f(S)^2
    }
  }
  ans /= Mint(maxp).pow(n);
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
