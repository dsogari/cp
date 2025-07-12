/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "utils.h"

/**
 * Element Frequencies
 */
struct Freq : vector<int> {
  Freq(const auto &a) : Freq(a, ranges::max(a)) {}
  Freq(const auto &a, int mx) : vector<int>(mx + 1) { // O(n)
    for (auto &&ai : a) {
      (*this)[ai]++;
    }
  }
};
