/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Barrett Reduction (for 32-bit moduli)
 * https://en.algorithmica.org/hpc/arithmetic/division/#barrett-reduction
 */
struct Barrett {
  static inline u64 m, u; // u = 2^64/m
  static void set(u32 y) { m = y, u = -1 / m; }
  operator u32() const { return m; }
  friend auto operator/(auto x, const Barrett &) {
    if constexpr (sizeof(x) > 8) {
      return x / m;
    }
    auto q = u128(x < 0 ? ~x + u128(1) : x) * u >> 64;
    return decltype(x)(x < 0 ? ~q + (x != ~q * m) : q + (x == (q + 1) * m));
  }
  friend auto operator%(auto x, const Barrett &rhs) {
    return decltype(x)(x - (x / rhs) * m);
  }
};

/**
 * Barrett Reduction (for 64-bit moduli)
 */
struct Barrett64 {
  static inline u128 m, u; // u = 2^128/m
  static void set(u64 y) { m = y, u = -1 / m; }
  operator u64() const { return m; }
  friend auto operator/(auto x, const Barrett64 &) {
    u128 xx = x < 0 ? ~x + u128(1) : x;
    u128 xl = u64(xx), ul = u64(u), xh = xx >> 64, uh = u >> 64;
    auto a = xl * ul, b = xl * uh, c = ul * xh, d = xh * uh;
    auto q = d + (b >> 64) + (c >> 64) + (((a >> 64) + u64(b) + u64(c)) >> 64);
    return decltype(x)(x < 0 ? ~q + (x != ~q * m) : q + (x == (q + 1) * m));
  }
  friend auto operator%(auto x, const Barrett64 &rhs) {
    return decltype(x)(x - (x / rhs) * m);
  }
};
