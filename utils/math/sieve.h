/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Precomputed factors (Divisors)
 */
struct Div : vector<vector<int>> {
  Div(int n) : vector<vector<int>>(n + 1) { // O(n*log n)
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= n; j += i) {
        (*this)[j].push_back(i);
      }
    }
  }
};

/**
 * Precomputed Prime numbers (Sieve of Eratosthenes)
 */
struct Sieve : vector<int> {
  Sieve(int n) : Sieve(n, n * log(n * log(n))) {}
  Sieve(int n, int mx) { // O(mx*log log mx)
    vector<bool> vis(mx + 1);
    for (int i = 2; i <= mx && size() < n; i++) {
      if (!vis[i]) {
        push_back(i);
        for (auto j = 1ll * i * i; j <= mx; j += i) {
          vis[j] = true;
        }
      }
    }
  }
};
