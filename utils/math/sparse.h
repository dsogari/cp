/**
 * (c) 2024 Diego Sogari
 */
#include "utils.h"

/**
 * Sparse Table
 */
template <typename T> struct Sparse {
  int k, n;
  vector<vector<T>> nodes;
  function<T(const T &, const T &)> f;
  Sparse(int n, auto &&f)
      : k(bit_width(unsigned(n))), n(n), f(f), nodes(k, vector<T>(n)) {}
  T &operator[](int i) { return nodes[0][i]; } // O(1)
  void build() {                               // O(n*log n)
    for (int i = 0; i < k - 1; i++) {
      for (int j = 0; j + (1 << i) < n; j++) {
        nodes[i + 1][j] = f(nodes[i][j], nodes[i][j + (1 << i)]);
      }
    }
  }
  T query(int l, int r) const { // [l, r] O(log n)
    _check(l, r);
    T ans = {};
    for (int i = k - 1; i >= 0; i--) {
      if ((1 << i) <= r - l + 1) {
        ans = f(ans, nodes[i][l]);
        l += 1 << i;
      }
    }
    return ans;
  }
  T min(int l, int r) const { // [l, r] O(1)
    _check(l, r);
    int i = bit_width(unsigned(r - l + 1)) - 1;
    return f(nodes[i][l], nodes[i][r - (1 << i) + 1]);
  }
  void _check(int l, int r) const { assert(l >= 0 && l <= r && r < n); }
};

/**
 * Disjoint Sparse Table
 */
template <typename T> struct DST {
  int k, n;
  vector<vector<T>> nodes;
  function<T(const T &, const T &)> f;
  DST(unsigned n, auto &&f)
      : k(bit_width(n) + 1), n(n), f(f), nodes(k, vector<T>(1 << k - 1)) {}
  T &operator[](int i) { return nodes[0][i]; } // O(1)
  void build() {                               // O(n*log n)
    for (int h = 1; h < k; h++) {
      int range = 1 << h, half = 1 << h - 1;
      for (int i = half; i < n; i += range) {
        nodes[h][i - 1] = nodes[0][i - 1];
        for (int j = i - 2; j >= i - half; j--) {
          nodes[h][j] = f(nodes[h][j + 1], nodes[0][j]);
        }
        nodes[h][i] = nodes[0][i];
        for (int j = i + 1; j < i + half; j++) {
          nodes[h][j] = f(nodes[h][j - 1], nodes[0][j]);
        }
      }
    }
  }
  T query(int l, int r) const { // [l, r] O(1)
    _check(l, r);
    if (l == r) {
      return nodes[0][l];
    }
    int h = bit_width(unsigned(l ^ r));
    return f(nodes[h][l], nodes[h][r]);
  }
  void _check(int l, int r) const { assert(l >= 0 && l <= r && r < n); }
};
