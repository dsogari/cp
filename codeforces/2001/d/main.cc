/**
 * https://codeforces.com/contest/2001/submission/305442233
 *
 * (c) 2024 Diego Sogari
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
  int mn, mx;
  Seg operator+(const Seg &other) const {
    return {min(mn, other.mn), max(mx, other.mx)};
  }
};

SegTree<Seg> st(3e5);

void solve(int t) {
  Int n;
  vector<Int> a(n);
  map<int, vector<int>> pos;
  for (int i = 0; i < n; i++) { // O(n*log n)
    pos[a[i]].push_back(i);
  }
  set<int> right;              // maximum position of each distinct element
  for (auto &[_, idx] : pos) { // O(n*log n)
    right.insert(idx.back());
  }
  st.n = n;                     // adjust tree length for the test case
  for (int i = 0; i < n; i++) { // O(n)
    st[i] = {a[i], a[i]};
  }
  st.build(); // O(n)
  vector<int> ans;
  auto f = [&](int &l, int x) { // O(log n) on average
    auto &idx = pos[x];
    auto it = ranges::lower_bound(idx, l);
    assert(it != idx.end());
    l = *it + 1; // increase last used position of the original array
    for (; it != idx.end(); it++) {
      st[*it] = {INT_MAX, INT_MIN}; // clear position
      st.update(*it);
    }
    right.erase(idx.back()); // remove right boundary of this element
    ans.push_back(x);
  };
  auto it = right.begin();
  for (int l = 0; it != right.end(); it = right.begin()) { // O(n*log n)
    auto seg = st.query(l, *it);
    f(l, ans.size() % 2 ? seg.mn : seg.mx);
  }
  assert(ans.size() == pos.size());
  println(ans.size());
  println(ans);
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
