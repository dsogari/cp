/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "utils.h"

/**
 * Precomputed Divisors (up to n)
 */
struct Divisors : vector<vector<int>> {
  Divisors(int n) : vector<vector<int>>(n + 1) { // O(n*log n)
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= n; j += i) {
        (*this)[j].push_back(i);
      }
    }
  }
};

/**
 * Divisor Counts (up to n)
 */
struct DivCount : vector<int> {
  DivCount(int n) : vector<int>(n + 1) { // O(n*log n)
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= n; j += i) {
        (*this)[j]++;
      }
    }
  }
};
