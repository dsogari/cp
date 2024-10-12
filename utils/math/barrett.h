/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Barrett Reduction
 * https://en.algorithmica.org/hpc/arithmetic/division/#barrett-reduction
 */
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
