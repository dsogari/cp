/**
 * (c) 2024 Diego Sogari
 */
#include "math/mod.h"

/**
 * Count distinct subsequences of positive length
 */
Mint distinct_subseq(const string &s) {
  vector<Mint> cnt(s.size() + 1);
  array<int, 'z' - 'a' + 1> pos;
  pos.fill(-1);
  for (int i = 0; i < s.size(); i++) { // O(n)
    auto &j = pos[s[i] - 'a'];
    cnt[i + 1] = cnt[i] * 2 + (j < 0 ? 1 : -cnt[j]);
    j = i;
  }
  return cnt.back();
}
