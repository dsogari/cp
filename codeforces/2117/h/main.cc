/**
 * https://codeforces.com/contest/2117/submission/323683411
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

template <typename T> ostream &operator<<(ostream &os, const vector<T> &a) {
  return ranges::for_each(a, [&os](auto &ai) { os << ai << ' '; }), os;
}
void println(auto &&...args) { ((cout << args << ' '), ...) << endl; }

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;

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
  int msum, lsum, rsum, tsum;             // subarray sums
  Seg operator+(const Seg &right) const { // non-commutative
    return {
        max({msum, right.msum, rsum + right.lsum}),
        max(lsum, tsum + right.lsum),
        max(rsum + right.tsum, right.rsum),
        tsum + right.tsum,
    };
  }
};

void solve(int t) {
  Int n, q;
  vector<Int> a(n);
  vector<array<Int, 2>> queries(q);
  map<int, vector<array<int, 3>>> indices;
  vector<array<array<int, 2>, 2>> changes(q);
  multiset<int> maj;
  vector<int> ans;
  SegTree<Seg> st(bit_ceil<unsigned>(n), {-1, -1, -1, -1});
  st.build();
  for (int i = 0; i < n; i++) {
    indices[a[i]].push_back({i, -1, 1});
  }
  for (int j = 0; j < q; j++) {
    auto [i, x] = queries[j];
    auto y = exchange(a[--i], x);
    indices[y].push_back({i, j, -1});
    indices[x].push_back({i, j, 1});
  }
  for (auto &[x, idx] : indices) {
    for (auto [i, j, k] : idx) {
      if (j >= 0) {
        break;
      }
      st[i] = {k, k, k, k};
      st.update(i);
    }
    maj.insert(st.full().msum);
    for (auto [i, j, k] : idx) {
      if (j < 0) {
        continue;
      }
      auto &[old, cur] = changes[j][(k + 1) / 2];
      old = st.full().msum;
      st[i] = {k, k, k, k};
      st.update(i);
      cur = st.full().msum;
    }
    for (auto [i, _j, _k] : idx) {
      if (st[i].msum < 0) {
        continue;
      }
      st[i] = {-1, -1, -1, -1};
      st.update(i);
    }
  }
  for (auto &[y, x] : changes) {
    maj.erase(maj.find(y[0]));
    maj.insert(y[1]);
    maj.erase(maj.find(x[0]));
    maj.insert(x[1]);
    ans.push_back(*maj.rbegin() / 2);
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
