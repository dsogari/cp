/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Seed Sequence for use with PRNGs
 */
seed_seq seq{(u64)now().time_since_epoch().count(),
             (u64)make_unique<char>().get()};

/**
 * Mersenne Twister pseudo-random number generator
 */
mt19937 rng(seq);
mt19937_64 rng64(seq);

/**
 * Uniform Distribution
 */
using Uniform = uniform_int_distribution<int>;

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
 * Array hashing function
 */
struct ArrayHash {
  const SplitHash split;
  size_t operator()(const auto &a) const {
    u64 z = 0;
    for (auto x : a) {
      z ^= split(x) << 1;
    }
    return z;
  }
};
