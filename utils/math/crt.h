/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "mod.h"

/**
 * Chinese Remainder Theorem
 */
template <typename T> struct CRT : vector<Mod<T>> {
  using vector<Mod<T>>::vector;
  array<i64, 2> operator()() const { // O(n*log^2 max(mi))
    i64 m = 1;
    for (const auto &ai : *this) {
      m *= ai.m; // mi are mutually coprime
    }
    i64 ans = 0;
    for (const auto &ai : *this) { // O(n*log^2 max(mi))
      auto Mi = m / ai.m;
      ans += Mi * (ai / Mi) % m;
    }
    return {ans, m};
  }
};
