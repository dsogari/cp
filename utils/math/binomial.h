/**
 * (c) 2024 Diego Sogari
 */
#include "factorial.h"

/**
 * (Modular) Binomial coefficient
 */
template <typename T> struct Bin : Fac<T> {
  vector<Mod<T>> inv;
  Mod<T> operator()(int n, int k) {
    if (k < 0 || k > n) {
      return this->front() * 0;
    }
    auto ans = (*this)[n];
    if (inv.size() <= n) {
      int s = inv.size();
      inv.resize(n + 1);
      inv[n] = Mod<T>(1) / ans;
      for (int i = n; i > s; i--) {
        inv[i - 1] = inv[i] * i;
      }
    }
    return ans * inv[k] * inv[n - k];
  }
};
