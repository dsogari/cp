/**
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

/**
 * Common pragmas
 */
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt")

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
 * Common associative operations (for tree node manipulation)
 */
const auto tadd = [](auto &lhs, auto &rhs) { return lhs + rhs; };
const auto tmul = [](auto &lhs, auto &rhs) { return lhs * rhs; };
const auto tmin = [](auto &lhs, auto &rhs) { return min(lhs, rhs); };
const auto tmax = [](auto &lhs, auto &rhs) { return max(lhs, rhs); };
