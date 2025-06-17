/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "utils.h"

/**
 * PCG pseudo-random number generator
 * https://www.pcg-random.org/
 */
struct PCG {
  u64 state, inc;
  PCG(u64 seed) : PCG(seed, (u64)this << 1u | 1u) {}
  PCG(u64 seed, u64 seq) : state(0), inc(seq) { step(), state += seed, step(); }
  u32 operator()() { // O(1)
    auto ans = rotr<u32>(((state >> 18u) ^ state) >> 27u, state >> 59u);
    return step(), ans;
  }
  void step() { state = state * 6364136223846793005ull + inc; } // O(1)
};
