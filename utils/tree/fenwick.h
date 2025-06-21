/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "math/hash.h"

/**
 * Fenwick Tree (Binary indexed tree)
 */
template <typename T> struct FenTree {
  int n;
  vector<T> nodes;
  FenTree(int n, T val = {}) : n(n), nodes(n + 1, val) {}
  T query(int i) const { // O(log n)
    assert(i < n);
    T ans = nodes[0];
    for (i++; i > 0; i -= i & -i) ans += nodes[i];
    return ans;
  }
  void update(int i, const T &val) { // O(log n)
    assert(i >= 0);
    for (i++; i <= n; i += i & -i) nodes[i] += val;
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
      this->nodes[l] += *it;
      int r = l + (l & -l);
      if (r <= this->n) {
        this->nodes[r] += *it;
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
  unordered_map<int, T, SplitHash> nodes;
  SparseFenTree(int n, T val = {}) : n(n), nodes{{0, val}} {}
  T query(int i) const { // O(log n)
    assert(i < n);
    T ans = nodes.find(0)->second;
    for (i++; i > 0; i -= i & -i) {
      auto it = nodes.find(i);
      if (it != nodes.end()) {
        ans += it->second;
      }
    }
    return ans;
  }
  void update(int i, const T &val) { // O(log n)
    assert(i >= 0);
    for (i++; i <= n; i += i & -i) nodes[i] += val;
  }
};

/**
 * Fenwick Tree node
 */
struct Node {
  int x;
  Node(int a = 0) : x(a) {}
  Node &operator+=(const Node &rhs) {
    x = max(x, rhs.x);
    return *this;
  }
};
