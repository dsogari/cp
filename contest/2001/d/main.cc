/**
 * https://codeforces.com/contest/2001/submission/277507551
 *
 * (c) 2024 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;

#ifdef ONLINE_JUDGE
#define debug
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

template <typename T> struct SegTree {
  int n;
  vector<T> nodes;
  function<T(const T &, const T &)> f;
  SegTree(int n, auto &&f, T val = {}) : n(n), f(f), nodes(2 * n, val) {}
  const T &full() const { return nodes[1]; }    // O(1)
  T &operator[](int i) { return nodes[i + n]; } // O(1)
  T query(int l, int r) const { return _check(l, r), _query(l + n, r + n); }
  void update(int i) { // O(log n)
    _check(i, i);
    for (i = (i + n) / 2; i > 0; i /= 2) {
      _update(i);
    }
  }
  void update_upto(int i) { // [0, i] O(n)
    _check(i, i);
    for (i = (i + n) / 2; i > 0; i--) {
      _update(i);
    }
  }
  T _query(int l, int r) const { // [l, r] O(log n)
    return l == r       ? nodes[l]
           : l % 2      ? f(nodes[l], _query(l + 1, r))
           : r % 2 == 0 ? f(_query(l, r - 1), nodes[r])
                        : _query(l / 2, r / 2);
  }
  void _update(int i) { nodes[i] = f(nodes[2 * i], nodes[2 * i + 1]); }
  void _check(int l, int r) const { assert(l >= 0 && l <= r && r < n); }
};

const auto tmin = [](auto &lhs, auto &rhs) { return min(lhs, rhs); };
const auto tmax = [](auto &lhs, auto &rhs) { return max(lhs, rhs); };

SegTree<int> segmin(3e5, tmin), segmax(3e5, tmax);

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
  segmin.n = segmax.n = n;      // adjust tree length for the test case
  for (int i = 0; i < n; i++) { // O(n)
    segmin[i] = segmax[i] = a[i];
  }
  segmin.update_upto(n - 1); // O(n)
  segmax.update_upto(n - 1); // O(n)
  vector<int> ans;
  auto f = [&](int &l, int x) { // O(log n) on average
    auto &idx = pos[x];
    auto it = ranges::lower_bound(idx, l);
    assert(it != idx.end());
    l = *it + 1; // increase last used position of the original array
    for (; it != idx.end(); it++) {
      segmin[*it] = INT_MAX; // clear position
      segmax[*it] = INT_MIN; // clear position
      segmin.update(*it);
      segmax.update(*it);
    }
    right.erase(idx.back()); // remove right boundary of this element
    ans.push_back(x);
  };
  auto it = right.begin();
  for (int l = 0; it != right.end(); it = right.begin()) { // O(n*log n)
    auto &segtree = ans.size() % 2 ? segmin : segmax;
    f(l, segtree.query(l, *it));
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
