/**
 * https://codeforces.com/contest/2001/submission/285653051
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
  using V = conditional_t<sizeof(T) <= 4, u64, u128>;
  static inline V m, u; // u = 2^(8*sizeof(V))/m
  static void set(T y) { m = y, u = V(-1) / m; }
  operator T() const { return m; }
  friend V operator/(V x, const Barrett &rhs) {
    V q;
    if constexpr (sizeof(T) <= 4) {
      q = u128(x) * u >> 64;
    } else {
      u128 xl = u64(x), ul = u64(u), xh = x >> 64, uh = u >> 64;
      u128 a = xl * ul, b = xl * uh, c = ul * xh, d = xh * uh;
      q = d + (b >> 64) + (c >> 64) + (((a >> 64) + u64(b) + u64(c)) >> 64);
    }
    return q + (x >= (q + 1) * m);
  }
  friend T operator%(V x, const Barrett &rhs) { return x - (x / rhs) * rhs.m; }
};

template <typename T, auto M> struct Mod {
  using V = conditional_t<sizeof(T) <= 4, u64, u128>;
  static V inv(V x, V m) { return x > 1 ? m - inv(m % x, x) * m / x : 1; }
  make_unsigned_t<T> x;
  Mod() : x(0) {}
  Mod(auto y) : x(y % i64(M)) { x >= M ? x += M : x; }
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
    for (auto e = y < 0 ? ~y + 1ull : +y; e; e >>= 1, base *= base) {
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
