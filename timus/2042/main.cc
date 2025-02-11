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

template <typename T, typename U> struct LazySegTree : SegTree<T> {
  using SegTree<T>::update;
  vector<U> lazy;
  LazySegTree(int n, T val = {}, U lazyval = {})
      : SegTree<T>(n, val), lazy(2 * n, lazyval) {} // O(n)
  void update(int l, int r, const U &val) {         // [l, r] O(lg n)
    _apply(l + this->n, r + this->n, val);
    update(l), update(r);
  }
  void _apply(int l, int r, const U &val) { // [l, r] O(lg n)
    l == r   ? (lazy[l] += val, void())
    : l & 1  ? (lazy[l] += val, _apply(l + 1, r, val))
    : ~r & 1 ? (lazy[r] += val, _apply(l, r - 1, val))
             : _apply(l >> 1, r >> 1, val);
  }
  virtual T _node(int i) const { return this->nodes[i] + lazy[i]; } // O(1)

private:
  using SegTree<T>::query; // only full queries allowed
};

template <typename T, typename U> struct PushSegTree : LazySegTree<T, U> {
  using SegTree<T>::n;
  using SegTree<T>::update;
  using LazySegTree<T, U>::LazySegTree;
  T get(int i) { return this->_node(i + n); } // O(1)
  T query(int l, int r) {                     // O(lg n)
    push(l), push(r), update(l), update(r);
    return SegTree<T>::query(l, r);
  }
  void update(int l, int r, const U &val) { // O(lg n)
    push(l), push(r);
    LazySegTree<T, U>::update(l, r, val);
  }
  void push() { for (int i = 1; i < n; _push(i++)); } // O(n)
  void push(unsigned i) { for (int s = bit_width(i += n); --s; _push(i >> s)); }
  void _push(unsigned i) {                // O(1)
    if (this->lazy[i] != this->lazy[0]) { // requires operator<=>
      this->lazy[i << 1] += this->lazy[i];
      this->lazy[i << 1 | 1] += this->lazy[i];
      this->lazy[i] = this->lazy[0];
    }
  }
};

template <typename T> struct Lazy {
  T val;            // lazy value
  bool set = false; // add by default
  auto operator<=>(const Lazy &) const = default;
  void operator+=(const Lazy &rhs) {
    set |= rhs.set;
    val = rhs.set ? rhs.val : val + rhs.val;
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
  Seg operator+(const Lazy<char> &lazy) const {
    return lazy.set ? set(lazy.val) : *this;
  }
  Seg set(char c) const { return {l, r, string(r - l + 1, c)}; }
};

void solve() {
  Str s;
  int n = s.size();
  Int k, m;
  vector<Query> q(m);
  PushSegTree<Seg, Lazy<char>> segtree(n);
  for (int i = 0; i < n; i++) {
    segtree[i] = {i, i, s.substr(i, 1)};
  }
  segtree.build();
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
    type == 1 ? segtree.update(l - 1, r - 1, {c, true}) : f(l - 1, r - 1);
  }
}

int main() {
  cin.tie(nullptr)->tie(nullptr)->sync_with_stdio(false);
  solve();
}
