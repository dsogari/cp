/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Segment Tree
 */
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

/**
 * Lazy Segment Tree (for range updates and full queries)
 */
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

/**
 * Push Segment Tree (for range updates and arbitrary queries)
 */
template <typename T, typename U> struct PushSegTree : LazySegTree<T, U> {
  using SegTree<T>::n;
  using SegTree<T>::update;
  using LazySegTree<T, U>::LazySegTree;
  T get(int i) { return this->_node(i + n); } // O(1)
  T query(int l, int r) {                     // O(lg n)
    push(l), push(r), update(l), update(r);
    return SegTree<T>::query(l, r);
  }
  void update(int l, int r, const U &val) { // O(lg n)
    push(l), push(r);
    LazySegTree<T, U>::update(l, r, val);
  }
  void push() { for (int i = 1; i < n; _push(i++)); } // O(n)
  void push(unsigned i) { for (int s = bit_width(i += n); --s; _push(i >> s)); }
  void _push(unsigned i) {                // O(1)
    if (this->lazy[i] != this->lazy[0]) { // requires operator<=>
      this->lazy[i << 1] += this->lazy[i];
      this->lazy[i << 1 | 1] += this->lazy[i];
      this->lazy[i] = this->lazy[0];
    }
  }
};

/**
 * Lazy Node for mixed-assignment operations
 */
template <typename T> struct Lazy {
  T val;            // lazy value
  bool set = false; // add by default
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
