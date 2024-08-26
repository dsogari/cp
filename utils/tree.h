/**
 * (c) 2024 Diego Sogari
 */
#include "graph.h"

/**
 * Path between two nodes
 */
struct Path : vector<int> {
  Path(const Graph &g, int s, int e) { dfs(g, s, e, s); }
  int dfs(const Graph &g, int a, int b, int p) {
    push_back(a);
    if (a == b) {
      return true;
    }
    for (auto &v : g[a]) {
      if (v != p && dfs(g, v, b, a)) {
        return true;
      }
    }
    pop_back();
    return false;
  }
};

/**
 * Matching
 */
struct Match : vector<int> {
  int count = 0;
  Match(const Graph &g, int s) : vector<int>(g.size(), -1) { dfs(g, s, s); }
  void dfs(const Graph &g, int u, int p) {
    for (auto v : g[u]) {
      if (v != p) {
        dfs(g, v, u); // post-order (visit leaves first)
        if ((*this)[u] == (*this)[v]) {
          (*this)[u] = v;
          (*this)[v] = u;
          count++;
        }
      }
    }
  }
};

/**
 * Tree (with additional information)
 */
struct Tree : Graph {
  struct Info {
    int par, dep, siz, hei;
  };
  vector<Info> info;
  Tree(int n) : Graph(n), info(n + 1) {} // no edges
  Tree(int n, int s) : Graph(n, n - 1), info(n + 1) { dfs(s, s); }
  void dfs(int u, int p, int d = 1) {
    auto &cur = info[u] = {p, d, 1, 1};
    for (auto &v : (*this)[u]) {
      if (v != p) {
        dfs(v, u, d + 1);
        cur.siz += info[v].siz;
        cur.hei = max(cur.hei, 1 + info[v].hei);
      }
    }
  }
};

/**
 * Disjoint set union (Union find)
 */
struct DSU {
  vector<int> par, siz;
  DSU(int n) : par(n + 1), siz(n + 1) {}
  int add(int v) { return siz[v] = 1, par[v] = v; }
  int find(int v) { return v == par[v] ? v : par[v] = find(par[v]); }
  int merge(int a, int b) {
    a = find(a), b = find(b);
    if (a != b) {
      if (siz[a] < siz[b]) {
        swap(a, b);
      }
      siz[a] += siz[b];
      par[b] = a;
    }
    return a;
  }
};

/**
 * Lowest Common Ancestor (Tarjan's off-line algorithm)
 */
struct LCA : vector<vector<int>> {
  DSU dsu;
  vector<int> anc, vis;
  LCA(const Graph &g, const vector<vector<int>> &q, int s)
      : vector<vector<int>>(g.size()), dsu(g.size()), anc(g.size()),
        vis(g.size()) {
    dfs(g, q, s, s);
  }
  void dfs(const Graph &g, const vector<vector<int>> &q, int u, int p) {
    for (auto &v : g[u]) {
      if (v != p) {
        dfs(g, q, v, u);
        anc[dsu.merge(v, u)] = u;
      }
    }
    for (auto &v : q[u]) {
      if (vis[v]) { // otherwise, wait until v is processed
        (*this)[u].push_back(anc[dsu.find(v)]);
      }
    }
  }
};

/**
 * Trie (N-ary prefix or suffix tree)
 */
template <typename T, size_t N> struct Trie {
  vector<pair<T, array<int, N>>> nodes;
  Trie(int cap = 1) : nodes(1) { nodes.reserve(cap); }
  void visit(auto &&f, auto &&x) {
    for (int i = 0, j = 0;; j++) {
      int k = f(nodes[i], j, x);
      if (k < 0) {
        break;
      }
      assert(k < N);
      auto &child = nodes[i].second[k];
      if (!child) {
        child = nodes.size();
        nodes.emplace_back(); // might invalidate references
      }
      i = nodes[i].second[k];
    }
  }
};

/**
 * Fenwick Tree (Binary indexed tree)
 */
template <typename T> struct FenTree {
  int n;
  vector<T> nodes;
  function<T(const T &, const T &)> f;
  FenTree(int n, auto &&f, T val = {}) : n(n), f(f), nodes(n + 1, val) {}
  T query(int i) const { // O(log n)
    assert(i < n);
    T ans = nodes[0];
    for (i++; i > 0; i -= i & -i) {
      ans = f(ans, nodes[i]);
    }
    return ans;
  }
  void update(int i, const T &val) { // O(log n)
    assert(i >= 0);
    for (i++; i <= n; i += i & -i) {
      _apply(i, val);
    }
  }
  void _apply(int i, const T &val) { nodes[i] = f(nodes[i], val); }
};

/**
 * Fenwick Tree (with linear range updates)
 */
