/**
 * (c) 2024 Diego Sogari
 */
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
 * Custom hashing function using CRC32
 * https://rigtorp.se/notes/hashing/
 */
struct CRC32Hash {
  size_t operator()(auto x) const noexcept {
    return _mm_crc32_u64((size_t)this, x);
  }
};

/**
 * Custom hashing function using Murmur Hash
 * https://github.com/aappleby/smhasher
 */
struct MurmurHash {
  size_t operator()(auto x) const {
    return _Hash_bytes(&x, sizeof(x), (size_t)this);
  }
};

/**
 * Array hashing function
 */
struct ArrayHash {
  const SplitHash hash;
  size_t operator()(const auto &a) const {
    u64 z = 0;
    for (auto x : a) {
      z ^= hash(x) << 1;
    }
    return z;
  }
};
