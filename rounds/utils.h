#pragma once

#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef DEBUG
using filesystem::path;
#define IO(file)                                                \
  auto in = ifstream(path(file).replace_filename("input.txt")); \
  auto &out = cout << fixed << setprecision(20)
#else
#define IO(_)                                                 \
  auto &in = (cin.tie(nullptr)->sync_with_stdio(false), cin); \
  auto &out = cout << fixed << setprecision(20)
#endif
