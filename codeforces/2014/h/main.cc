/**
 * https://codeforces.com/contest/2014/submission/282768571
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using u64 = uint64_t;

#ifdef ONLINE_JUDGE
#define debug
#else
#include "debug.h"
init();
#endif

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

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

struct SplitHash {
  size_t operator()(u64 x) const {
    x += (u64)this + 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
};

void solve(int t) {
  Int n, m;
  vector<Int> a(n);
  vector<array<Int, 2>> q(m);
  vector<bool> ans(m);
  SplitHash hash;
  u64 acc = 0;
  auto add = [&](int i) { acc ^= hash(a[i - 1]); };
  auto rem = [&](int i) { acc ^= hash(a[i - 1]); };
  auto get = [&](int j) { ans[j] = acc; };
  Mos mos(m);
  mos.sort(q, hilbert);           // O(m*log m + m*log n)
  mos.visit(q, add, rem, get, 1); // O(m*sqrt n)
  for (int i = 0; i < m; i++) {   // O(m)
    println(ans[i] ? "NO" : "YES");
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
