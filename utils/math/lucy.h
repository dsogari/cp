/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "utils.h"

/**
 * Lucy DP
 * https://projecteuler.net/action=redirect;post_id=111677
 */
struct Lucy : vector<int> {
  int n, s, m;
  Lucy(int n, auto &&f) : n(n), s(sqrt(n)), m(2 * this->s) { // O(n^0.75)
    vector<int> v(m);
    for (int i = 0; i < m; i++) {
      v[i] = i < s ? i + 1 : n / (m - i);
      push_back(f(v[i]));
    }
    for (int p = 2; p <= s; p++) {
      if ((*this)[p - 1] != (*this)[p - 2]) { // p is prime
        for (int i = m - 1; i >= 0 && p * p <= v[i]; i--) {
          (*this)[i] -= get(v[i] / p) - (*this)[p - 2];
        }
      }
    }
  }
  int get(int x) const { return (*this)[x <= s ? x - 1 : m - n / x]; }; // O(1)
};
