/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "utils.h"

/**
 * Segment Tree
 */
template <typename T> struct SegTree {
  int n;
  vector<T> nodes;
  SegTree(int n, T val = {}) : n(n), nodes(2 * n, val) {}      // O(n)
  T full() const { return _node(1); }                          // O(1)
  T &operator[](int i) { return nodes[i + n]; }                // O(1)
  T query(int l, int r) const { return _query(l + n, r + n); } // [l,r] O(log n)
  void update() { for (int i = n; --i; _merge(i)); }           // O(n)
  void update(int i) { for (i += n; i >>= 1; _merge(i)); }     // O(log n)
  void update(int l, int r) { // [l,r] O(r-l + log r)
    for (l += n, r += n; l >>= 1, r >>= 1;) {
      for (int i = r; i >= max(1, l); _merge(i--));
    }
  }
  void _merge(int i) { nodes[i] = _node(i << 1) + _node(i << 1 | 1); } // O(1)
  T _query(int l, int r) const { // [l,r] O(log n)
    return l == r   ? _node(l)
           : l & 1  ? _node(l) + _query(l + 1, r)
           : ~r & 1 ? _query(l, r - 1) + _node(r)
                    : _query(l >> 1, r >> 1);
  }
  virtual T _node(int i) const { return nodes[i]; } // O(1)
};

/**
 * Lazy Segment Tree (for range updates and full queries)
 */
template <typename T, typename U> struct LazySegTree : SegTree<T> {
  using SegTree<T>::n, SegTree<T>::nodes, SegTree<T>::update;
  vector<U> lazy;
  LazySegTree(int n, T x = {}, U y = {}) : SegTree<T>(n, x), lazy(2 * n, y) {}
  void update(int l, int r, const U &val) { // [l,r] O(log n)
    _apply(l + n, r + n, val), update(l), update(r);
  }
  void _apply(int l, int r, const U &val) { // [l,r] O(log n)
    l == r   ? (lazy[l] += val, void())
    : l & 1  ? (lazy[l] += val, _apply(l + 1, r, val))
    : ~r & 1 ? (lazy[r] += val, _apply(l, r - 1, val))
             : _apply(l >> 1, r >> 1, val);
  }
  virtual T _node(int i) const { return nodes[i] + lazy[i]; } // O(1)

private:
  using SegTree<T>::query; // only full queries allowed
};

/**
 * Push Segment Tree (for range updates and arbitrary queries)
 */
template <typename T, typename U> struct PushSegTree : LazySegTree<T, U> {
  using SegTree<T>::n, SegTree<T>::update;
  using LazySegTree<T, U>::LazySegTree, LazySegTree<T, U>::lazy;
  T get(int i) { return this->_node(i + n); } // O(1)
  T query(int l, int r) {                     // [l,r] O(log n)
    return push(l), push(r), update(l), update(r), SegTree<T>::query(l, r);
  }
  void update(int l, int r, const U &val) { // [l,r] O(log n)
    push(l), push(r), LazySegTree<T, U>::update(l, r, val);
  }
  void push() { for (int i = 1; i < n; _push(i++)); } // O(n)
  void push(int i) {                                  // O(log n)
    for (int s = bit_width<unsigned>(i += n); --s; _push(i >> s));
  }
  void push(int l, int r) { // [l,r] O(r-l + log r)
    for (int s = (l += n, bit_width<unsigned>(r += n)); --s;) {
      for (int i = max(1, l >> s); i <= r >> s; _push(i++));
    }
  }
  void _push(int i) {         // O(1)
    if (lazy[i] != lazy[0]) { // requires operator<=>
      lazy[i << 1] += lazy[i];
      lazy[i << 1 | 1] += lazy[i];
      lazy[i] = lazy[0];
    }
  }
};

/**
 * Lazy Node for mixed-assignment operations
 */
template <typename T> struct Lazy {
  T val;    // lazy value
  bool set; // add by default
  auto operator<=>(const Lazy &) const = default;
  void operator+=(const Lazy &rhs) {
    set |= rhs.set;
    val = rhs.set ? rhs.val : val + rhs.val;
  }
};

/**
 * Generic Node
 */
struct Seg {
  int x;
  Seg operator+(const Seg &other) const { return {max(x, other.x)}; }
  Seg operator+(const Lazy<int> &rhs) const {
    return {rhs.set ? rhs.val : x + rhs.val};
  }
};
