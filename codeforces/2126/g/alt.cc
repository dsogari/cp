/**
 * https://codeforces.com/contest/2126/submission/329872539
 *
 * Inspired by: https://codeforces.com/contest/2126/submission/329723214
 *
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#define debug(...)
#else
#include "debug.h"
init();
#endif

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

struct Seg {
  int sum, mn, mx;                        // prefmin, prefmax
  Seg operator+(const Seg &other) const { // Kadane's formula
    return {
        sum + other.sum,
        min(mn, sum + other.mn),
        max(mx, sum + other.mx),
    };
  }
  int get() const { return mn - sum; } // because sum is added to the suffix
};

void solve(int t) {
  Int n;
  vector<Int> a(n);
  Iota idx(n, [&](int i, int j) { return a[i] < a[j]; });
  SegTree<Seg> st(n + 1, {1, 1, 1});
  st[0] = {0, 0, 0}; // prefix sum
  st.update();       // build tree
  int ans = 0;
  for (int l = 0, r = 0; r < n; r++) { // O(n log n)
    while (l <= r && st.query(0, idx[l]).get() > st.query(idx[l] + 1, n).mx) {
      l++;
    }
    if (l <= r) {
      ans = max(ans, a[idx[r]] - a[idx[l]]);
    }
    st[idx[r] + 1] = {-1, -1, -1}; // remove idx[r]
    st.update(idx[r] + 1);
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
