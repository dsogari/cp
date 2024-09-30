/**
 * (c) 2024 Diego Sogari
 */
#include "mod.h"

/**
 * (Modular) Factorial
 */
struct Fact : vector<Mint> {
  Fact() : vector<Mint>(1, 1) {}
  Mint operator[](int n) { // O(1) amortized (use reserve if necessary)
    while (size() <= n) {
      push_back(back() * size());
    }
    return vector<Mint>::operator[](n);
  }
};
