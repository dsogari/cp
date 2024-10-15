/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Barrett Reduction
 * https://en.algorithmica.org/hpc/arithmetic/division/#barrett-reduction
 */
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
