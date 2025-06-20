/**
 * https://codeforces.com/contest/2121/submission/325306599
 *
 * (c) 2025 Diego Sogari
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

template <typename T> struct Number {
  T x;
  Number() { cin >> x; }
  Number(T a) : x(a) {}
  operator T &() { return x; }
  operator T() const { return x; }
};

using Int = Number<int>;

template <typename T> struct SparseFenTree {
  int n;
  map<int, T> nodes;
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

struct Node {
  int x;
  Node(int a = 0) : x(a) {}
  Node &operator+=(const Node &rhs) {
    x = max(x, rhs.x);
    return *this;
  }
};

void solve(int t) {
  Int n;
  vector<array<Int, 2>> a(n);
  SparseFenTree<Node> fen(1e9 + 1);
  set<int, greater<int>> seen;
  vector<int> ans;
  for (auto [l, r] : a) {
    seen.insert(l);
    for (auto &&x : seen) {
      if (l <= x && x <= r) {
        fen.update(x, fen.query(x).x + 1);
      }
    }
    ans.push_back(fen.query(1e9).x);
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
