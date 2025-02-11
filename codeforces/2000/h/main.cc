/**
 * https://codeforces.com/contest/2000/submission/305725626
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
using Chr = Num<char>;

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

constexpr auto first_false(auto &&f, auto s, auto e) { // [s, e) O(log n)
  return *ranges::partition_point(ranges::views::iota(s, e), f);
}

struct Seg {
  int x;
  Seg operator+(const Seg &other) const { return {max(x, other.x)}; }
};

constexpr int mxa = 2e6;
SegTree<Seg> gaps(mxa + 2);
auto set_gap = [](auto it) { // O(log n)
  auto x = *it + 1;
  gaps[x] = {*next(it) - x};
  gaps.update(x);
};
auto clear_gap = [](auto it) { // O(log n)
  auto x = *it + 1;
  gaps[x] = {0};
  gaps.update(x);
};

void solve(int t) { // O((n + m)*log n)
  Int n;
  vector<Int> a(n);
  Int m;
  vector<pair<Chr, Int>> ops(m);
  set<int> vals(a.begin(), a.end()); // O(n*log n)
  vals.insert({0, 2 * mxa + 1});
  for (auto it = vals.begin(), end = prev(vals.end()); it != end; it++) {
    set_gap(it);
  }
  function<void(int)> add = [&](int x) { // O(log n)
    auto [it, ok] = vals.insert(x);
    if (ok) {
      set_gap(it);
      set_gap(prev(it));
    }
  };
  function<void(int)> rem = [&](int x) { // O(log n)
    auto it = vals.find(x);
    if (it != vals.end()) {
      clear_gap(it);
      it = vals.erase(it);
      set_gap(prev(it));
    }
  };
  vector<int> ans;
  function<void(int)> rep = [&](int k) { // O(log^2 n)
    auto f = [&](int x) { return gaps.query(0, x).x < k; };
    auto x = first_false(f, 1, mxa + 2);
    ans.push_back(x);
  };
  for (auto &&[type, x] : ops) { // O(m*log^2 n)
    auto op = type == '+' ? add : type == '-' ? rem : rep;
    op(x);
  }
  println(ans);
  for (auto it = vals.begin(), end = prev(vals.end()); it != end; it++) {
    clear_gap(it);
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  Int t;
  for (int i = 1; i <= t; i++) {
    solve(i);
  }
}
