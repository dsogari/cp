/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Segment Tree
 */
template <typename T> struct SegTree {
  int n;
  vector<T> nodes;
  SegTree(int n, T val = {}) : n(n), nodes(2 * n, val) {}
  T full() const { return _node(1); }           // O(1)
  T &operator[](int i) { return nodes[i + n]; } // O(1)
  T query(int l, int r) const { return _check(l, r), _query(l + n, r + n); }
  T _query(int l, int r) const { // [l, r] O(log n)
    return l == r   ? _node(l)
           : l & 1  ? _node(l) + _query(l + 1, r)
           : ~r & 1 ? _query(l, r - 1) + _node(r)
                    : _query(l >> 1, r >> 1);
  }
  void update(int i, bool single) { _check(i, i), _update(i + n, single); }
  void _update(int i, bool single) { // O(log n) / [0, i] O(n)
    function<void()> dec[] = {[&]() { i--; }, [&]() { i >>= 1; }};
    for (i >>= 1; i > 0; dec[single]()) {
      nodes[i] = _node(i << 1) + _node(i << 1 | 1);
    }
  }
  virtual T _node(int i) const { return nodes[i]; }
  void _check(int l, int r) const { assert(l >= 0 && l <= r && r < n); }
};

/**
 * Lazy Segment Tree (for range updates and full queries)
 */
template <typename T, typename U> struct LazySegTree : SegTree<T> {
  vector<U> lazy;
  LazySegTree(int n, T val = {}, U lazyval = {})
      : SegTree<T>(n, val), lazy(2 * n, lazyval) {}
  using SegTree<T>::update;
  void update(int l, int r, const U &val) { // [l, r] O(log n)
    this->_check(l, r);
    _apply(l + this->n, r + this->n, val);
    this->_update(l + this->n, true);
    this->_update(r + this->n, true);
  }
  void _apply(int l, int r, const U &val) { // [l, r] O(log n)
    return l == r   ? _apply(l, val)
           : l & 1  ? (_apply(l, val), _apply(l + 1, r, val))
           : ~r & 1 ? (_apply(r, val), _apply(l, r - 1, val))
                    : _apply(l >> 1, r >> 1, val);
  }
  void _apply(int i, const U &val) { lazy[i] += val; }
  virtual T _node(int i) const { return this->nodes[i] + lazy[i]; }

private:
  using SegTree<T>::query; // hide method (only full queries allowed)
};

/**
 * Push Segment Tree (for range updates and arbitrary queries)
 */
template <typename T, typename U> struct PushSegTree : LazySegTree<T, U> {
  using LazySegTree<T, U>::LazySegTree;
  T query(int l, int r) { // [l, r] O(log n)
    this->_check(l, r);
    _push(l + this->n, true);
    _push(r + this->n, true);
    return this->_query(l + this->n, r + this->n);
  }
  void pushall(int i) { this->_check(i, i), _push(i + this->n, false); }
  void _push(unsigned i, bool single) { // O(log n) / [0, i] O(n)
    int s = bit_width(i), j = 0, end = single ? i : i / 2 + 1;
    function<void()> inc[] = {[&]() { j++; }, [&]() { s--, j = i >> s; }};
    for (inc[single](); j != end; inc[single]()) { // O(1)
      if (this->lazy[j] != this->lazy[0]) {        // requires operator<=>
        this->_apply(j << 1, this->lazy[j]);
        this->_apply(j << 1 | 1, this->lazy[j]);
        this->lazy[j] = this->lazy[0];
      }
    }
    this->_update(i, single);
  }
};

/**
 * Lazy Node for mixed-assignment operations
 */
template <typename T, typename U> struct Lazy {
  bool set; // add by default
  U val;    // lazy value
  auto operator<=>(const Lazy &) const = default;
  void operator+=(const Lazy &rhs) {
    set |= rhs.set;
    val = rhs.set ? rhs.val : val + rhs.val;
  }
};

/**
 * Seg operator+(const Lazy &rhs) const {
 *  return rhs.set ? rhs.val : x + rhs.val;
 * }
 */

/**
 * Assignment Segment Tree (supports range assignments)
 */
template <typename T, typename U>
struct AssignSegTree : PushSegTree<T, Lazy<T, U>> {
  AssignSegTree(int n, T val = {}, U lazyval = {})
      : PushSegTree<T, Lazy<T, U>>(n, val, {false, lazyval}) {}
  using SegTree<T>::update;
  void update(int l, int r, const U &val, bool set) { // [l, r] O(log n)
    this->_check(l, r);
    this->_push(l + this->n, true);
    this->_push(r + this->n, true);
    this->_apply(l + this->n, r + this->n, {set, val});
    this->_update(l + this->n, true);
    this->_update(r + this->n, true);
  }
};
