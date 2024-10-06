/**
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

struct Barrett {
  static inline u32 den; // the original modulus
  static inline u64 mu;  // the precomputed approximation of 2^64/d
  operator u32() const { return den; }
  static void set(u32 d) { den = d, mu = u64(-1) / d; }
  static u64 div(u64 x) { return u128(x) * mu >> 64; }
  static u32 mod(u64 x) { return x -= div(x) * den, x < den ? x : x - den; }
  friend u64 operator/(u64 x, const Barrett &rhs) { return rhs.div(x); }
  friend u32 operator%(u64 x, const Barrett &rhs) { return rhs.mod(x); }
};

template <typename T, auto M> struct Mod {
  using V = conditional_t<is_same_v<make_unsigned_t<T>, u64>, u128, u64>;
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
using Mint = Mod<int, Barrett{}>;

void solve(int t) {
  Int n, k, p;
  Barrett::set(p);
  vector<Mint> gt(k + 1, 1), lt(k + 1, 1), gt2(k + 1, 1), sum(k + 1);
  gt[0] = gt2[0] = 0;
  for (int i = 1; i < n; i++) {   // O(n*k^2)
    for (int j = k; j > 0; j--) { // work backwards to reuse the dp vector
      sum[j] = gt2[j];
      for (int x = 1; x < j && x + j <= k; x++) {
        sum[j] += lt[x] * (gt2[j] - sum[x]) + gt[x] * sum[x - 1];
      }
      for (int x = 1; x < j - x; x++) { // deterministic choices
        gt[j] += lt[x] * gt[j - x];
        lt[j] += lt[x] * lt[j - x];
        gt2[j] += lt[x] * (gt2[j - x] - sum[x]) + gt[x] * sum[x - 1];
      }
      gt[j] *= 2; // adjustment due to the tree symmetry
      lt[j] *= 2;
      gt2[j] *= 2;
      sum[j] *= 2;
      if (j % 2 == 0) { // non-deterministic choices
        lt[j] += lt[j / 2] * lt[j / 2];
      }
    }
    for (int j = 1; j <= k; j++) { // accumulate to get the actual values
      gt[j] += gt[j - 1];
      lt[j] += lt[j - 1];
      gt2[j] += gt2[j - 1];
      sum[j] += sum[j - 1];
    }
    assert(sum[k] == gt2[k]);
  }
  println(gt2[k]);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
