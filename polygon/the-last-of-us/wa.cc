/**
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;

#ifdef ONLINE_JUDGE
#define debug(...)
#else
#include "debug.h"
init();
#endif

template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

using Int = Number<int>;

struct Iota : vector<int> {
  Iota(int n, int s = 0) : vector<int>(n) { iota(begin(), end(), s); }
  Iota(int n, auto &&f, int s = 0) : Iota(n, s) { ranges::sort(*this, f); }
};

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

function<bool(int, int)> f;

struct Seg {
  int i;
  Seg operator+(const Seg &rhs) const { return {f(i, rhs.i) ? i : rhs.i}; }
};

void solve(int t) {
  Int n, k;
  vector<Int> a(n);
  vector<array<i64, 2>> cost(n);
  i64 sum = 0;
  for (int i = 0; i < n + k; i++) { // O(n)
    if (i < n) {
      sum += a[i];
    }
    if (i >= k) {
      sum -= a[i - k];
      cost[i - k][1] = sum;
    }
    if (i < n - 1) {
      cost[i + 1][0] = sum;
    }
  }
  auto f1 = [&](int i) { return a[i] - cost[i][0] - cost[i][1]; };
  f = [&](int i, int j) {
    return make_pair(f1(i), a[i]) < make_pair(f1(j), a[j]);
  };
  SegTree<Seg> st(n);
  for (int i = 0; i < n; i++) { // O(n)
    st[i] = {i};
  }
  st.update(); // O(n)
  i64 ans = 0;
  Iota left(n, -1), right(n, 1);
  array<i64, 2> erased = {INT_MIN, INT_MIN};
  for (int total = 0; total < n;) { // O(n*log n)
    auto i = st.full().i;
    ans += a[i];
    cost[i] = erased, st.update(i);
    total++;
    int l = left[i], r = right[i];
    i64 lc = 0, rc = 0;
    for (int c = 0; c < k; c++) {
      if (l >= 0) {
        lc = cost[l][0];
        cost[l] = erased, st.update(l);
        l = left[l];
        total++;
      }
      if (r < n) {
        rc = cost[r][1];
        cost[r] = erased, st.update(r);
        r = right[r];
        total++;
      }
    }
    if (l >= 0) {
      right[l] = r;
    }
    if (r < n) {
      left[r] = l;
    }
    for (int c = 0; c < k; c++) {
      if (l >= 0) {
        cost[l][1] = rc, st.update(l);
        rc += a[l];
        l = left[l];
      }
      if (r < n) {
        cost[r][0] = lc, st.update(r);
        lc += a[r];
        r = right[r];
      }
    }
  }
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
