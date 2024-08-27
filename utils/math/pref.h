/**
 * (c) 2024 Diego Sogari
 */
#include "matrix.h"

/**
 * Prefix Array
 */
template <typename T> struct Pref : vector<T> {
  int n;
  function<T(const T &, const T &)> f;
  Pref(int n, auto &&f, T val = {}) : vector<T>(n, val), n(n), f(f) {}
  T full() const { return query(0, n - 1); }
  T query(int l, int r) const { // O(n)
    T ans = (*this)[l];
    for (int i = l + 1; i <= r; i++) {
      ans = f(ans, (*this)[i]);
    }
    return ans;
  }
};

/**
 * Prefix Matrix
 */
template <typename T> struct Pref2D : Mat<T> {
  Pref2D(int n, int m) : Mat<T>(n + 1, m + 1) {}
  void rect(T x, const array<int, 4> &range) { // O(1)
    auto [r1, c1, r2, c2] = range;
    (*this)[r1][c1] += x;
    (*this)[r2 + 1][c1] -= x;
    (*this)[r1][c2 + 1] -= x;
    (*this)[r2 + 1][c2 + 1] += x;
  }
  void rows(T x, const array<int, 2> &range) { // O(1)
    auto [r1, r2] = range;
    (*this)[r1][0] += x;
    (*this)[r2 + 1][0] -= x;
  }
  void cols(T x, const array<int, 2> &range) { // O(1)
    auto [c1, c2] = range;
    (*this)[0][c1] += x;
    (*this)[0][c2 + 1] -= x;
  }
  void cross(T x, const array<int, 4> &range) { // O(1)
    auto [r1, c1, r2, c2] = range;
    rows(x, {r1, r2});
    cols(x, {c1, c2});
    rect(-x, range);
  }
  void visit(auto &&f) { // O(n*m)
    vector<T> cur(this->m);
    for (int i = 0; i < this->n - 1; i++) {
      for (int j = 0, prev = 0, saved; j < this->m - 1; j++, prev = saved) {
        saved = cur[j + 1];
        cur[j + 1] += (*this)[i][j] + cur[j] - prev;
        f(i, j, cur[j + 1]);
      }
    }
  }
};
