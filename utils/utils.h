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
 * Common types
 */
using i64 = int64_t;
using u64 = uint64_t;
using f64 = double;

/**
 * Common constants
 */
constexpr int lowerlatin = 'z' - 'a' + 1;
constexpr int upperlatin = 'Z' - 'A' + 1;

/**
 * Common associative operations
 */
const auto tadd = [](auto &lhs, auto &rhs) { return lhs + rhs; };
const auto tmul = [](auto &lhs, auto &rhs) { return lhs * rhs; };
const auto txor = [](auto &lhs, auto &rhs) { return lhs ^ rhs; };

/**
 * Common associative idempotent operations
 */
const auto tmin = [](auto &lhs, auto &rhs) { return min(lhs, rhs); };
const auto tmax = [](auto &lhs, auto &rhs) { return max(lhs, rhs); };
// for gcd, use gcd<int, int>

/**
 * Timing utilities
 */
auto now() { return chrono::high_resolution_clock::now(); }
