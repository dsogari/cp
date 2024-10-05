/**
 * https://codeforces.com/contest/1996/submission/282544166
 *
 * (c) 2024 Diego Sogari
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

struct Graph : vector<vector<int>> {
  const int n, m;
  Graph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m) {
    for (auto &[u, v] : vector<array<Int, 2>>(m)) {
      add(u, v);
    }
  }
  void add(int u, int v) { _add(u, v), _add(v, u); }
  void _add(int u, int v) { (*this)[u].push_back(v); }
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

template <typename T, typename U> struct LazySegTree : SegTree<T> {
  vector<U> lazy;
  function<T(const T &, const U &)> ftree;
  function<U(const U &, const U &)> flazy;
  LazySegTree(int n, auto &&f, auto &&ft, auto &&fl, T val = {}, U lazyval = {})
      : SegTree<T>(n, f, val), ftree(ft), flazy(fl), lazy(2 * n, lazyval) {}
  using SegTree<T>::update;
  void update(int l, int r, const U &val) { // [l, r] O(log n)
    this->_check(l, r);
    _apply(l + this->n, r + this->n, val);
    this->_build(l + this->n, true);
    this->_build(r + this->n, true);
  }
  void _apply(int l, int r, const U &val) { // [l, r] O(log n)
    return l == r   ? _apply(l, val)
           : l & 1  ? (_apply(l, val), _apply(l + 1, r, val))
           : ~r & 1 ? (_apply(r, val), _apply(l, r - 1, val))
                    : _apply(l >> 1, r >> 1, val);
  }
  void _apply(int i, const U &val) { lazy[i] = flazy(lazy[i], val); }
  virtual T _node(int i) const { return ftree(this->nodes[i], lazy[i]); }

private:
  using SegTree<T>::query; // hide method (only full queries allowed)
};

struct Seg {
  int mn, cnt;
  Seg join(const Seg &rhs) const {
    auto ans = mn <= rhs.mn ? *this : rhs;
    if (mn == rhs.mn) {
      ans.cnt += rhs.cnt;
    }
    return ans;
  }
  Seg add(int x) const { return {mn + x, cnt}; }
};

void solve(int t) {
  Int n, m;
  Graph g(n, m);
  LazySegTree<Seg, int> segtree(n, &Seg::join, &Seg::add, plus<int>{}, {0, 1});
  segtree.update(n - 1, false);  // build the tree
  for (int u = 1; u <= n; u++) { // O(n + m*log n)
    for (auto &v : g[u]) {
      if (u < v) {
        segtree.update(u - 1, v - 2, 1);
      }
    }
  }
  auto f = [&](int u, int v, int c) { // O(log n)
    if (u > 1) {
      segtree.update(0, u - 2, -c);
    }
    segtree.update(u - 1, v - 2, c); // path between u and v
    segtree.update(v - 1, n - 1, -c);
  };
  int mx = segtree.full().cnt;
  for (int u = 1; u <= n; u++) { // O(n + m*log n)
    for (auto &v : g[u]) {
      u < v ? f(u, v, -1) : f(v, u, 1); // toggle paths
    }
    auto [mn, cnt] = segtree.full();
    assert(mn == 0);
    mx = max(mx, cnt);
  }
  println(n - mx);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
