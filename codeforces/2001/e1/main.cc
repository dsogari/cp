/**
 * https://codeforces.com/contest/2001/submission/286080856
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

template <typename T> struct Barrett {
  static inline conditional_t<sizeof(T) <= 4, u64, u128> m, u;
  static void set(T y) { m = y, u = -1 / m; } // u = 2^(16*sizeof(T))/m
  operator T() const { return m; }
  static u64 div(u128 x) requires(sizeof(T) <= 4) { return x * u >> 64; }
  static u128 div(u128 x) requires(sizeof(T) > 4) {
    u128 xl = u64(x), ul = u64(u), xh = x >> 64, uh = u >> 64;
    auto a = xl * ul, b = xl * uh, c = ul * xh, d = xh * uh;
    return d + (b >> 64) + (c >> 64) + (((a >> 64) + u64(b) + u64(c)) >> 64);
  }
  friend auto operator/(auto x, Barrett) requires(sizeof(x) <= sizeof(u)) {
    auto q = x < 0 ? ~div(~x + u128(1)) : div(x);
    return decltype(x)(q + (x < 0 ? x > q * m : x >= (q + 1) * m));
  }
  friend auto operator%(auto x, Barrett) requires(sizeof(x) <= sizeof(u)) {
    auto q = x < 0 ? ~div(~x + u128(1)) : div(x);
    return x -= q * m, decltype(x)(x < 0 || x < m ? x : x - m);
  }
};

template <typename T, auto M> struct Mod {
  using V = conditional_t<sizeof(T) <= 4, u64, u128>;
  static V inv(V x, V m) { return x > 1 ? m - inv(m % x, x) * m / x : 1; }
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
using Mint = Mod<int, Barrett<int>{}>;

void solve(int t) {
  Int n, k, p;
  Barrett<int>::set(p);
  vector<Mint> gt(k + 1, 1), lt(k + 1, 1);
  gt[0] = 0;
  for (int i = 1; i < n; i++) {         // O(n*k^2)
    for (int j = k; j > 0; j--) {       // work backwards to reuse the dp vector
      for (int x = 1; x < j - x; x++) { // compute the deterministic choices
        gt[j] += lt[x] * gt[j - x];     // path of the pop operation
        lt[j] += lt[x] * lt[j - x];     // the rest of the tree
      }
      gt[j] *= 2; // adjustment due to the tree symmetry
      lt[j] *= 2;
      if (j % 2 == 0) { // compute the non-deterministic choices
        lt[j] += lt[j / 2] * lt[j / 2];
      }
    }
    for (int j = 1; j <= k; j++) { // accumulate to get the actual values
      gt[j] += gt[j - 1];
      lt[j] += lt[j - 1];
    }
  }
  println(gt[k]);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
