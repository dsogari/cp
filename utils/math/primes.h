/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Sieve of Eratosthenes (Prime numbers) - NOT TESTED YET
 */
struct Sieve : vector<int> {
  Sieve(int n) : Sieve(n, n * log(n * log(n))) {}
  Sieve(int n, int mx) { // O(mx*log log mx)
    vector<bool> vis(mx + 1);
    for (int i = 2; i <= mx && size() < n; i++) {
      if (!vis[i]) {
        push_back(i);
        for (int j = 2 * i; j <= mx; j += i) {
          vis[j] = true;
        }
      }
    }
  }
};

/**
 * Precomputed Prime numbers (up to 2^16) - NOT TESTED YET
 * https://en.algorithmica.org/hpc/algorithms/factorization/
 */
struct Primes {
  static constexpr int N = 1 << 16;
  array<u64, 6542> magic = {}; // ~51KB
  constexpr Primes() {         // O(N*log log N) = O(2^18)
    array<bool, N> vis = {};
    for (int i = 2, cnt = 0; i < N; i++) {
      if (!vis[i]) {
        magic[cnt++] = u64(-1) / i + 1;
        for (int j = 2 * i; j < N; j += i)
          vis[j] = true;
      }
    }
  }
  vector<u32> factors(u32 n) const { // O(sqrt n/log n)
    vector<u32> ans = {1};
    auto mx = u64(-1) / u64(sqrt(n)) + 1;
    for (auto m : magic) {
      if (m * n < m) {
        ans.push_back(u64(-1) / m + 1);
      } else if (m < mx) {
        break;
      }
    }
    return ans;
  }
};
