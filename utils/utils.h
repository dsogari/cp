/**
 * (c) 2024 Diego Sogari
 */
#pragma once

/**
 * Common includes
 */
#include <bits/stdc++.h>

/**
 * Common namespaces
 */
using namespace std;
using namespace placeholders;

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
 * Common constants
 */
constexpr int lowerlatin = 'z' - 'a' + 1;
constexpr int upperlatin = 'Z' - 'A' + 1;
const string vowels = "aeiou";

/**
 * Timing utilities
 */
auto now() { return chrono::high_resolution_clock::now(); }
