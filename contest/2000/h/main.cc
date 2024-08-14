/**
 * https://codeforces.com/contest/2000/submission/276456105
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

template <typename T> struct FenTreeMap {
  const int n;
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

const auto tget = [](auto &lhs, auto &rhs) {
  if (rhs.size()) {
    lhs.insert(*rhs.begin());
  }
};
const auto tadd = [](auto &lhs, auto &rhs) { lhs.insert(rhs); };
const auto trem = [](auto &lhs, auto &rhs) { lhs.erase(rhs); };
constexpr int mxa = 2e6;

void solve(int t) {
  Int n;
  vector<Int> a(n);
  Int m;
  vector<pair<Chr, Int>> ops(m);
  set<int> vals(a.begin(), a.end()); // O(n*log n)
  vals.insert(0);
  vals.insert(2 * mxa + 1);
  FenTreeMap<set<int>> gaps(2 * mxa);
  auto add_gap = [&](auto it) { // O(log^2 n)
    auto gap = *next(it) - *it - 1;
    if (gap > 0) {
      gaps.update(2 * mxa - gap, tadd, *it);
    }
  };
  auto rem_gap = [&](auto it) { // O(log^2 n)
    auto gap = *next(it) - *it - 1;
    if (gap > 0) {
      gaps.update(2 * mxa - gap, trem, *it);
    }
  };
  for (auto it = vals.begin(), end = prev(vals.end()); it != end; it++) {
    add_gap(it);
  }
  function<void(int)> add = [&](int x) { // O(log^2 n)
    auto it = vals.lower_bound(x);
    if (*it > x) {
      rem_gap(prev(it));
      it = vals.insert(it, x);
      add_gap(it);
      add_gap(prev(it));
    }
  };
  function<void(int)> rem = [&](int x) { // O(log^2 n)
    auto it = vals.find(x);
    if (it != vals.end()) {
      rem_gap(prev(it));
      rem_gap(it);
      it = vals.erase(it);
      add_gap(prev(it));
    }
  };
  vector<int> ans;
  function<void(int)> rep = [&](int k) { // O(log^2 n)
    auto vals = gaps.query(2 * mxa - k, tget);
    assert(vals.size());
    auto x = *vals.begin();
    ans.push_back(x + 1);
  };
  for (auto &&[type, x] : ops) { // O(m*log^2 n)
    auto op = type == '+' ? add : type == '-' ? rem : rep;
    op(x);
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
