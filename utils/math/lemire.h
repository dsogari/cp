/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "utils.h"

/**
 * Lemire Reduction (for values up to 2^32)
 * https://en.algorithmica.org/hpc/arithmetic/division/#lemire-reduction
 */
struct Lemire {
  static inline u32 den;
  static inline u64 mu;
  operator u32() const { return den; }
  static void set(u32 d) { den = d, mu = u64(-1) / d + 1; }
  static u32 div(u32 x) { return u128(x) * mu >> 64; }
  static u32 mod(u32 x) { return u128(x * mu) * den >> 64; }
  friend u32 operator/(u32 x, const Lemire &rhs) { return rhs.div(x); }
  friend u32 operator%(u32 x, const Lemire &rhs) { return rhs.mod(x); }
};
