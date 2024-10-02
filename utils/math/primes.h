/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Sieve of Prime numbers (up to 2^32)
 */
struct Sieve : vector<int> {
  Sieve(int n, bool isval) { // max value or min count
    int mx = isval ? n : ceil(n * log(n * log(n + 1) + 1) + 1);
    vector<bool> vis(mx + 1);
    for (int i = 2; i <= mx; i++) { // O(mx*log log mx)
      if (!vis[i]) {
        push_back(i);
        for (int j = i; j <= mx; j += i) {
          vis[j] = true;
        }
      }
    }
  }
};

/**
 * Sieve of Prime numbers (up to 2^16)
 * https://en.algorithmica.org/hpc/algorithms/factorization/
 */
struct Primes : array<u16, 6542> { // ~13KB
  constexpr Primes() {             // O(N*log log N) = O(2^18)
    array<bool, 1 << 16> vis = {};
    for (int i = 2, cnt = 0; i < vis.size(); i++) {
      if (!vis[i]) {
        (*this)[cnt++] = i;
        for (int j = i; j < vis.size(); j += i) {
          vis[j] = true;
        }
      }
    }
  }
};

/**
 * Prime Factors of a number (up to 2^32)
 * https://en.algorithmica.org/hpc/algorithms/factorization/
 */
struct Factors : Primes {
  array<u64, 6542> magic;          // ~51KB
  constexpr Factors() : Primes() { // O(N*log log N) = O(2^18)
    for (int i = 0; i < magic.size(); i++) {
      magic[i] = u64(-1) / (*this)[i] + 1;
    }
  }
  vector<u32> get(u32 x) const { // O(min(6542,x/log x))
    vector<u32> ans = {1};
    auto mx = u64(-1) / u64(x) + 1;
    for (auto m : magic) {
      if (m * x < m) {
        ans.push_back(u64(-1) / m + 1);
      } else if (m < mx) {
        break;
      }
    }
    return ans;
  }
};
