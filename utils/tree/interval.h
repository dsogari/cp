/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Interval Tree Node
 */
template <typename T> struct Interval {
  T mid;
  list<array<T, 2>> contained;
  void insert(T l, T r) { contained.push_back({l, r}); } // O(1)
  void visit(T x, auto &&f) {                            // O(n)
    for (auto it = contained.begin(); it != contained.end();) {
      auto [l, r] = *it;
      it = l <= x && x < r && f(l, r) ? contained.erase(it) : next(it);
    }
  }
  bool contains(T x) const {
    auto f = [&](auto &pair) { return pair[0] <= x && x < pair[1]; };
    return ranges::find_if(contained, f) != contained.end();
  }
};

/**
 * Interval Tree
 */
template <typename T> struct IntTree {
  int n;
  vector<Interval<T>> nodes;
  IntTree(int n) : n(n), nodes(2 * n) {}
  IntTree(int n, T l, T r) : IntTree(n) { build(l, r); }
  void build(T l, T r, int i = 1) { // [l, r) O(n)
    auto mid = nodes[i].mid = (l + r) / 2;
    if (i < n) {
      build(l, mid, 2 * i);
      build(mid, r, 2 * i + 1);
    }
  }
  void insert(T l, T r) { // [l, r) O(log n)
    assert(l < r);
    int i = 1;
    while (i < n && (l >= nodes[i].mid || r <= nodes[i].mid)) {
      i = 2 * i + (l >= nodes[i].mid);
    }
    nodes[i].insert(l, r);
  }
  void visit(T x, auto &&f) { // O(n^2) all covering point x
    int i = 1;
    for (; i < n; i = 2 * i + (x >= nodes[i].mid)) {
      nodes[i].visit(x, f); // internal node
    }
    nodes[i].visit(x, f); // leaf node
  }
  bool contains(T x) const {
    int i = 1;
    for (; i < n; i = 2 * i + (x >= nodes[i].mid)) {
      if (nodes[i].contains(x)) { // internal node
        return true;
      }
    }
    return nodes[i].contains(x); // leaf node
  }
};
