/**
 * https://codeforces.com/contest/2114/submission/326782397
 *
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

void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

using Int = Number<int>;

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

struct Seg {
  int expl, expr;
  i64 suml, sumr;
  Seg operator+(const Seg &rhs) const { // non-commutative
    auto l = (1 << expr) - (expr <= rhs.expl ? 0 : (1 << (rhs.expl + 1)) - 1);
    auto r = (1 << rhs.expl) - (rhs.expl <= expr ? 0 : (1 << (expr + 1)) - 1);
    return {
        expl,
        rhs.expr,
        suml + rhs.suml + l,
        sumr + rhs.sumr + r,
    };
  }
};

void solve(int t) {
  Int n, k;
  vector<Int> a(n);
  SegTree<Seg> st(bit_ceil<unsigned>(n));
  for (int i = 0; i < n; i++) { // O(n*log n)
    int e = countr_zero<unsigned>(a[i]);
    a[i] >>= e; // get odd quotient
    st[i] = {e, e, 0, 0};
  }
  st.build();
  vector<array<i64, 3>> pref = {{0, 0, 0}};
  for (int i = 0, j = 0; i <= n; i++) { // O(n*log n)
    if (i == n || a[i] != a[j]) {
      auto [l, _, r] = pref.back();
      i64 m = 0;
      for (int k = j; k < i; k++) {
        auto pref = st.query(j, k);
        auto suff = st.query(k, i - 1);
        auto sum = pref.suml + (1 << st[k].expl) + suff.sumr;
        m = max(m, sum);
        if (k == j) {
          r += sum;
        }
        if (k == i - 1) {
          l += sum;
        }
      }
      pref.push_back({l, m, r});
      j = i;
    }
  }
  i64 mx = 0;
  for (int i = 1; i < pref.size(); i++) { // O(n)
    mx = max(mx, pref[i - 1][0] + pref[i][1] + pref.back()[2] - pref[i][2]);
  }
  auto ans = k <= mx ? "YES" : "NO";
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
