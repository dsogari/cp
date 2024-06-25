#pragma once

#include <bits/stdc++.h>

using namespace std;
using filesystem::path;
using i64 = int64_t;
using f64 = double;

namespace std {
string to_string(const string &s) { return s; }
} // namespace std

constexpr int inc_mod(int a, int m) { return (a + 1) % m; }
constexpr int dec_mod(int a, int m) { return (a ? a : m) - 1; }

// cout << fixed << setprecision(20);