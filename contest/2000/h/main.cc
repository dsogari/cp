/**
 * https://codeforces.com/contest/2000/submission/276549811
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
  const int n;
  vector<T> nodes;
  function<T(const T &, const T &)> f;
  SegTree(int n, auto &&f, T val = {}) : n(n), f(f), nodes(2 * n, val) {}
  const T &full() const { return nodes[1]; }    // O(1)
  T &operator[](int i) { return nodes[i + n]; } // O(1)
  T query(int l, int r) const {                 // O(log n)
    assert(l >= 0 && l <= r && r < n);
    return _query(l + n, r + n);
  }
  T _query(int l, int r) const { // [l, r] O(log n)
    return l == r       ? nodes[l]
           : l % 2      ? f(nodes[l], _query(l + 1, r))
           : r % 2 == 0 ? f(_query(l, r - 1), nodes[r])
                        : _query(l / 2, r / 2);
  }
  void update(int i) { // O(log n)
    assert(i >= 0 && i < n);
    for (i = (i + n) / 2; i > 0; i /= 2) {
      nodes[i] = f(nodes[2 * i], nodes[2 * i + 1]);
    }
  }
  void update_upto(int i) { // [0, i] O(n)
    assert(i >= 0 && i < n);
    for (i = (i + n) / 2; i > 0; i--) {
      nodes[i] = f(nodes[2 * i], nodes[2 * i + 1]);
    }
  }
};

int binsearch(auto &&f, int s, int e) { // (s, e] O(log n)
  while (s < e) {
    auto m = s + (e - s + 1) / 2; // 0 < e - s < 2^31-1
    f(m) ? s = m : e = m - 1;
  }
  return e; // last such that f is true
}

const auto tmax = [](auto &lhs, auto &rhs) { return max(lhs, rhs); };
constexpr int mxa = 2e6;
SegTree<int> gaps(mxa + 2, tmax);
auto set_gap = [](auto it) { // O(log n)
  auto x = *it + 1;
  gaps[x] = *next(it) - x;
  gaps.update(x);
};
auto clear_gap = [](auto it) { // O(log n)
  auto x = *it + 1;
  gaps[x] = 0;
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
    auto f = [&](int x) { return gaps.query(0, x) < k; };
    auto x = binsearch(f, 0, mxa + 1) + 1;
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
