/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "utils.h"

/**
 * Maximum Palindromic odd-lengths (Manacher's algorithm)
 */
struct Manacher : vector<int> {
  Manacher(auto &&a, int s = 0) : Manacher(a, s, a.size()) {}
  Manacher(auto &&a, int s, int e) : vector<int>(e - s) { // [s, e) O(n)
    auto &z = *this;
    for (int i = 0, j = 0; i + s < e; i++) {
      auto &c = z[i] = max(0, min(j + z[j] - i, z[max(0, 2 * j - i)]));
      while (i + c + s < e && i - c >= s && a[i + c + s] == a[i - c + s]) {
        c++, j = i; // update center of palindrome
      }
    }
  }
};

/**
 * Maximum Palindromic lengths
 */
vector<array<int, 2>> manacher(auto &&a, int s, int e, auto d) { // [s, e) O(n)
  typename remove_cvref<decltype(a)>::type b = {d};
  for (int i = s; i < e; i++) {
    b.insert(b.end(), {a[i], d});
  }
  Manacher z(b);
  vector<array<int, 2>> ans(e - s);
  for (int i = 0; i < e - s; i++) {
    ans[i][0] = (z[2 * i] - 1) / 2; // even
    ans[i][1] = (z[2 * i + 1]) / 2; // odd
  }
  return ans;
}
