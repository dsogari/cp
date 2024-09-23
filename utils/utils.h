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
const string vowels = "aeiou";

/**
 * Timing utilities
 */
auto now() { return chrono::high_resolution_clock::now(); }