template <typename T> struct FenTreePlus : FenTree<T> {
  using FenTree<T>::FenTree;
  void update_from(int l, auto it) { // [l, n] O(n)
    assert(l >= 0);
    for (l++; l <= this->n; l++, it++) {
      this->_apply(l, *it);
      int r = l + (l & -l);
      if (r <= this->n) {
        this->_apply(r, *it);
      }
    }
  }
  void update_from(int l, const T &val) { // [l, n] O(n)
    struct {
      const T &val;
      const T &operator*() { return val; }
      void operator++(int) {}
    } it{val};
    update_from(l, it);
  }
};

/**
 * Fenwick Tree (using a map)
 */
template <typename T> struct FenTreeMap {
  int n;
  unordered_map<int, T> nodes = {{0, {}}};
  FenTreeMap(int n) : n(n) {}
  T query(int i, auto &&f) const { // O(log n)
    assert(i < n);
    T ans = nodes.find(0)->second;
    for (i++; i > 0; i -= i & -i) {
      auto it = nodes.find(i);
      if (it != nodes.end()) {
        f(ans, it->second);
      }
    }
    return ans;
  }
  void update(int i, auto &&f, const auto &val) { // O(log n)
    assert(i >= 0);
    for (i++; i <= n; i += i & -i) {
      f(nodes[i], val);
    }
  }
};

/**
 * Segment Tree
 */
template <typename T> struct SegTree {
  int n;
  vector<T> nodes;
  function<T(const T &, const T &)> f;
  SegTree(int n, auto &&f, T val = {}) : n(n), f(f), nodes(2 * n, val) {}
  const T &full() const { return nodes[1]; }    // O(1)
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

/**
 * Lazy Segment Tree (for range updates and full queries)
 */
template <typename T, typename U> struct LazySegTree : SegTree<T> {
  vector<U> lazy;
  function<T(const T &, const U &)> ftree;
  function<U(const U &, const U &)> flazy;
  LazySegTree(int n, auto &&f, auto &&ft, auto &&fl, T val = {}, U lazyval = {})
      : SegTree<T>(n, f, val), ftree(ft), flazy(fl), lazy(2 * n, lazyval) {}
  using SegTree<T>::update;
  void update(int l, int r, const U &val) { // [l, r] O(log n)
    this->_check(l, r);
    _apply(l + this->n, r + this->n, val);
    this->_build(l + this->n, true);
    this->_build(r + this->n, true);
  }
  void _apply(int l, int r, const U &val) { // [l, r] O(log n)
    return l == r   ? _apply(l, val)
           : l & 1  ? (_apply(l, val), _apply(l + 1, r, val))
           : ~r & 1 ? (_apply(r, val), _apply(l, r - 1, val))
                    : _apply(l >> 1, r >> 1, val);
  }
  void _apply(int i, const U &val) { lazy[i] = flazy(lazy[i], val); }
  virtual T _node(int i) const { return ftree(this->nodes[i], lazy[i]); }

private:
  using SegTree<T>::query; // hide method (only full queries allowed)
};

/**
 * Push Segment Tree (for range updates and arbitrary queries)
 */
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
    int s = bit_width(i), j = 0, end = single ? i : i >> 1 | 1;
    function<void()> inc[] = {[&]() { j++; }, [&]() { s--, j = i >> s; }};
    for (inc[single](); j != end; inc[single]()) {
      _pushone(j);
    }
    this->_build(i, single);
  }
  void _pushone(int i) { // O(1)
    if (this->lazy[i] != this->lazy[0]) {
      this->_apply(i << 1, this->lazy[i]);
      this->_apply(i << 1 | 1, this->lazy[i]);
      this->lazy[i] = this->lazy[0];
    }
  }
};

/**
 * Interval Tree Node
 */
template <typename T> struct Interval {
  T mid;
  list<array<T, 2>> contained;
  void insert(T l, T r) { contained.push_back({l, r}); } // O(1)
  void visit(T x, auto &&f) {                            // O(n)
    for (auto it = contained.begin(); it != contained.end();) {
      auto [l, r] = *it;
      it = l <= x && x < r && f(l, r) ? contained.erase(it) : next(it);
    }
  }
  bool contains(T x) const {
    auto f = [&](auto &pair) { return pair[0] <= x && x < pair[1]; };
    return ranges::find_if(contained, f) != contained.end();
  }
};

/**
 * Interval Tree
 */
template <typename T> struct IntTree {
  int n;
  vector<Interval<T>> nodes;
  IntTree(int n) : n(n), nodes(2 * n) {}
  IntTree(int n, T l, T r) : IntTree(n) { build(l, r); }
  void build(T l, T r, int i = 1) { // [l, r) O(n)
    auto mid = nodes[i].mid = (l + r) / 2;
    if (i < n) {
      build(l, mid, 2 * i);
      build(mid, r, 2 * i + 1);
    }
  }
  void insert(T l, T r) { // [l, r) O(log n)
    assert(l < r);
    int i = 1;
    while (i < n && (l >= nodes[i].mid || r <= nodes[i].mid)) {
      i = 2 * i + (l >= nodes[i].mid);
    }
    nodes[i].insert(l, r);
  }
  void visit(T x, auto &&f) { // O(n^2) all covering point x
    int i = 1;
    for (; i < n; i = 2 * i + (x >= nodes[i].mid)) {
      nodes[i].visit(x, f); // internal node
    }
    nodes[i].visit(x, f); // leaf node
  }
  bool contains(T x) const {
    int i = 1;
    for (; i < n; i = 2 * i + (x >= nodes[i].mid)) {
      if (nodes[i].contains(x)) { // internal node
        return true;
      }
    }
    return nodes[i].contains(x); // leaf node
  }
};

