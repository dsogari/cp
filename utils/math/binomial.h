/**
 * (c) 2024 Diego Sogari
 */
#include "factorial.h"

/**
 * (Modular) Binomial coefficient
 */
struct Binom : Fact {
  vector<Mint> inv;
  Mint operator()(int n, int k) { // O(1) amortized
    assert(k >= 0 && k <= n);
    auto ans = (*this)[n]; // updates the factorial up to n
    int s = inv.size();
    if (s <= n) {
      inv.reserve(capacity());
      inv.resize(size());
      inv[n] = Mint(1) / ans;
      for (int i = n; i > s; i--) {
        inv[i - 1] = inv[i] * i;
      }
    }
    return ans * inv[k] * inv[n - k];
  }
};
