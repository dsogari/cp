/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "utils.h"

/**
 * Custom hashing function using SplitMix
 * https://xoshiro.di.unimi.it/splitmix64.c
 */
struct SplitHash {
  size_t operator()(u64 x) const {
    x += (u64)this + 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
};

/**
 * Compound hashing function (for arrays and vectors)
 */
template <typename F> struct CompoundHash {
  const F f;
  size_t operator()(const auto &a) const {
    u64 z = 0;
    for (auto x : a) {
      z ^= f(x) << 1;
    }
    return z;
  }
};
