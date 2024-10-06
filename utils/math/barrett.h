/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Barrett Reduction
 * https://en.algorithmica.org/hpc/arithmetic/division/#barrett-reduction
 */
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
