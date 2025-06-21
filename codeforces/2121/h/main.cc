/**
 * https://codeforces.com/contest/2121/submission/325463307
 *
 * (c) 2025 Diego Sogari
 */
#include <bits/stdc++.h>

using namespace std;
using u64 = uint64_t;

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

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

using Int = Number<int>;

struct SplitHash {
  size_t operator()(u64 x) const {
    x += (u64)this + 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
};

template <typename T> struct SparseFenTree {
  int n;
  unordered_map<int, T, SplitHash> nodes;
  SparseFenTree(int n, T val = {}) : n(n), nodes{{0, val}} {}
  T query(int i) const { // O(log n)
    assert(i < n);
    T ans = nodes.find(0)->second;
    for (i++; i > 0; i -= i & -i) {
      auto it = nodes.find(i);
      if (it != nodes.end()) {
        ans += it->second;
      }
    }
    return ans;
  }
  void update(int i, const T &val) { // O(log n)
    assert(i >= 0);
    for (i++; i <= n; i += i & -i) nodes[i] += val;
  }
};

void solve(int t) {
  Int n;
  vector<array<Int, 2>> a(n);
  SparseFenTree<int> fen(1e9 + 1);
  set<int> seen;
  vector<int> ans;
  for (auto [l, r] : a) {
    fen.update(l, 1);
    seen.insert(l);
    auto it = seen.upper_bound(r);
    if (it != seen.end()) {
      fen.update(*it, -1);
      if (fen.query(r) == fen.query(*it)) {
        seen.erase(it);
      }
    }
    ans.push_back(fen.query(1e9));
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
