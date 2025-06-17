/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "lucy.h"
#include "mod.h"
#include "primes.h"

/**
 * Black algorithm
 * https://atcoder.jp/contests/abc370/editorial/10906
 */
Mint black(int n, auto &&unit, auto &&sum) { // O(n)
  Lucy lucy(n, [](int x) { return x - 1; });
  auto dfs = [&](auto &self, int x, int i, int e, Mint prod) -> Mint {
    auto cur = prod * unit(i, e); // f(x*p^e)
    auto ans = cur;
    for (int j = i; j < primes.size(); j++) {
      auto y = u64(x) * primes[j]; // next number
      if (y * primes[j] > lucy.n) {
        ans += cur * sum(max(i + 1, j), lucy.get(lucy.n / x) - 1);
        if (j == i && y <= lucy.n) {
          ans += prod * unit(i, e + 1);
        }
        break;
      }
      ans += self(self, y, j, j == i ? e + 1 : 1, j == i ? prod : cur);
    }
    return ans;
  };
  return dfs(dfs, 1, 0, 0, 1);
}
