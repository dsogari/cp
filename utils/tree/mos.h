/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Hilbert Curve 2-to-1D mapping
 */
u64 hilbert(unsigned x, unsigned y) { // O(log max(x,y))
  const unsigned maxr = max(x, y) * 2 + 1;
  const unsigned logn = (bit_width(maxr) - 1) | 1;
  const unsigned maxn = (1 << logn) - 1;
  const unsigned tran[2][2] = {{0, 3}, {1, 2}};
  u64 ans = 0;
  for (unsigned s = 1 << (logn - 1); s; s >>= 1) {
    bool rx = x & s, ry = y & s;
    ans = (ans << 2) | tran[rx][ry];
    if (!rx) {
      if (ry) {
        x ^= maxn, y ^= maxn;
      }
      swap(x, y);
    }
  }
  return ans;
}

/**
 * Classic Even/Odd block mapping
 */
u64 evenodd(int blocksize, unsigned x, unsigned y) {
  u64 block = x / blocksize;
  return block << 32 | (block & 1 ? y : -1u - y);
}

/**
 * Mo's algorithm
 */
struct Mos {
  vector<int> idx;
  Mos(int m) : idx(m) { iota(idx.begin(), idx.end(), 0); }
  void sort(auto &&q, auto &&f) { // O(m*log m + m*F(n))
    vector<u64> ord(idx.size());
    for (int i = 0; i < idx.size(); i++) {
      auto [l, r] = q[i];
      ord[i] = f(l, r);
    }
    auto cmp = [&](int i, int j) { return ord[i] < ord[j]; };
    ranges::sort(idx, cmp);
  }
  void visit(auto &&q, auto &&add, auto &&rem, auto &&get, int s = 0) const {
    for (int i = 0, L = s, R = s - 1; i < idx.size(); i++) { // O(m*sqrt n)
      auto [l, r] = q[idx[i]];
      while (L > l) {
        add(--L);
      }
      while (R < r) {
        add(++R);
      }
      while (L < l) {
        rem(L++);
      }
      while (R > r) {
        rem(R--);
      }
      get(idx[i]);
    }
  }
};