/**
 * Cartesian Tree (using a vector)
 */
struct Treap {
  struct Info {
    int par, left, right, start, end; // [start,end) of subtree
  };
  vector<Info> nodes;
  stack<int> above; // minimum stack
  function<bool(int, int)> f;
  int top = -1;
  Treap(auto &&f) : f(f) {}
  void push(int i) { // O(1) amortized / i must be pushed in order
    assert(i == nodes.size());
    nodes.emplace_back(-1, -1, -1, i, -1);
    int last = -1;
    while (above.size() && f(above.top(), i)) {
      last = above.top();
      nodes[last].end = i;
      above.pop();
    }
    if (above.size()) {
      nodes[i].par = above.top(); // smallest greater or equal
      nodes[above.top()].right = i;
    }
    if (last >= 0) {
      nodes[last].par = i;
      nodes[i].left = last; // greatest smaller
      nodes[i].start = nodes[last].start;
    }
    if (top < 0 || f(top, i)) {
      top = i;
    }
    above.push(i);
  }
  void finish() { // O(n)
    while (!above.empty()) {
      nodes[above.top()].end = nodes.size();
      above.pop();
    }
  }
};

/**
 * Cartesian Tree (using a map)
 */
template <typename T> struct TreapMap {
  struct Info {
    T par, left, right, start, end; // [start,end] of subtree
  };
  unordered_map<T, Info> nodes;
  stack<T> above; // minimum stack
  function<bool(const T &, const T &)> f;
  const Info empty;
  T top, end, def;
  TreapMap(auto &&f, T def) : f(f), top(def), end(def), def(def) {}
  void push(T x) { // O(1) amortized / x must be pushed in order
    assert(above.empty() || above.top() < x);
    nodes.emplace(x, Info{def, def, def, x, def});
    T last = def;
    while (above.size() && f(above.top(), x)) {
      last = above.top();
      nodes[last].end = end;
      above.pop();
    }
    if (above.size()) {
      nodes[x].par = above.top(); // smallest greater or equal
      nodes[above.top()].right = x;
    }
    if (last != def) {
      nodes[last].par = x;
      nodes[x].left = last; // greatest smaller
      nodes[x].start = nodes[last].start;
    }
    if (top == def || f(top, x)) {
      top = x;
    }
    end = x;
    above.push(x);
  }
  void finish() { // O(n)
    while (!above.empty()) {
      nodes[above.top()].end = end;
      above.pop();
    }
  }
};

// Tree manipulation
const auto tadd = [](auto &lhs, auto &rhs) { return lhs + rhs; };
const auto tmul = [](auto &lhs, auto &rhs) { return lhs * rhs; };
const auto tmin = [](auto &lhs, auto &rhs) { return min(lhs, rhs); };
const auto tmax = [](auto &lhs, auto &rhs) { return max(lhs, rhs); };

// Trie manipulation
const auto nodeinc = [](auto &node) { node++; };
const auto nodedec = [](auto &node) { node--; };
const auto nodevis = [](auto &&fn, auto &&fx, auto &node, int j, auto &&x) {
  return fn(node.first), fx(j, x);
};

// Bit prefixes
const auto bitpref = [](int j, unsigned x) {
  return j < 32 ? (x & (1 << (31 - j))) != 0 : -1;
};
const auto bpinc = bind(nodevis, nodeinc, bitpref, _1, _2, _3);
const auto bpdec = bind(nodevis, nodedec, bitpref, _1, _2, _3);

// Bit suffixes
const auto bitsuff = [](int j, unsigned x) {
  return j < 32 ? (x & (1 << j)) != 0 : -1;
};
const auto bsinc = bind(nodevis, nodeinc, bitsuff, _1, _2, _3);
const auto bsdec = bind(nodevis, nodedec, bitsuff, _1, _2, _3);

// String prefixes
const auto strpref = [](int j, auto &&s) {
  return j < s.size() ? s[j] - 'a' : -1;
};
const auto spinc = bind(nodevis, nodeinc, strpref, _1, _2, _3);
const auto spdec = bind(nodevis, nodedec, strpref, _1, _2, _3);

// String suffixes
const auto strsuff = [](int j, auto &&s) {
  return j < s.size() ? s[s.size() - j - 1] - 'a' : -1;
};
const auto ssinc = bind(nodevis, nodeinc, strsuff, _1, _2, _3);
const auto ssdec = bind(nodevis, nodedec, strsuff, _1, _2, _3);
