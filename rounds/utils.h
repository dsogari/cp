#pragma once

#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef DEBUG
using filesystem::path;
#define INPUT(file) auto input = ifstream(path(file).replace_filename("input.txt"))
#else
#define INPUT(_) auto &input = (cin.tie(nullptr)->sync_with_stdio(false), cin)
#endif
