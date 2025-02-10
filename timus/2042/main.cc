/**
 * (c) 2024-2025 Diego Sogari
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

template <typename T> struct Num {
  T x;
  Num() { cin >> x; }
  Num(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};
using Int = Num<int>;
using Chr = Num<char>;

struct Str : string {
  Str() { cin >> *this; }
};

template <typename T> struct SegTree {
  int n;
  vector<T> nodes;
  SegTree(int n, T val = {}) : n(n), nodes(2 * n, val) {}
  T full() const { return _node(1); }           // O(1)
  T &operator[](int i) { return nodes[i + n]; } // O(1)
  T query(int l, int r) const { return _check(l, r), _query(l + n, r + n); }
  T _query(int l, int r) const { // [l, r] O(log n)
    return l == r   ? _node(l)
           : l & 1  ? _node(l) + _query(l + 1, r)
           : ~r & 1 ? _query(l, r - 1) + _node(r)
                    : _query(l >> 1, r >> 1);
  }
  void update(int i, bool single) { _check(i, i), _update(i + n, single); }
  void _update(int i, bool single) { // O(log n) / [0, i] O(n)
    function<void()> dec[] = {[&]() { i--; }, [&]() { i >>= 1; }};
    for (i >>= 1; i > 0; dec[single]()) {
      nodes[i] = _node(i << 1) + _node(i << 1 | 1);
    }
  }
  virtual T _node(int i) const { return nodes[i]; }
  void _check(int l, int r) const { assert(l >= 0 && l <= r && r < n); }
};

template <typename T, typename U> struct LazySegTree : SegTree<T> {
  vector<U> lazy;
  LazySegTree(int n, T val = {}, U lazyval = {})
      : SegTree<T>(n, val), lazy(2 * n, lazyval) {}
  using SegTree<T>::update;
  void update(int l, int r, const U &val) { // [l, r] O(log n)
    this->_check(l, r);
    _apply(l + this->n, r + this->n, val);
    this->_update(l + this->n, true);
    this->_update(r + this->n, true);
  }
  void _apply(int l, int r, const U &val) { // [l, r] O(log n)
    return l == r   ? _apply(l, val)
           : l & 1  ? (_apply(l, val), _apply(l + 1, r, val))
           : ~r & 1 ? (_apply(r, val), _apply(l, r - 1, val))
                    : _apply(l >> 1, r >> 1, val);
  }
  void _apply(int i, const U &val) { lazy[i] += val; }
  virtual T _node(int i) const { return this->nodes[i] + lazy[i]; }

private:
  using SegTree<T>::query; // hide method (only full queries allowed)
};

template <typename T, typename U> struct PushSegTree : LazySegTree<T, U> {
  using LazySegTree<T, U>::LazySegTree;
  T query(int l, int r) { // [l, r] O(log n)
    this->_check(l, r);
    _push(l + this->n, true);
    _push(r + this->n, true);
    return this->_query(l + this->n, r + this->n);
  }
  void pushall(int i) { this->_check(i, i), _push(i + this->n, false); }
  void _push(unsigned i, bool single) { // O(log n) / [0, i] O(n)
    int s = bit_width(i), j = 0, end = single ? i : i / 2 + 1;
    function<void()> inc[] = {[&]() { j++; }, [&]() { s--, j = i >> s; }};
    for (inc[single](); j != end; inc[single]()) { // O(1)
      if (this->lazy[j] != this->lazy[0]) {        // requires operator<=>
        this->_apply(j << 1, this->lazy[j]);
        this->_apply(j << 1 | 1, this->lazy[j]);
        this->lazy[j] = this->lazy[0];
      }
    }
    this->_update(i, single);
  }
};

template <typename T, typename U> struct Lazy {
  bool set; // add by default
  U val;    // lazy value
  auto operator<=>(const Lazy &) const = default;
  void operator+=(const Lazy &rhs) {
    set |= rhs.set;
    val = rhs.set ? rhs.val : val + rhs.val;
  }
};

template <typename T, typename U>
struct AssignSegTree : PushSegTree<T, Lazy<T, U>> {
  AssignSegTree(int n, T val = {}, U lazyval = {})
      : PushSegTree<T, Lazy<T, U>>(n, val, {false, lazyval}) {}
  using SegTree<T>::update;
  void update(int l, int r, const U &val, bool set) { // [l, r] O(log n)
    this->_check(l, r);
    this->_push(l + this->n, true);
    this->_push(r + this->n, true);
    this->_apply(l + this->n, r + this->n, {set, val});
    this->_update(l + this->n, true);
    this->_update(r + this->n, true);
  }
};

struct Manacher : vector<int> {
  Manacher(auto &&a, int s = 0) : Manacher(a, s, a.size()) {}
  Manacher(auto &&a, int s, int e) : vector<int>(e - s) { // [s, e) O(n)
    auto &z = *this;
    for (int i = 0, j = 0; i + s < e; i++) {
      auto &c = z[i] = max(0, min(j + z[j] - i, z[max(0, 2 * j - i)]));
      while (i + c + s < e && i - c >= s && a[i + c + s] == a[i - c + s]) {
        c++, j = i; // update center of palindrome
      }
    }
  }
};

vector<array<int, 2>> manacher(auto &&a, int s, int e, auto d) { // [s, e) O(n)
  typename remove_cvref<decltype(a)>::type b = {d};
  for (int i = s; i < e; i++) {
    b.insert(b.end(), {a[i], d});
  }
  Manacher z(b);
  vector<array<int, 2>> ans(e - s);
  for (int i = 0; i < e - s; i++) {
    ans[i][0] = (z[2 * i] - 1) / 2; // even
    ans[i][1] = (z[2 * i + 1]) / 2; // odd
  }
  return ans;
}

struct Query {
  Int type, l, r;
  Chr c = 0;
  Query() {
    if (type == 1) {
      c = {};
    }
  }
};

struct Seg {
  int l, r;
  string s;
  Seg operator+(const Seg &rhs) const {
    return l < rhs.l ? Seg{l, rhs.r, s + rhs.s} : Seg{rhs.l, r, rhs.s + s};
  }
  Seg operator+(const Lazy<Seg, char> &lazy) const {
    return lazy.set ? set(lazy.val) : *this;
  }
  Seg set(char c) const { return {l, r, string(r - l + 1, c)}; }
};

void solve() {
  Str s;
  int n = s.size();
  Int k, m;
  vector<Query> q(m);
  AssignSegTree<Seg, char> segtree(n);
  for (int i = 0; i < n; i++) {
    segtree[i] = {i, i, s.substr(i, 1)};
  }
  segtree.update(n - 1, false);
  auto f = [&](int l, int r) { // O(|r-l+1|+log n)
    auto str = segtree.query(l, r).s;
    auto cnt = manacher(str, 0, str.size(), '#');
    i64 ans = 0;
    for (auto &[even, odd] : cnt) {
      ans += min(k / 2, even) + min((k + 1) / 2, odd);
    }
    println(ans);
  };
  for (auto &[type, l, r, c] : q) {
    type == 1 ? segtree.update(l - 1, r - 1, c, true) : f(l - 1, r - 1);
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  solve();
}
