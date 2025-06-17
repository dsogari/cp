/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "io.h"

/**
 * Numeric types
 */
using i64 = int64_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t; // available on 64-bit targets
using i128 = __int128_t;  // available on 64-bit targets
using f128 = __float128;  // available on 64-bit targets

/**
 * Common aliases
 */
using Int = Number<int>;
using Chr = Number<char>;
using I64 = Number<i64>;
using U64 = Number<u64>;
using F64 = Number<double>;
using Str = String<char>;

/**
 * Common constants
 */
constexpr int lowerlatin = 'z' - 'a' + 1;
constexpr int upperlatin = 'Z' - 'A' + 1;
const string vowels = "aeiou";

/**
 * Timing utilities
 */
auto now() { return chrono::high_resolution_clock::now(); }
