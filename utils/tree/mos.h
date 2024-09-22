/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Hilbert Curve 2-to-1D Mapping
 */
u64 hilbert(int x, int y) { // O(log max(x,y))
  const unsigned mx = max(x, y) * 2 + 1;
  const int logn = (bit_width(mx) - 1) | 1;
  const int maxn = (1ull << logn) - 1;
  u64 ans = 0;
  for (int s = 1ull << (logn - 1); s; s >>= 1) {
    bool rx = x & s, ry = y & s;
    ans = (ans << 2) | (rx ? ry ? 2 : 1 : ry ? 3 : 0);
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
struct Mos {
  vector<int> idx;
  vector<u64> ord;
  function<bool(int, int)> cmp = [&](int i, int j) { return ord[i] < ord[j]; };
  void build(auto &&q) { // O(m*log m)
    idx.resize(q.size());
    ord.resize(q.size());
    iota(idx.begin(), idx.end(), 0);
    for (int i = 0; i < q.size(); i++) {
      auto [l, r] = q[i];
      ord[i] = hilbert(l, r);
    }
    ranges::sort(idx, cmp);
  }
  void visit(auto &&q, auto &&add, auto &&rem, auto &&get,
             int from = 0) const { // O((n + m)*s)
    for (int i = 0, L = from, R = from - 1; i < idx.size(); i++) {
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
