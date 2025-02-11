/**
 * https://codeforces.com/contest/1996/submission/305725871
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
  vector<array<Int, 2>> edges;
  Graph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m), edges(m) {
    for (auto &[u, v] : edges) {
      add(u, v);
    }
  }
  void add(int u, int v) { (*this)[u].push_back(v), (*this)[v].push_back(u); }
};

template <class T> struct SegTree {
  int n;
  vector<T> nodes;
  SegTree(int n, const T &val = {}) : n(n), nodes(2 * n, val) {} // O(n)
  T full() const { return _node(1); }                            // O(1)
  T &operator[](int i) { return nodes[i + n]; }                  // O(1)
  virtual T _node(int i) const { return nodes[i]; }              // O(1)
  void build() { for (int i = n; --i; _merge(i)); }              // O(n)
  void update(int i) { for (i += n; i >>= 1; _merge(i)); }       // O(lg n)
  void _merge(int i) { nodes[i] = _node(i << 1) + _node(i << 1 | 1); } // O(1)
  T query(int l, int r) const { return _query(l + n, r + n); } // [l, r] O(lg n)
  T _query(int l, int r) const {                               // [l, r] O(lg n)
    return l == r   ? _node(l)
           : l & 1  ? _node(l) + _query(l + 1, r)
           : ~r & 1 ? _query(l, r - 1) + _node(r)
                    : _query(l >> 1, r >> 1);
  }
};

template <typename T, typename U> struct LazySegTree : SegTree<T> {
  using SegTree<T>::update;
  vector<U> lazy;
  LazySegTree(int n, T val = {}, U lazyval = {})
      : SegTree<T>(n, val), lazy(2 * n, lazyval) {} // O(n)
  void update(int l, int r, const U &val) {         // [l, r] O(lg n)
    _apply(l + this->n, r + this->n, val);
    update(l), update(r);
  }
  void _apply(int l, int r, const U &val) { // [l, r] O(lg n)
    l == r   ? (lazy[l] += val, void())
    : l & 1  ? (lazy[l] += val, _apply(l + 1, r, val))
    : ~r & 1 ? (lazy[r] += val, _apply(l, r - 1, val))
             : _apply(l >> 1, r >> 1, val);
  }
  virtual T _node(int i) const { return this->nodes[i] + lazy[i]; } // O(1)

private:
  using SegTree<T>::query; // only full queries allowed
};

struct Seg {
  int mn, cnt;
  Seg operator+(const Seg &rhs) const {
    auto ans = mn <= rhs.mn ? *this : rhs;
    if (mn == rhs.mn) {
      ans.cnt += rhs.cnt;
    }
    return ans;
  }
  Seg operator+(int lazy) const { return {mn + lazy, cnt}; }
};

void solve(int t) {
  SegTree<int> a(1);
  a.query(0, 0);
  Int n, m;
  Graph g(n, m);
  LazySegTree<Seg, int> segtree(n, {0, 1});
  segtree.build();
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
