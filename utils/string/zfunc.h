/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "utils.h"

/**
 * Maximum Prefix lengths (Z-function)
 */
struct Zfn : vector<int> {
  Zfn(auto &&a, int s = 0) : Zfn(a, s, a.size()) {}
  Zfn(auto &&a, int s, int e) : vector<int>(e - s) { // [s, e) O(n)
    auto &z = *this;
    for (int i = 1, j = 1; i + s < e; i++) {
      auto &c = z[i] = max(0, min(j + z[j] - i, z[i - j]));
      while (i + c + s < e && a[i + c + s] == a[c + s]) {
        c++, j = i; // update start of prefix
      }
    }
  }
};
