/**
 * https://codeforces.com/contest/2014/submission/282649842
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

struct SplitHash {
  size_t operator()(u64 x) const {
    x += (u64)this + 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
};

auto now() { return chrono::high_resolution_clock::now(); }

seed_seq seq{(u64)now().time_since_epoch().count(),
             (u64)make_unique<char>().get()};
mt19937 rng(seq);

void solve(int t) {
  Int n, m;
  vector<Int> a(n);
  vector<array<Int, 2>> q(m);
  unordered_map<int, int, SplitHash> ids;
  for (auto &&ai : a) { // O(n)
    if (!ids.contains(ai)) {
      ids[ai] = rng();
    }
  }
  vector<bool> ans(m);
  int acc = 0;
  auto add = [&](int i) { acc ^= ids[a[i - 1]]; };
  auto rem = [&](int i) { acc ^= ids[a[i - 1]]; };
  auto get = [&](int j) { ans[j] = acc; };
  Mos mos(q);                   // O(m*(log m + log n))
  mos.visit(add, rem, get, 1);  // O(m*sqrt n)
  for (int i = 0; i < m; i++) { // O(m)
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
