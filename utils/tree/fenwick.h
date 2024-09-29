/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Fenwick Tree (Binary indexed tree)
 */
template <typename T> struct FenTree {
  int n;
  vector<T> nodes;
  function<T(const T &, const T &)> f;
  FenTree(int n, auto &&f, T val = {}) : n(n), f(f), nodes(n + 1, val) {}
  T query(int i) const { // O(log n)
    assert(i < n);
    T ans = nodes[0];
    for (i++; i > 0; i -= i & -i) {
      ans = f(ans, nodes[i]);
    }
    return ans;
  }
  void update(int i, const T &val) { // O(log n)
    assert(i >= 0);
    for (i++; i <= n; i += i & -i) {
      nodes[i] = f(nodes[i], val);
    }
  }
};

/**
 * Fenwick Tree (with linear range updates)
 */
template <typename T> struct FenTreePlus : FenTree<T> {
  using FenTree<T>::FenTree;
  void update_from(int l, auto it) { // [l, n] O(n)
    assert(l >= 0);
    for (l++; l <= this->n; l++, it++) {
      this->nodes[l] = this->f(this->nodes[l], *it);
      int r = l + (l & -l);
      if (r <= this->n) {
        this->nodes[r] = this->f(this->nodes[r], *it);
      }
    }
  }
  void update_from(int l, const T &val) { // [l, n] O(n)
    struct {
      const T &val;
      const T &operator*() { return val; }
      void operator++(int) {}
    } it{val};
    update_from(l, it);
  }
};

/**
 * Sparse Fenwick Tree
 */
template <typename T> struct SparseFenTree {
  int n;
  unordered_map<int, T> nodes = {{0, {}}};
  SparseFenTree(int n) : n(n) {}
  T query(int i, auto &&f) const { // O(log n)
    assert(i < n);
    T ans = nodes.find(0)->second;
    for (i++; i > 0; i -= i & -i) {
      auto it = nodes.find(i);
      if (it != nodes.end()) {
        f(ans, it->second);
      }
    }
    return ans;
  }
  void update(int i, auto &&f, const auto &val) { // O(log n)
    assert(i >= 0);
    for (i++; i <= n; i += i & -i) {
      f(nodes[i], val);
    }
  }
};
