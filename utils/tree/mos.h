/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Hilbert Curve 2-to-1D Mapping
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
 * Mo's algorithm
 */
template <typename T> struct Mos {
  const T &q;
  vector<int> idx;
  vector<u64> ord;
  Mos(const T &q) : q(q), idx(q.size()), ord(q.size()) { // O(m*(log m + log n))
    auto cmp = [&](int i, int j) { return ord[i] < ord[j]; };
    iota(idx.begin(), idx.end(), 0);
    for (int i = 0; i < q.size(); i++) {
      auto [l, r] = q[i];
      ord[i] = hilbert(l, r);
    }
    ranges::sort(idx, cmp);
  }
  void visit(auto &&add, auto &&rem, auto &&get, int from = 0) const {
    for (int i = 0, L = from, R = from - 1; i < q.size(); i++) { // O(m*sqrt n)
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
