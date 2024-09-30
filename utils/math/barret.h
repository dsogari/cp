/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Barrett Reduction
 */
struct Barret {
  static inline u64 mod, mu;
  static void set(u64 m) { mod = m, mu = u64(-1) / m; }
  operator u64() const { return mod; }
  static u64 div(u64 x) {
#ifdef __SIZEOF_INT128__
    x -= (__uint128_t(x) * mu >> 64) * mod;
#else
    x %= mod;
#endif
    return x < mod ? x : x - mod;
  }
  friend u64 operator%(u64 x, const Barret &rhs) { return rhs.div(x); }
};
