/**
 * (c) 2024 Diego Sogari
 */
#pragma once

#include "utils.h"

/**
 * Doubly-linked list (with fixed length)
 */
struct DLinked {
  int n;
  vector<int> prev, next;
  DLinked(int n) : n(n), prev(n + 2), next(n + 2) {
    iota(prev.begin(), prev.end(), -1);
    iota(next.begin(), next.end(), 1);
  }
  bool empty() const { return next[0] == n + 1; }      // O(1)
  bool has(int u) const { return prev[next[u]] == u; } // [1,n] O(1)
  bool erase(int u) {                                  // [1,n] O(1)
    if (has(u)) {
      prev[next[u]] = prev[u];
      next[prev[u]] = next[u];
      return true;
    }
    return false;
  }
};
