/**
 * https://codeforces.com/contest/2055/submission/300995755
 *
 * Sorting; segment
 *
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef ONLINE_JUDGE
#define debug(...)
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

struct Iota : vector<int> {
  Iota(int n, int s = 0) : vector<int>(n) { iota(begin(), end(), s); }
  Iota(int n, auto &&f, int s = 0) : Iota(n, s) { ranges::sort(*this, f); }
};

template <typename T> struct SegTree {
  int n;
  vector<T> nodes;
  function<T(const T &, const T &)> f;
  SegTree(int n, auto &&f, T val = {}) : n(n), f(f), nodes(2 * n, val) {}
  T full() const { return _node(1); }           // O(1)
  T get(int i) const { return _node(i + n); }   // O(1)
  T &operator[](int i) { return nodes[i + n]; } // O(1)
  T query(int l, int r) const { return _check(l, r), _query(l + n, r + n); }
  void update(int i, bool single) { _check(i, i), _build(i + n, single); }
  void _build(int i, bool single) { // O(log n) / [0, i] O(n)
    function<void()> dec[] = {[&]() { i--; }, [&]() { i >>= 1; }};
    for (i >>= 1; i > 0; dec[single]()) {
      _merge(i);
    }
  }
  T _query(int l, int r) const { // [l, r] O(log n)
    return l == r   ? _node(l)
           : l & 1  ? f(_node(l), _query(l + 1, r))
           : ~r & 1 ? f(_query(l, r - 1), _node(r))
                    : _query(l >> 1, r >> 1);
  }
  virtual T _node(int i) const { return nodes[i]; }
  void _merge(int i) { nodes[i] = f(_node(i << 1), _node(i << 1 | 1)); }
  void _check(int l, int r) const { assert(l >= 0 && l <= r && r < n); }
};

struct Seg {
  i64 mx = 0, sum = 0;
  /// non-commutative (use power-of-two)
  Seg join(const Seg &rhs) const {
    return {max(mx, sum + rhs.mx), sum + rhs.sum};
  }
};

void solve(int t) {
  Int n;
  vector<array<Int, 2>> a(n);
  i64 sum1 = 0, sum2 = 0;
  for (int i = 0; i < n; i++) { // O(n)
    auto [x, y] = a[i];
    sum1 += x;
    sum2 += y;
  }
  auto cmp = [&](int i, int j) {
    auto [x1, y1] = a[i];
    auto [x2, y2] = a[j];
    return x1 < y1 ? x2 >= y2 || x1 < x2 || (x1 == x2 && y1 > y2)
                   : x2 > y2 && (x1 == y1 || y1 > y2);
  };
  Iota idx(n, cmp); // O(n*log n)
  SegTree<Seg> segtree(bit_ceil<unsigned>(n), &Seg::join);
  for (int i = 0; i < n; i++) { // O(n)
    auto [x, y] = a[idx[i]];
    segtree[i] = {x, x - y};
  }
  segtree.update(n - 1, false); // O(n)
  i64 ans = LLONG_MAX;
  for (int i = 0; i < n; i++) { // O(n*log n)
    auto [x, y] = a[idx[i]];
    if (sum1 - sum2 + y <= 0) {
      segtree[i] = {};
      segtree.update(i, true);
      ans = min(ans, segtree.full().mx);
      segtree[i] = {x, x - y};
      segtree.update(i, true);
    }
  }
  ans == LLONG_MAX ? ans = -1 : ans += sum1;
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
