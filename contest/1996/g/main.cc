/**
 * https://codeforces.com/contest/1996/submission/277956244
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

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

// struct Graph : vector<vector<int>> {
//   const int n, m;
//   Graph(int n, int m = 0) : vector<vector<int>>(n + 1), n(n), m(m) {
//     for (auto &[u, v] : vector<array<Int, 2>>(m)) {
//       add(u, v);
//     }
//   }
//   void add(int u, int v) { _add(u, v), _add(v, u); }
//   void _add(int u, int v) { (*this)[u].push_back(v); }
// };

// template <typename T> struct SegTree {
//   int n;
//   vector<T> nodes;
//   function<T(const T &, const T &)> f;
//   SegTree(int n, auto &&f, T val = {}) : n(n), f(f), nodes(2 * n, val) {}
//   const T &full() const { return nodes[1]; }    // O(1)
//   T &operator[](int i) { return nodes[i + n]; } // O(1)
//   T query(int l, int r) const { return _check(l, r), _query(l + n, r + n); }
//   void update(int i) { // O(log n)
//     _check(i, i);
//     for (i = (i + n) / 2; i > 0; i /= 2) {
//       _update(i);
//     }
//   }
//   void update_upto(int i) { // [0, i] O(n)
//     _check(i, i);
//     for (i = (i + n) / 2; i > 0; i--) {
//       _update(i);
//     }
//   }
//   T _query(int l, int r) const { // [l, r] O(log n)
//     return l == r       ? nodes(l)
//            : l % 2      ? f(nodes(l), _query(l + 1, r))
//            : r % 2 == 0 ? f(_query(l, r - 1), nodes(r))
//                         : _query(l / 2, r / 2);
//   }
//   void _update(int i) { nodes[i] = f(nodes[2 * i], nodes[2 * i + 1]); }
//   void _check(int l, int r) const { assert(l >= 0 && l <= r && r < n); }
// };

// template <typename T, typename U> struct LazySegTree : SegTree<T> {
//   function<T(const T &, const U &)> f2;
//   LazySegTree(int n, auto &&f, auto &&f2, T val = {})
//       : SegTree<T>(n, f, val), f2(f2) {}
//   void update(int l, int r, U val) { // [l, r] O(log n)
//     this->_check(l, r);
//     _update(l + this->n, r + this->n, val);
//   }
//   void _update(int l, int r, const U &val) { // [l, r] O(log n)
//     return l == r       ? (_apply(l, val), this->update(l))
//            : l % 2      ? (_apply(l, val), _update(l + 1, r, val))
//            : r % 2 == 0 ? (_update(l, r - 1, val), _apply(r, val))
//                         : _update(l / 2, r / 2, val);
//   }
//   void _apply(int i, const U &val) { this->nodes[i] = f2(this->nodes[i],
//   val); }
// };

// struct Seg {
//   int mn, cnt;
//   Seg join(const Seg &rhs) const {
//     auto ans = mn <= rhs.mn ? *this : rhs;
//     if (mn == rhs.mn) {
//       ans.cnt += rhs.cnt;
//     }
//     return ans;
//   }
//   Seg add(int x) const { return {mn + x, cnt}; }
// };

// const auto tadd = [](auto &lhs, auto &rhs) { return lhs + rhs; };

void solve(int t) {
  // Int n, m;
  // Graph g(n, m);
  // LazySegTree<Seg, int> segtree(n, &Seg::join, &Seg::add, tadd, {0, 1}, 0);
  // segtree.update_upto(n - 1);    // build the tree
  // for (int u = 1; u <= n; u++) { // O(n + m*log n)
  //   for (auto &v : g[u]) {
  //     if (u < v) {
  //       segtree.update(u - 1, v - 2, 1);
  //     }
  //   }
  // }
  // auto f = [&](int u, int v, int c) { // O(log n)
  //   if (u > 1) {
  //     segtree.update(0, u - 2, -c);
  //   }
  //   segtree.update(u - 1, v - 2, c); // path between u and v
  //   segtree.update(v - 1, n - 1, -c);
  // };
  // int mx = 0;
  // for (int u = 1; u <= n; u++) { // O(n + m*log n)
  //   for (auto &v : g[u]) {
  //     u < v ? f(u, v, -1) : f(v, u, 1); // toggle paths
  //   }
  //   auto [mn, cnt] = segtree.full();
  //   assert(mn == 0);
  //   mx = max(mx, cnt);
  // }
  // println(n - mx);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
