/**
 * https://codeforces.com/contest/2000/submission/283959707
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
using Chr = Num<char>;

template <typename T> struct SegTree {
  int n;
  vector<T> nodes;
  function<T(const T &, const T &)> f;
  SegTree(int n, auto &&f, T val = {}) : n(n), f(f), nodes(2 * n, val) {}
  T full() const { return _node(1); }           // O(1)
  T get(int i) const { return _node(i + n); }   // O(1)
  T &operator[](int i) { return nodes[i + n]; } // O(1)
  T query(int l, int r) const { return _check(l, r), _query(l + n, r + n); }
  void update(int i, bool single) { _check(i, i), _build(i + n, single); }
  void _build(int i, bool single) { // O(log n) / [0, i] O(n)
    function<void()> dec[] = {[&]() { i--; }, [&]() { i >>= 1; }};
    for (i >>= 1; i > 0; dec[single]()) {
      _merge(i);
    }
  }
  T _query(int l, int r) const { // [l, r] O(log n)
    return l == r   ? _node(l)
           : l & 1  ? f(_node(l), _query(l + 1, r))
           : ~r & 1 ? f(_query(l, r - 1), _node(r))
                    : _query(l >> 1, r >> 1);
  }
  virtual T _node(int i) const { return nodes[i]; }
  void _merge(int i) { nodes[i] = f(_node(i << 1), _node(i << 1 | 1)); }
  void _check(int l, int r) const { assert(l >= 0 && l <= r && r < n); }
};

int binsearch(auto &&f, int s, int e) { // [s, e) O(log n)
  for (int inc = s < e ? 1 : -1; s != e;) {
    auto m = midpoint(s, e);
    f(m) ? s = m + inc : e = m;
  }
  return s; // first such that f is false
}

template <typename T> struct Max {
  T operator()(const T &lhs, const T &rhs) const { return max(lhs, rhs); }
};

constexpr int mxa = 2e6;
SegTree<int> gaps(mxa + 2, Max<int>{});
auto set_gap = [](auto it) { // O(log n)
  auto x = *it + 1;
  gaps[x] = *next(it) - x;
  gaps.update(x, true);
};
auto clear_gap = [](auto it) { // O(log n)
  auto x = *it + 1;
  gaps[x] = 0;
  gaps.update(x, true);
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
    auto f = [&](int x) { return gaps.query(0, x) < k; };
    auto x = binsearch(f, 1, mxa + 2);
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
